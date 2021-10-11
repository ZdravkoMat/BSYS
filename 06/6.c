#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sched.h>

int main()
{
    const int core_id = 0;
    //const pid_t pid = getpid();
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    printf("hello world (pid:%d)\n", (int)getpid());
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
        close(fd[0]);
        //printf("hello, i am child (pid:%d)\n", (int) getpid());
        struct timeval t;
        gettimeofday(&t, NULL);
        write(fd[1], &t, sizeof(struct timeval));
        exit(0);
    }
    else
    {
        close(fd[1]);
        //printf("hello, i am parent of %d (pid:%d)\n", rc, (int) getpid());
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