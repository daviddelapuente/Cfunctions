#include <stdint.h>
void printA(int (*A)[4], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= 3; j++)
        {
            printf("%i ", A[i][j]);
        }
        printf("\n");
    }
}

void printArray(uint16_t *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%i ", A[i]);
    }
    printf("\n");
}

void shift1(int (*A)[4], int n, int i, int j)
{
    int actualPos = 4 * i + j;
    for (int i2 = actualPos; i2 < (4 * n) - 1; i2++)
    {
        int newPos = i2 + 1;
        int iaux = newPos / 4;
        int jaux = newPos % 4;
        A[i2 / 4][i2 % 4] = A[iaux][jaux];
    }
    A[n - 1][3] = 0;
}

void deleteOn2(int (*A)[4], int n)
{
    int c = 4 * n;
    int i = 0;
    while (c)
    {
        if (A[i / 4][i % 4] == 0)
        {
            shift1(A, n, i / 4, i % 4);
        }
        else
        {
            i++;
        }
        c--;
    }
}

void deleteOn(int (*A)[4], int n)
{
    int zeroIndex = 0;
    for (int actualIndex = 0; actualIndex < 4 * n; actualIndex++)
    {
        if (A[actualIndex / 4][actualIndex % 4] != 0)
        {
            int aux = A[actualIndex / 4][actualIndex % 4];
            A[actualIndex / 4][actualIndex % 4] = A[zeroIndex / 4][zeroIndex % 4];
            A[zeroIndex / 4][zeroIndex % 4] = aux;
            zeroIndex++;
        }
    }
}

uint16_t table[4] = {0x0fff, 0xf0ff, 0xff0f, 0xfff0};

void deleteZeros16Bits(uint16_t *A, int n)
{
    int zeroIndex = 0;
    for (int actualIndex = 0; actualIndex < 4 * n; actualIndex++)
    {
        uint16_t actualNumber = A[actualIndex / 4];
        actualNumber <<= (actualIndex % 4) * 4;
        actualNumber >>= 3 * 4;
        if (actualNumber != 0)
        {
            uint16_t aux = actualNumber;
            uint16_t zeroAux = A[zeroIndex / 4];
            zeroAux <<= (zeroIndex % 4) * 4;
            zeroAux >>= 3 * 4;

            A[actualIndex / 4] = A[actualIndex / 4] & table[actualIndex % 4] | (zeroAux << (4 * (3 - (actualIndex % 4))));
            A[zeroIndex / 4] = A[zeroIndex / 4] & table[zeroIndex % 4] | (aux << (4 * (3 - (zeroIndex % 4))));
            zeroIndex++;
        }
    }
}