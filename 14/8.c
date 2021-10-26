#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct vector
{
    int basic_size;
    int max_length;
    int length;
    void **items;
} vector;

typedef struct Node
{
    void *item;
    struct Node *last;
    struct Node *next;
} Node;

typedef struct linked_list
{
    Node *first;
    Node *last;
} linked_list;

vector *create_vector(int basic_size)
{
    vector *v = malloc(sizeof(vector));
    v->basic_size = basic_size;
    v->max_length = basic_size;
    v->length = 0;
    v->items = malloc(basic_size * sizeof(void *));
    return v;
}

linked_list *create_linked_list()
{
    linked_list *l = malloc(sizeof(linked_list));
    l->first = NULL;
    l->last = NULL;
    return l;
}

void resize_vector(vector *v)
{
    const int new_size = v->max_length + v->basic_size;
    v->items = realloc(v->items, new_size * sizeof(void *));
    v->max_length = new_size;
    if (v->items == NULL)
    {
        fprintf(stderr, "realloc failed!\n");
        exit(1);
    }
}

void add_item_to_vector(vector *v, void *item)
{
    const int index = v->length;
    if (index == v->max_length)
    {
        resize_vector(v);
    }
    v->items[index] = item;
    v->length += 1;
}

void add_item_to_linked_list(linked_list *l, void *item)
{
    Node *n = malloc(sizeof(Node));
    n->next = NULL;
    n->item = item;
    n->last = l->last;

    if (l->first == NULL)
    {
        l->first = n;
    }
    else if (l->last != NULL)
    {
        l->last->next = n;
    }
    l->last = n;
}

void print_vector(vector *v)
{
    for (int i = 0; i < v->length; i++)
    {
        printf("v->items[%d] = %d\n", i, *((int *)v->items[i]));
    }
}

void print_linked_list(linked_list *l)
{
    Node *n = l->first;
    int i = 0;
    while (n != NULL)
    {
        printf("v->items[%d] = %d\n", i, *((int *)n->item));
        n = n->next;
        i++;
    }
}

int **fill_integer_array(int number_of_items)
{
    int **array = malloc(number_of_items * sizeof(int *));
    for (int i = 0; i < number_of_items; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i * 4;
        array[i] = a;
    }
    return array;
}

long get_diff(struct timespec *start, struct timespec *end)
{
#define BILLION 1000000000L
    return ((*end).tv_sec - (*start).tv_sec) * BILLION + (*end).tv_nsec - (*start).tv_nsec;
}

long get_loop_time(int number_of_items)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < number_of_items; i++)
    {
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    return get_diff(&start, &end);
}

void free_integer_array(int **array, int number_of_items)
{
    for (int i = 0; i < number_of_items; i++)
    {
        free(array[i]);
    }
    free(array);
}

void free_vector(vector *v)
{
    free(v->items);
    free(v);
}

void free_linked_list(linked_list *l)
{
    Node *n = l->first;
    while (n != NULL)
    {
        Node *p = n;
        n = n->next;
        free(p);
    }
    free(l);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Anzahl Listeneinträge und Basisgröße des Vektor"
                        "eingeben!\nmit -p die Listen ausgeben\n");
        exit(1);
    }
    const int number_of_items = atoi(argv[1]);
    const int basic_size_vector = atoi(argv[2]);
    const bool print_values = argc == 4 && strcmp(argv[3], "-p") == 0;

    const int loop_time = get_loop_time(number_of_items);

    vector *v = create_vector(basic_size_vector);
    linked_list *l = create_linked_list();

    int **array = fill_integer_array(number_of_items);
    struct timespec start, end;
    //long loop_time = getLoopTime(number_of_items);

    //Add to vector

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < number_of_items; i++)
    {
        add_item_to_vector(v, array[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("diff(add to vector) = %ld ns\n", get_diff(&start, &end) - loop_time);

    //Add to LinkedList
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < number_of_items; i++)
    {
        add_item_to_linked_list(l, array[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("diff(add to linked_list) = %ld ns\n", get_diff(&start, &end) - loop_time);

    if (print_values)
    {
        //Print Vector
        clock_gettime(CLOCK_MONOTONIC, &start);
        print_vector(v);
        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("diff(print vector) = %ld ns\n", get_diff(&start, &end) - loop_time);

        //Print LinkedList
        clock_gettime(CLOCK_MONOTONIC, &start);
        print_linked_list(l);
        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("diff(print linked_list) = %ld ns\n", get_diff(&start, &end) - loop_time);
    }

    free_integer_array(array, number_of_items);
    free_vector(v);
    free_linked_list(l);
    return 0;
}
