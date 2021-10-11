#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sched.h>

int main()
{
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    int fd[2];

    if (pipe(fd) == -1)
    {
        exit(1);
    }

    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask) == -1)
        {
            exit(EXIT_FAILURE);
        }
        close(fd[0]);
        struct timeval t;
        gettimeofday(&t, NULL);
        write(fd[1], &t, sizeof(struct timeval));
        exit(0);
    }
    else
    {
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask) == -1)
        {
            exit(EXIT_FAILURE);
        }
        close(fd[1]);
        struct timeval t1;
        read(fd[0], &t1, sizeof(struct timeval));
        printf("t1.tv_sec = %ld, t1.tv_usec = %ld\n", t1.tv_sec, t1.tv_usec);

        struct timeval t2;
        gettimeofday(&t2, NULL);
        printf("t2.tv_sec = %ld, t2.tv_usec = %ld\n", t2.tv_sec, t2.tv_usec);

        long int sec_diff = t2.tv_sec - t1.tv_sec;
        long int usec_diff = t2.tv_usec - t1.tv_usec;

        if (usec_diff < 0)
        {
            sec_diff -= 1;
            usec_diff = 1000000 + sec_diff;
        }

        printf("sec_diff = %ld, usec_diff = %ld\n", sec_diff, usec_diff);
    }
    return 0;
}
