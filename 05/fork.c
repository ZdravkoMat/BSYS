#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int x = 100;
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "Fork failed\n");
    } else if (rc == 0) {
        printf("Childprocess: %d\n", (int)getpid());
        // This child process will have its own copy of x
        printf("child x before: %d\n", x);
        x += 10;
        printf("child x after: %d\n", x);
    } else {
        wait(NULL);
        printf("Parentprocess: %d\n", (int)getpid());
        printf("parent x before: %d\n", x);
        x += 10;
        printf("parent x after: %d\n", x);
    }
    return 0;
}