#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char buf[20];
    int fd = open("./file.txt", O_WRONLY);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("Childprocess: %d\n", (int)getpid());
        strcpy(buf, "Child writes");
        write(fd, buf, 13);
        close(fd);
    } else {
        printf("Parentprocess: %d\n", (int)getpid());
        strcpy(buf, "Parent writes");
        write(fd, buf, 14);
        close(fd);
    }
    return 0;
}
