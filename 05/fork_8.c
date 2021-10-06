#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BSIZE 100

int main(int argc, char **argv)
{
    int fildes[2];
    char buf[BSIZE];
    int status_pipe;
    ssize_t nbytes;
    status_pipe = pipe(fildes);
    if (status_pipe == -1)
    {
        fprintf(stderr, "Pipeerror\n");
        exit(1);
    }

    if (fork() < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (fork() == 0)
    {
        close(fildes[1]);                     /* Write end is unused */
        nbytes = read(fildes[0], buf, BSIZE); /* Get data from pipe */
        if (nbytes == -1)
        {
            fprintf(stderr, "Readerror\n");
            exit(1);
        }
        printf("read : %s", buf);
        /* At this point, a further read would see end of file ... */
        close(fildes[0]); /* Finished with pipe */
        exit(EXIT_SUCCESS);
    }
    else
    {                                          /* Parent - writes to pipe */
        close(fildes[0]);                      /* Read end is unused */
        write(fildes[1], "Hello world\n", 12); /* Write data on pipe */
        close(fildes[1]);                      /* Child will see EOF */
        exit(EXIT_SUCCESS);
    }
    return 0;
}