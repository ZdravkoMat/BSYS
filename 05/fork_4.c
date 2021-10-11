#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    char *const parm[] = {"/bin/ls", "-l", "/home/zdravko/Desktop/BSYS/05", NULL};
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("Childprocess\n");
        //execl("/bin/ls", "ls -l");
        //execle("/bin/ls", "ls -a");
        //execlp("/bin/ls", "ls");
        //execv("/bin/ls", parm);
        execvp("/bin/ls", parm);
        //execvpe("/bin/ls", parm); //help
    }
    else
    {
        wait(NULL);
        printf("Parentprocess\n");
    }
    return 0;
}
