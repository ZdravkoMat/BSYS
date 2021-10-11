#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
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
        close(fd[0]); // closes up input side
        printf("test\n");
        close(fd[1]); // closes up output side
    }
    else
    {
        close(fd[0]);
        printf("test2\n");
        close(fd[1]);
    }
    return 0;
}
