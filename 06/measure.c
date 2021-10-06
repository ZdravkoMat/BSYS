#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

int main(){
    int fd = open("./1.txt", O_WRONLY), n = 1000000;

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (size_t i = 0; i < n; i++) {
        read(fd, NULL, 0);
    }
    gettimeofday(&end, NULL);
    printf("Systemcall: %f micro seconds\n", (float) (end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec)/n);
    close(fd);
}