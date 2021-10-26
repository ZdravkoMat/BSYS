#include <stdio.h>
#include <stdlib.h>

typedef struct vector
{
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

typedef struct linked_List
{
    Node *first;
    Node *last;
} linked_list;

vector *create_vector(int size)
{
    vector *v = malloc(sizeof(vector));
    v->max_length = size;
    v->length = 0;
    v->items = malloc(size * sizeof(void *));
    return v;
}

linked_list *create_linked_list()
{
    linked_list *l = malloc(sizeof(linked_list));
    l->first = NULL;
    l->last = NULL;
    return l;
}

void add_item_to_vector(vector *v, void *item)
{
    const int index = v->length;
    if (index == v->max_length)
    {
        fprintf(stderr, "Size of vector reached!\n");
        exit(1);
    }
    v->items[index] = item;
    v->length += 1;
}

void add_item_to_liked_list(linked_list *l, void *item)
{
    Node *n = malloc(sizeof(Node));
    n->item = item;
    n->last = l->last;
    n->next = NULL;
    if (n->last != NULL)
    {
        n->last->next = n;
    }
    l->last = n;
}

void resize_vector(vector *v, int new_size)
{
    if(realloc(v, new_size)== NULL){
        exit(1);
    }
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
        i++;
    }
}

void free_vector(vector *v)
{
    for (int i = 0; i < v->length; i++)
    {
        free(v->items[i]);
    }
    free(v->items);
    free(v);
}

int main()
{
    vector *v = create_vector(100);
    linked_list *l = create_linked_list();

    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    *a = 5464;
    *b = 6565;

    printf("Added to Vector!\n");
    add_item_to_vector(v, a);
    add_item_to_vector(v, b);
    printf("Added to Linked List!\n");
    add_item_to_liked_list(l, a);
    add_item_to_liked_list(l, b);
    printf("Printing:\n");
    print_vector(v);
    print_linked_list(l);

    resize_vector(v, 20);
    print_vector(v);

    free_vector(v);

    return 0;
}
