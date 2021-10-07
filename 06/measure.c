#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

int main()
{
    int file = open("./file.txt", O_WRONLY);
    int loops = 1000000;

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (size_t i = 0; i < loops; i++)
    {
        read(file, NULL, 0);
    }
    gettimeofday(&end, NULL);
    printf("Systemcall: %f micro seconds\n", (float)(end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec) / loops);
    close(file);
}