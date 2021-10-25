#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int *data;
    data = (int *)malloc(sizeof(int) * 100);
    free(&data[50]);
    printf("%d\n", data[50]);
    return 0;
}
