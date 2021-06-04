#ifdef Linux
#define _GNU_SOURCE
#include <sched.h> // CPU_ZERO
#endif

#include "thread_helper.h"
#include <stdio.h>
#include <stdlib.h>   // malloc, free
#include <sys/time.h> // clock_gettime
#include <unistd.h>   // sysconf
#define ONE_MILLION 1000000

typedef struct __counter_t {
  int value;
  pthread_mutex_t lock;
} counter_t;

typedef struct __thread_info_t {
  counter_t *counter;
  pthread_t thread;
  int cpu_idx;
} thread_info_t;

static void init(counter_t *c) {
  c->value = 0;
  Pthread_mutex_init(&c->lock, NULL);
}

static void increment(counter_t *c) {
  Pthread_mutex_lock(&c->lock);
  c->value++;
  Pthread_mutex_unlock(&c->lock);
}

static int get(counter_t *c) {
  Pthread_mutex_lock(&c->lock);
  int rc = c->value;
  Pthread_mutex_unlock(&c->lock);
  return rc;
}

static void *thread_function(void *arg) {
  thread_info_t *m = (thread_info_t *)arg;
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset); // Clears set, so that it contains no CPUs
  CPU_SET(m->cpu_idx, &cpuset); // Add CPU cpu to set
  Pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset); // Sets the CPU affinity mask

  for (int i = 0; i < ONE_MILLION; i++)
    increment(m->counter);

  pthread_exit(EXIT_SUCCESS);
}

int main() {
  int cpus = (int)sysconf(_SC_NPROCESSORS_ONLN); // Return number of processors that are available

  for (int i = 1; i <= cpus; i++) { // Schleife für CPUs
    for (int l = 1; l <= cpus; l++) { // Schleife für Threads

      thread_info_t *tinfo = malloc((size_t)l * sizeof(thread_info_t));
      counter_t *counter = malloc(sizeof(counter_t));
      init(counter);

      struct timespec start, stop;

      clock_gettime(CLOCK_MONOTONIC, &start);
      
      for (int j = 0; j < l; j++) {
        tinfo[j].counter = counter;
        Pthread_create(&tinfo[j].thread, NULL, &thread_function, &tinfo[j]);
      }

      for (int k = 0; k < l; k++)
        Pthread_join(tinfo[k].thread, NULL);
      
      clock_gettime(CLOCK_MONOTONIC, &stop);

      long long startusec, endusec;
      startusec = start.tv_sec * ONE_MILLION + start.tv_nsec;
      endusec = stop.tv_sec * ONE_MILLION + stop.tv_nsec;

      printf("%d cpus, %d threads\n", i, l);
      printf("global count: %d\n", get(counter));
      printf("Time (seconds): %f\n\n", ((double)(endusec - startusec) / 1000000000));
      
      Pthread_mutex_destroy(&counter->lock);
      free(counter);
      free(tinfo);
    }
  }
  return 0;
}