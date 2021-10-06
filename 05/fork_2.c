#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h> //strcpy

int main(int argc, char **argv)
{
    char buf[14];
    int fd = open("./file.txt", O_WRONLY); //open for write only
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("Childprocess: %d\n", (int)getpid());
        strcpy(buf, "Child writes\n");
        write(fd, buf, 13);
        close(fd);
    }
    else
    {
        printf("Parentprocess: %d\n", (int)getpid());
        strcpy(buf, "Parent writes\n");
        write(fd, buf, 14);
        close(fd);
    }
    return 0;
}
