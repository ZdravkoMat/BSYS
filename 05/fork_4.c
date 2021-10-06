#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("Childprocess");
        //execl("/bin/ls", "ls");
        //execle("/bin/ls", "ls");
        //execlp("/bin/ls", "ls");
        //execv("/bin/ls", "ls"); //help
        //execvp("/bin/ls", "ls"); //help
        //execvpe("/bin/ls", "ls"); //help
    }
    else
    {
        wait(NULL);
        printf("Parentprocess");
    }
    return 0;
}