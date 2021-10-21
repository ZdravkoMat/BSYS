#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int *data;
    data = malloc(sizeof(int)*100);
    data[100] = 0;
    free(data);
    return 0;
}
