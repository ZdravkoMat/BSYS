#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#define BILLION 1000000000L

int main(int argc, char **argv) {
    int i, j;
    int *a;
    long int time;
    cpu_set_t set;
    struct timespec start, end;
    if (argc != 3) {
        puts("usage: ./tlb npages ntrials");
        exit(1);
    }
    CPU_SET(0, &set);
    if (sched_setaffinity(getpid(), sizeof(set), &set) == -1) {
        fprintf(stderr, "Schederror\n");
        exit(2);
    }
    long PAGESIZE = sysconf(_SC_PAGESIZE);
    long int npages = atoi(argv[1]);
    int ntrials = atoi(argv[2]);
    int jump = PAGESIZE / sizeof(int);
    a = calloc((npages * jump), sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    for (i = 0; i < (npages * jump); i += jump) {
        a[i] += 1;
    }
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        fprintf(stderr, "error in clock_getres\n");
        exit(3);
    }
    for (j = 0; j < ntrials; j++) {
        for (i = 0; i < (npages * jump); i += jump) {
            a[i] += 1;
        }
    }
    if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
        fprintf(stderr, "error in clock_getres\n");
        exit(3);
    }
    time = (BILLION * (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec))/ntrials;
    double result = (double)time / npages;
    fprintf(stdout, "%ld\n", npages);
    fprintf(stdout, "%f\n", result);
    return 0;
}