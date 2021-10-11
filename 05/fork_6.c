#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
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
        int waitpid_rc = waitpid(-1, NULL, 0); // (wait for any child -1, info status in NULL, option 0)
        printf("Return Childprocess: %d\n", waitpid_rc);
    }
    else
    {
        printf("Parentprocess: %d\n", (int)getpid());
        int waitpid_rc = waitpid(-1, NULL, 0); // (wait for any child -1, info status in NULL, option 0)
        printf("Return Parentprocess: %d\n", waitpid_rc);
    }
    return 0;
}
