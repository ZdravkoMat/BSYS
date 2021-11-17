#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>

#define PAGESIZE 4096
#define BILLION 1000000000
#define handle_error_en(en, msg) \
    do                           \
    {                            \
        errno = en;              \
        perror(msg);             \
        exit(EXIT_FAILURE);      \
    } while (0)

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        puts("No Inputs! -> ./tlb.out pages trials");
        exit(1);
    }

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    int s;
    pthread_t thread = pthread_self();

    s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &mask);
    if (s != 0)
        handle_error_en(s, "pthread_setaffinity_np");

    int NUMPAGES = atoi(argv[1]);
    int TRIALS = atoi(argv[2]);
    const int jump = PAGESIZE / sizeof(int);
    int *a = malloc(NUMPAGES * PAGESIZE);
    struct timespec start, end;
    long int time = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int t = 0; t < TRIALS; t++)
    {
        for (int i = 0; i < (NUMPAGES * jump); i += jump)
        {
            a[i] += 1;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    time = (end.tv_sec - start.tv_sec) * BILLION + (end.tv_nsec - start.tv_nsec);

    printf("Time: %ld\n", time / NUMPAGES / TRIALS);
    free(a);
    return 0;
}
