#include <stdio.h>
#include <stdlib.h>

void merge(int *array, int left, int mid, int right)
{
    int temp[right - left + 1];

    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
    {
        if (array[i] <= array[j])
        {
            temp[k] = array[i];
            k += 1;
            i += 1;
        }
        else
        {
            temp[k] = array[j];
            k += 1;
            j += 1;
        }
    }

    while (i <= mid)
    {
        temp[k] = array[i];
        k += 1;
        i += 1;
    }

    while (j <= right)
    {
        temp[k] = array[j];
        k += 1;
        j += 1;
    }

    for (i = left; i <= right; i += 1)
    {
        array[i] = temp[i - left];
    }
}

void mergesort(int array[], int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;
        mergesort(array, left, middle);
        mergesort(array, middle + 1, right);

        merge(array, left, middle, right);
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;

    int arrayLength;

    fp = fopen(argv[1], "r");

    if (fp == NULL)
        return 0;

    fscanf(fp, "%d", &arrayLength);

    int array[arrayLength];

    for (int i = 0; i < arrayLength; i++)
    {
        fscanf(fp, "%d,", &array[i]);
    }

    fclose(fp);

    mergesort(array, 0, arrayLength - 1);

    int finalArray[arrayLength];
    int j = 0;

    for (int i = 0; i < arrayLength; i++)
    {
        if (array[i] % 2 != 0)
        {
            finalArray[j] = array[i];
            j++;
        }
    }

    for (int i = arrayLength - 1; i >= 0; i--)
    {
        if (array[i] % 2 == 0)
        {
            finalArray[j] = array[i];
            j++;
        }
    }

    for (int i = 0; i < arrayLength; i++)
    {
        printf("%d\t", finalArray[i]);
    }

    return 0;
}
