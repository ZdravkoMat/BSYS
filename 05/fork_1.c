#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int x = 100;
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "Fork failed\n");
    }
    else if (rc == 0)
    {
        printf("child x before: %d\n", x);
        x += 10;
        printf("child x after: %d\n", x);
    }
    else
    {
        printf("parent x before: %d\n", x);
        x += 100;
        printf("parent x after: %d\n", x);
    }
    return 0;
}
