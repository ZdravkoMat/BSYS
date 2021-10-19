#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main()
{
    long int time = 0, loops = 1000000;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < loops; i++)
    {
        open("./file.txt", O_WRONLY | O_CREAT);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    if ((end.tv_nsec-start.tv_nsec)<0)
    {
        time += ((end.tv_sec - start.tv_sec) + (1000000000 + end.tv_nsec - start.tv_nsec)) / loops;
    }
    else 
    {
        time += ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)) / loops;
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < loops; i++)
    {
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    if ((end.tv_nsec-start.tv_nsec)<0)
    {
        time -= ((end.tv_sec - start.tv_sec) + (1000000000 + end.tv_nsec - start.tv_nsec)) / loops;
    }
    else 
    {
        time -= ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)) / loops;
    }
    printf("systemcall: %ld ns\n", time);
    return 0;
}
