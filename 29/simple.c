#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MILLION 1000000
#define BILLION 1E9

typedef struct __counter_t
{
    long int value;
} counter_t;

void init(counter_t *c)
{
    c->value = 0;
};

void increment(counter_t *c)
{
    c->value++;
}

void decrement(counter_t *c)
{
    c->value--;
}

int get(counter_t *c)
{
    return c->value;
}

counter_t c_t;

long int getTime(struct timespec *start, struct timespec *end){
    long int secDiff = end->tv_sec - start->tv_sec;
    long int nsecDiff = end->tv_nsec - start->tv_nsec;
    if(nsecDiff < 0){
        secDiff -= 1.0;
        nsecDiff += BILLION;
    }
    long int accum = secDiff * BILLION + nsecDiff;
    return accum;
}

int main()
{
    int cpu_count = (int)sysconf(_SC_NPROCESSORS_ONLN);
    printf("CPU count: %d\n", cpu_count);

    struct timespec start, end;
    long int total_time;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (int i = 0; i < MILLION; i++)
    {
        increment(&c_t);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    total_time = getTime(&start, &end);
    printf("Counter: %ld\n", c_t.value);
    printf("Time: %ld ns\n", total_time);

    return 0;
}

long int loopTime()
{
    long int totalLoop;
    struct timespec start, end;
    if (clock_gettime(CLOCK_MONOTONIC_RAW, &start) < 0)
    {
        printf("timestamp start error!");
        exit(1);
    }
    for (int i = 0; i < MILLION; i++)
    {
    }
    if (clock_gettime(CLOCK_MONOTONIC_RAW, &end) < 0)
    {
        printf("timestamp end error!");
        exit(1);
    }
    totalLoop = ((end.tv_sec - start.tv_sec) + BILLION) + (end.tv_nsec - start.tv_nsec);
    return totalLoop;
}