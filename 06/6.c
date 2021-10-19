#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>

int main()
{
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(1, &mask);
    struct timespec start, end;
    long int time = 0, loops = 1000000;
    int fd1[2], fd2[2];
    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int rc = fork();
    if (rc < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (rc == 0)
    {
        if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1)
        {
            perror("sched_setaffinity");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < loops; i++)
        {
            read(fd1[0], NULL, 0);
            write(fd2[1], NULL, 0);
        }
    }
    else
    {
        if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1)
        {
            perror("sched_setaffinity");
            exit(EXIT_FAILURE);
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < loops; i++)
        {
            write(fd1[1], NULL, 0);
            read(fd2[0], NULL, 0);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        if ((end.tv_nsec - start.tv_nsec) < 0)
        {
            time += ((end.tv_sec - start.tv_sec) + (1000000000 + end.tv_nsec - start.tv_nsec)) / loops;
            printf("%ld\n", time);
        }
        else
        {
            time += ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)) / loops;
            printf("%ld\n", time);
        }
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < loops; i++)
        {
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        if ((end.tv_nsec - start.tv_nsec) < 0)
        {
            time -= ((end.tv_sec - start.tv_sec) + (1000000000 + end.tv_nsec - start.tv_nsec)) / loops;
            printf("%ld\n", time);
        }
        else
        {
            time -= ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)) / loops;
            printf("%ld\n", time);
        }
        printf("%ld\n", time);
    }
    return 0;
}
