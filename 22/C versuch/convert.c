#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 80
#define VPN_MASK 0xFFFFF000

int main(){

    char line[MAX_LINE_LENGTH] = {0};

    FILE *fp = fopen("./clean.txt", "r");
    //FILE *sf = fopen("./vpn.txt", "w");

    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        // VPN = (value % mask) >> 12
    }
}
