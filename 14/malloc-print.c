#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int *data;
    data = malloc(sizeof(int) * 100);
    free(data);
    printf("%d\n", data[100]);
    return 0;
}