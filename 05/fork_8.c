#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{

    if (fork() < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (fork() == 0)
    {

    }
    else
    {
        
    }
    return 0;
}