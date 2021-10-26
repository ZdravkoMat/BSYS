#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int *data;
    data = (int *)malloc(sizeof(int) * 100);
    data[0] = 43123;
    data[1] = 4314;
    data[2] = 6544;
    data[3] = 84674;

    int *b = &data[2];
    free(b);
    printf("%d\n", *b);
    return 0;
}
