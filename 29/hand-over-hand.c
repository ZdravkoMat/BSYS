#include "thread_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define ONE_MILLION 1000000

// basic node structure
typedef struct __node_t {
  struct __node_t *next;
  pthread_mutex_t lock;
  int key;
} node_t;

// basic list structure (one used per list)
typedef struct __list_t {
  node_t *head;
  pthread_mutex_t insert_lock;
} list_t;

static void List_Init(list_t *L) {
  L->head = NULL;
  Pthread_mutex_init(&L->insert_lock, NULL);
}

static void List_Insert(list_t *L, int key) {
  // synchronization not needed
  node_t *new = malloc(sizeof(node_t));
  if (new == NULL)
    handle_error_en(errno, "malloc");
  new->key = key;
  Pthread_mutex_init(&new->lock, NULL);

  // just lock critical section
  Pthread_mutex_lock(&L->insert_lock);
  new->next = L->head;
  L->head = new;
  Pthread_mutex_unlock(&L->insert_lock);
}

static int List_Lookup(list_t *L, int key) {
  int rv = -1;
  node_t *curr = L->head;
  if (!curr)
    return rv;
  Pthread_mutex_lock(&curr->lock);
  while (curr) {
    if (curr->key == key) {
      rv = 0;
      Pthread_mutex_unlock(&curr->lock);
      break;
    }
    pthread_mutex_t *tempLock = &curr->lock;
    curr = curr->next;
    if (curr)
      Pthread_mutex_lock(&curr->lock);
    Pthread_mutex_unlock(tempLock);
  }
  return rv; // now both success and failure
}

static void List_Free(list_t *L) {
  node_t *curr = L->head;
  if (!curr)
    return;
  Pthread_mutex_lock(&curr->lock);
  while (curr) {
    node_t *tempNode = curr;
    curr = curr->next;
    if (curr)
      Pthread_mutex_lock(&curr->lock);
    Pthread_mutex_unlock(&tempNode->lock);
    free(tempNode);
  }
  free(L);
}

static void *thread_function(void *args) {
  list_t *l = (list_t *)args;
  List_Lookup(l, 0);
  pthread_exit(EXIT_SUCCESS);
}

int main() {
  int list_length = ONE_MILLION;
  int thread_count = 4;

  list_t *list = malloc(sizeof(list_t));
  List_Init(list);

  for (int i = 0; i < list_length; i++)
    List_Insert(list, i);

  for (int i = 1; i <= thread_count; i++) {

    struct timespec start, stop;

    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_t *threads = malloc((size_t)i * sizeof(pthread_t));

    for (int j = 0; j < i; j++)
      Pthread_create(&threads[j], NULL, &thread_function, list);
    for (int k = 0; k < i; k++)
      Pthread_join(threads[k], NULL);

    clock_gettime(CLOCK_MONOTONIC, &stop);

    long long startusec, endusec;
    startusec = start.tv_sec * ONE_MILLION + start.tv_nsec;
    endusec = stop.tv_sec * ONE_MILLION + stop.tv_nsec;

    printf("%d threads, time (seconds): %f\n\n", i, ((double)(endusec - startusec) / 1000000000));
    free(threads);
  }

  List_Free(list);

  return 0;
}