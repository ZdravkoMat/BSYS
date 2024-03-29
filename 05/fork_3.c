#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("Childprocess: %d\n", (int)getpid());
        printf("hello\n");
    }
    else
    {
        int rc_wait = wait(NULL);
        printf("Parentprocess: %d\n", (int)getpid());
        printf("goodbye %d\n", rc_wait);
    }
    return 0;
}
