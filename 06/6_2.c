#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sched.h>
#include <time.h>

int main()
{
    cpu_set_t mask;
    CPU_ZERO(&mask);
	CPU_SET(0, &mask);
    struct timespec start, end;
    size_t tyield, loops = 1000000;
    int first_pipefd[2], second_pipefd[2];
    if (pipe(first_pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(second_pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        if(sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1){
            perror("sched_setaffinity");
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < loops; i++) {
            read(first_pipefd[0], NULL, 0);
            write(second_pipefd[1], NULL, 0);
        }
    }
    else
    {
        if(sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1){
            perror("sched_setaffinity");
            exit(EXIT_FAILURE);
        }
        clock_gettime(CLOCK_MONOTONIC, &start);
        for(size_t i = 0; i < loops; i++){
            write(first_pipefd[1], NULL, 0);
            read(second_pipefd[0], NULL, 0);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        tyield = (end.tv_sec + end.tv_nsec - start.tv_sec + start.tv_nsec)/loops;
        printf("%zu\n", tyield);
    }
    return 0;
}
