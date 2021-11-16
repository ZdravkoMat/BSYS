#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <sched.h>
#define handle_error_en(en, msg) \
    do                           \
    {                            \
        errno = en;              \
        perror(msg);             \
        exit(EXIT_FAILURE);      \
    } while (0)

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Aufruf: Seitengröße, Anzahl der Seiten und Versuche");
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

    int PAGESIZE = atoi(argv[1]);
    int NUMPAGES = atoi(argv[2]);
    int TRIALS = atoi(argv[3]);

    const int JUMP = PAGESIZE / sizeof(int);

    int *a = malloc(NUMPAGES * PAGESIZE);

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);

    for (int j = 0; j < TRIALS; j++)
    {
        for (int i = 0; i < NUMPAGES * JUMP; i += JUMP)
            a[i] += 1;
    }

    clock_gettime(CLOCK_MONOTONIC, &t2);

    long int diff = (t2.tv_sec - t1.tv_sec) * 1000000000 + (t2.tv_nsec - t1.tv_nsec);
    printf("%ld\n", diff);
    free(a);
    return 0;
}
