#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int *data;
    data = malloc(sizeof(int) * 100);
    free(data);
    printf("%d\n", data[50]);
    return 0;
}
