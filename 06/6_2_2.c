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
    int fd[2], fd2[2];
    int loops = 1000000;
    struct timeval start, end;

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
	CPU_SET(0, &mask);
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask) == -1)
        {

        }
        for(int i = 0; i < loops; i++){
            read(fd[0], NULL, 0);
            write(fd2[1], NULL, 0);
        }
    }
    else
    {
	CPU_SET(0, &mask);
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask) == -1)
        {

        }
        gettimeofday(&start, NULL);
        for(int i = 0; i < loops; i++){
            write(fd2[1], NULL, 0);
            read(fd[0], NULL, 0);
        }
        gettimeofday(&end, NULL);
        printf("%f ms\n", (float)(end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec) / loops);
    }
    return 0;
}
