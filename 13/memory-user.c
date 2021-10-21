#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv)
{
    printf("PID: %d\n", getpid());

    int memory, *array;
    long int time, diff;

    memory = atoi(argv[1]);
    time = atoi(argv[2]);
    array = malloc(memory);
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do
    {
        for (int i = 0; i < memory; i++)
        {
            array[i] += 1;
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        diff = end.tv_sec-start.tv_sec;
    } while (diff <= time);
    free(array);
    return 0;
}
