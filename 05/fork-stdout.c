#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fork_rc;
    int wait_rc;
    fork_rc = fork();
    if (fork_rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (fork_rc == 0) {
        printf("Childprocess: %d\n", (int)getpid());
        close(STDOUT_FILENO);
        printf("Test\n");
    } else {
        wait_rc = wait(NULL);
        printf("Parentprocess: %d\n", (int)getpid());
        if (wait_rc == -1) {
            printf("errno : %s\n", strerror(errno));
        }
    }
    return 0;
}