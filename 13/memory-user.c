#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    printf("pid: %d\n", getpid());

    int memory;
    int *array;

    if (argc != 2)
    {
        fprintf(stderr, "use: ./memory-user MB\n");
        exit(1);
    }

    memory = atoi(argv[1]);
    array = malloc(memory);

    while (1)
    {
        for (int i = 0; i < memory; i++)
        {
            array[i] += 1;
        }
    }
    free(array);
    return 0;
}