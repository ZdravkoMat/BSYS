#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define STATS 200
#define BILLION 1000000000L

long int cost(unsigned int nbytes) {
    char buf[1];
    //defined in /usr/include/bits/types/struct_timespec.h
    struct timespec start, end;
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        fprintf(stderr, "error in clock_getres\n");
        exit(1);
    }
    for (int i = 0; i < nbytes; i++) {
        read(STDIN_FILENO, buf, 0);
    }
    if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
        fprintf(stderr, "error in clock_getres\n");
        exit(1);
    }
    //convert seconds to nanoseconds and add to nanoseconds
    long int res = (BILLION * (end.tv_sec - start.tv_sec) +
                    (end.tv_nsec - start.tv_nsec)) /
                   nbytes;
    return res;
}

void statistics() {
    int nbytes[] = {100, 1000, 10000, 100000};
    long int average_nsec[sizeof(nbytes) / sizeof(int)] = {0};
    int length = sizeof(nbytes) / sizeof(int);
    long int average = 0;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < STATS; j++) {
            average_nsec[i] += cost(nbytes[i]);
        }
        average_nsec[i] /= STATS;
        printf("average for read %d times : %ld ns\n", nbytes[i],
               (average_nsec[i]));
    }
    for (int i = 0; i < length; i++) {
        average += average_nsec[i];
    }
    printf("average total : %ld ns\n", average / length);
    return;
}

int main(int argc, char **argv) {
    statistics();
    return 0;
}