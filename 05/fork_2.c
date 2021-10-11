#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    FILE *fp;
    fp = fopen("./file.txt", "w");
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("Childprocess: %d\n", (int)getpid());
        fprintf(fp, "%s", "Child writes\n");
        fclose(fp);
    }
    else
    {
        printf("Parentprocess: %d\n", (int)getpid());
        fprintf(fp, "%s", "Parent writes\n");
        fclose(fp);
    }
    return 0;
}
