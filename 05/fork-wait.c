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
        strcpy(buf, "hello");
        write(fd, buf, 6);
        close(fd);
    } else {
        // int rc_wait = wait(NULL);
        printf("Parentprocess: %d\n", (int)getpid());
        strcpy(buf, "goodbye");
        write(fd, buf, 8);
        close(fd);
    }
    return 0;
}
