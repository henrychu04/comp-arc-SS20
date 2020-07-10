#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short comp(unsigned short *x, int v)
{
    *x ^= 1 << v;
    return *x;
}

unsigned short set(unsigned short *x, int n, int v)
{
    if (v == 0)
    {
        *x &= ~(1 << n);
    }
    else if (v == 1)
    {
        *x |= 1 << n;
    }

    return *x;
}

void get(unsigned short *x, int n)
{
    int bit = (*x & (1 << n)) >> n;
    printf("%d\n", bit);
}

int main(int argc, char *argv[])
{
    FILE *fp;

    fp = fopen(argv[1], "r");

    if (fp == NULL)
        return 0;

    unsigned short *var = (unsigned short *)malloc(sizeof(unsigned short));

    fscanf(fp, "%hu", var);

    char command[10];
    int n, v;

    while (fscanf(fp, "%s\t%d\t%d", command, &n, &v) != EOF)
    {
        if (strcmp(command, "set") == 0)
        {
            *var = set(var, n, v);
            printf("%hu\n", *var);
        }
        else if (strcmp(command, "comp") == 0)
        {
            *var = comp(var, n);
            printf("%hu\n", *var);
        }
        else if (strcmp(command, "get") == 0)
        {
            get(var, n);
        }
    }

    fclose(fp);
    free(var);
}