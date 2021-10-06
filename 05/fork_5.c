#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int fork_rc = fork();
    if (fork_rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (fork_rc == 0)
    {
        printf("Childprocess: %d\n", (int)getpid());
        int wait_rc = wait(NULL);
        printf("Return Childprocess: %d\n", wait_rc);
    }
    else
    {
        printf("Parentprocess: %d\n", (int)getpid());
        int wait_rc = wait(NULL);
        printf("Return Parentprocess: %d\n", wait_rc);
    }
    return 0;
}