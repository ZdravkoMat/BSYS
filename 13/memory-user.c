#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MB 1024 * 1024

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "./memory-user.out MB SEK");
    }
    printf("PID: %d\n", getpid());

    int memory;
    char *array;
    long int time, diff;

    memory = atoi(argv[1]) * MB;
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
        diff = end.tv_sec - start.tv_sec;
    } while (diff <= time);
    free(array);
    return 0;
}
