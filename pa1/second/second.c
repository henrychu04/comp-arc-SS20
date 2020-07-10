#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
} node;

struct node *array[10000];

void *insert(int key, int value)
{
    node *newptr = (node *)malloc(sizeof(node));

    if (newptr == NULL)
    {
        return NULL;
    }

    newptr->value = value;
    newptr->next = NULL;

    if (array[key] == NULL)
    {
        array[key] = newptr;
        printf("inserted\n");
        return newptr;
    }
    else
    {
        node *prev = array[key];

        while (1)
        {
            if (prev->value == value)
            {
                printf("duplicate\n");
                return NULL;
            }
            else if (prev->next == NULL)
            {
                prev->next = newptr;
                printf("inserted\n");
                return newptr;
            }

            prev = prev->next;
        }
    }
}

int hash(int value)
{
    int key = value % 10000;

    if (key < 0)
    {
        key *= -1;
    }

    return key;
}

void search(int buffer)
{
    int key = hash(buffer);

    if (array[key] == NULL)
    {
        printf("absent\n");
    }
    else
    {
        node *newptr = array[key];

        while (1)
        {
            if (newptr == NULL)
            {
                printf("absent\n");
                break;
            }
            else if (newptr->value == buffer)
            {
                printf("present\n");
                break;
            }

            newptr = newptr->next;
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;

    fp = fopen(argv[1], "r");

    if (fp == NULL)
        return 0;

    char c;
    int value;
    int *keys[10000];
    int j = 0;

    while (fscanf(fp, "%c\t%d\n", &c, &value) != EOF)
    {
        if (c == 'i')
        {
            int key = hash(value);
            int *result = insert(key, value);

            if (result != NULL)
            {
                keys[j] = result;
                j++;
            }
        }
        else if (c == 's')
        {
            search(value);
        }
    }

    fclose(fp);

    // freeing memory

    for (int i = 0; i < 10000; i++)
    {
        if (keys[i] == NULL)
        {
            break;
        }

        int *address = keys[i];

        free(address);
    }

    return 0;
}