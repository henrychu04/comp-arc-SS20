#include <stdio.h>
#include <stdlib.h>

double **transpose(double **transposed, double **matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

double **multiply(double **multiplied, double **matrix1, double **matrix2, int rows1, int columns1, int rows2, int columns2)
{
    int columnCount = 0;
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < columns2; j++)
        {
            double adding = 0;
            columnCount = 0;
            for (int k = 0; k < rows2; k++)
            {
                adding += matrix1[i][columnCount] * matrix2[k][j];
                columnCount++;
            }
            multiplied[i][j] = adding;
        }
    }

    return multiplied;
}

double **inverse(double **inversed, double **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            inversed[i][j] = matrix[i][j];
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = rows; j < rows * 2; j++)
        {
            if (j == (i + rows))
            {
                inversed[i][j] = 1;
            }
            else
            {
                inversed[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (i != j)
            {
                double ratio = inversed[j][i] / inversed[i][i];
                for (int k = 0; k < 2 * rows; k++)
                {
                    inversed[j][k] = inversed[j][k] - ratio * inversed[i][k];
                }
            }
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = rows; j < 2 * rows; j++)
        {
            inversed[i][j] = inversed[i][j] / inversed[i][i];
        }
    }

    return inversed;
}

int main(int argc, char *argv[])
{
    FILE *fp;

    fp = fopen(argv[1], "r");

    if (fp == NULL)
        return 0;

    int columns, rows;
    fscanf(fp, "%d\n%d", &columns, &rows);

    double **matrixX = (double **)malloc(sizeof(double *) * (rows));
    double **matrixY = (double **)malloc(sizeof(double *) * (rows));
    double **transposed = (double **)malloc(sizeof(double *) * (columns + 1));
    double **multiplied = (double **)malloc(sizeof(double *) * (columns + 1));
    double **inversed = (double **)malloc(sizeof(double *) * (columns + 1));
    double **inverseEdited = (double **)malloc(sizeof(double *) * (columns + 1));
    double **next = (double **)malloc(sizeof(double *) * (columns + 1));
    double **weight = (double **)malloc(sizeof(double *) * (columns + 1));

    for (int i = 0; i < rows; i++)
    {
        matrixX[i] = malloc((columns + 1) * sizeof(double));
        matrixY[i] = malloc(sizeof(double));
    }

    for (int i = 0; i < columns + 1; i++)
    {
        transposed[i] = malloc((rows) * sizeof(double));
        multiplied[i] = malloc((columns + 1) * sizeof(double));
        inversed[i] = malloc((columns + 1) * 2 * sizeof(double));
        inverseEdited[i] = malloc((columns + 1) * sizeof(double));
        next[i] = malloc((rows) * sizeof(double));
        weight[i] = malloc(sizeof(double));
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns + 2; j++)
        {
            if (j == 0)
            {
                matrixX[i][j] = 1;
            }
            else
            {
                double temp;
                fscanf(fp, "%lf,", &temp);
                if (j == 1)
                {
                    matrixY[i][0] = temp;
                    continue;
                }
                else
                {
                    matrixX[i][j - 1] = temp;
                }
            }
        }
    }

    transposed = transpose(transposed, matrixX, rows, columns + 1);

    multiplied = multiply(multiplied, transposed, matrixX, columns + 1, rows, rows, columns + 1);

    inversed = inverse(inversed, multiplied, columns + 1);

    for (int i = 0; i < columns + 1; i++)
    {
        for (int j = columns + 1; j < (columns + 1) * 2; j++)
        {
            inverseEdited[i][j - columns - 1] = inversed[i][j];
        }
    }

    next = multiply(next, inverseEdited, transposed, columns + 1, columns + 1, columns + 1, rows);

    weight = multiply(weight, next, matrixY, columns + 1, rows, rows, 1);

    fp = fopen(argv[2], "r");

    int num;

    fscanf(fp, "%d", &num);

    if (fp == NULL)
        return 0;

    double ans;

    for (int i = 0; i < num; i++)
    {
        ans = weight[0][0];
        for (int j = 0; j < columns; j++)
        {
            double temp = 0;
            fscanf(fp, "%lf,", &temp);
            ans += (weight[j + 1][0] * temp);
        }
        printf("%0.0lf\n", ans);
    }

    // freeing matrices

    for (int i = 0; i < rows; i++)
    {
        free(matrixX[i]);
        free(matrixY[i]);
    }

    for (int i = 0; i < columns + 1; i++)
    {
        free(transposed[i]);
        free(multiplied[i]);
        free(inversed[i]);
        free(inverseEdited[i]);
        free(next[i]);
        free(weight[i]);
    }

    free(matrixX);
    free(matrixY);
    free(transposed);
    free(multiplied);
    free(inversed);
    free(inverseEdited);
    free(next);
    free(weight);

    return 0;
}