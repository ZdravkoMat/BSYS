#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int *data;
    data = malloc(sizeof(int)*100);
    data[100] = 0;
    //printf("x: %d\n", *data);
    return 0;
}