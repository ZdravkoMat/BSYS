#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int rc;
    int wait_rc;
    rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("Childprocess: %d\n", (int)getpid());
        close(STDOUT_FILENO);
        printf("Test\n");
    } else {
        wait_rc = wait(NULL);
        printf("Parentprocess: %d\n", (int)getpid());
    }
    return 0;
}