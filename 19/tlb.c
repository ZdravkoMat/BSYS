#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>

#define PAGESIZE 4096 // getconf PAGESIZE
#define BILLION 1000000000L

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        puts("No Inputs! -> ./tlb.out pages trials");
        exit(1);
    }

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(9, &mask);

    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1)
    {
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    }

    int pages = atoi(argv[1]);
    int trials = atoi(argv[2]);
    int jump = PAGESIZE / sizeof(int);
    int *a = (int *)malloc((size_t)pages * (size_t)PAGESIZE);;
    struct timespec start, end;
    //long int time = 0;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (int t = 0; t < trials; t++)
    {
        for (int i = 0; i < pages * jump; i += jump)
        {
            a[i] += 1;
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Time S: %ld ns\n", (end.tv_sec - start.tv_sec) / trials);
    printf("Time NS: %ld ns\n", (end.tv_nsec - start.tv_nsec) / trials);
}
