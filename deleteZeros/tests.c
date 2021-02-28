#include <assert.h>
#include <stdio.h>
#include "deleteZeros.c"

void assertMatrixEqual(int (*A1)[4], int (*A2)[4], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= 3; j++)
        {
            assert(A1[i][j] == A2[i][j]);
        }
    }
}

void assertArrayEqual(uint16_t *A1, uint16_t *A2, int n)
{
    for (int i = 0; i < n; i++)
    {
        assert(A1[i] == A2[i]);
    }
}

void testShift1()
{
    int A[2][4] = {{1, 2, 3, 0}, {1, 0, 3, 4}};
    shift1(A, 2, 1, 1);
    int Ar[2][4] = {{1, 2, 3, 0}, {1, 3, 4, 0}};
    assertMatrixEqual(A, Ar, 2);
    shift1(A, 2, 0, 3);
    int Ar2[2][4] = {{1, 2, 3, 1}, {3, 4, 0, 0}};

    int A2[3][4] = {{0, 2, 3, 4}, {1, 0, 0, 4}, {0, 2, 0, 4}};
    shift1(A2, 3, 2, 2);
    int A2r[3][4] = {{0, 2, 3, 4}, {1, 0, 0, 4}, {0, 2, 4, 0}};
    assertMatrixEqual(A2, A2r, 3);
    shift1(A2, 3, 2, 3);
    assertMatrixEqual(A2, A2r, 3);
    shift1(A2, 3, 2, 0);
    int A2r2[3][4] = {{0, 2, 3, 4}, {1, 0, 0, 4}, {2, 4, 0, 0}};
    assertMatrixEqual(A2, A2r2, 3);
    shift1(A2, 3, 1, 2);
    int A2r3[3][4] = {{0, 2, 3, 4}, {1, 0, 4, 2}, {4, 0, 0, 0}};
    assertMatrixEqual(A2, A2r3, 3);
    shift1(A2, 3, 1, 1);
    int A2r4[3][4] = {{0, 2, 3, 4}, {1, 4, 2, 4}, {0, 0, 0, 0}};
    assertMatrixEqual(A2, A2r4, 3);
    shift1(A2, 3, 0, 0);
    int A2r5[3][4] = {{2, 3, 4, 1}, {4, 2, 4, 0}, {0, 0, 0, 0}};
    assertMatrixEqual(A2, A2r5, 3);
}

void testDeleteO2n()
{
    int A[1][4] = {{0, 0, 3, 0}};
    deleteOn2(A, 1);
    int Ar[1][4] = {{3, 0, 0, 0}};
    assertMatrixEqual(A, Ar, 1);

    int A2[1][4] = {{3, 0, 3, 0}};
    deleteOn2(A2, 1);
    int A2r[1][4] = {{3, 3, 0, 0}};
    assertMatrixEqual(A2, A2r, 1);

    int A3[1][4] = {{0, 0, 0, 0}};
    deleteOn2(A3, 1);
    int A3r[1][4] = {{0, 0, 0, 0}};
    assertMatrixEqual(A3, A3r, 1);

    int A4[2][4] = {{0, 0, 0, 0}, {1, 2, 0, 4}};
    deleteOn2(A4, 2);
    int A4r[2][4] = {{1, 2, 4, 0}, {0, 0, 0, 0}};
    assertMatrixEqual(A4, A4r, 2);

    int A5[4][4] = {{0, 0, 3, 1}, {1, 2, 3, 4}, {3, 0, 3, 0}, {1, 2, 3, 4}};
    deleteOn2(A5, 4);
    int A5r[4][4] = {{3, 1, 1, 2}, {3, 4, 3, 3}, {1, 2, 3, 4}, {0, 0, 0, 0}};
    assertMatrixEqual(A5, A5r, 4);

    int A6[4][4] = {{0, 0, 0, 1}, {1, 0, 0, 4}, {0, 0, 3, 0}, {0, 0, 0, 4}};
    deleteOn2(A6, 4);
    int A6r[4][4] = {{1, 1, 4, 3}, {4, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    assertMatrixEqual(A6, A6r, 4);
}

void testDeleteOn()
{
    int A[1][4] = {{1, 2, 3, 4}};
    deleteOn(A, 1);
    int Ar[1][4] = {{1, 2, 3, 4}};
    assertMatrixEqual(A, Ar, 1);

    int A2[2][4] = {{1, 2, 3, 4}, {1, 1, 1, 1}};
    deleteOn(A2, 2);
    int A2r[2][4] = {{1, 2, 3, 4}, {1, 1, 1, 1}};
    assertMatrixEqual(A2, A2r, 2);

    int A3[4][4] = {{0, 0, 3, 1}, {1, 2, 3, 4}, {3, 0, 3, 0}, {1, 2, 3, 4}};
    deleteOn(A3, 4);
    int A3r[4][4] = {{3, 1, 1, 2}, {3, 4, 3, 3}, {1, 2, 3, 4}, {0, 0, 0, 0}};
    assertMatrixEqual(A3, A3r, 4);

    int A4[4][4] = {{0, 0, 0, 1}, {1, 0, 0, 4}, {0, 0, 3, 0}, {0, 0, 0, 4}};
    deleteOn(A4, 4);
    int A4r[4][4] = {{1, 1, 4, 3}, {4, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    assertMatrixEqual(A4, A4r, 4);

    int A5[5][4] = {{0, 1, 0, 1}, {0, 1, 2, 0}, {1, 2, 3, 4}, {1, 2, 0, 1}, {1, 0, 0, 1}};
    deleteOn(A5, 5);
    int A5r[5][4] = {{1, 1, 1, 2}, {1, 2, 3, 4}, {1, 2, 1, 1}, {1, 0, 0, 0}, {0, 0, 0, 0}};
    assertMatrixEqual(A5, A5r, 5);
}

void testDeleteZeros16Bits()
{
    uint16_t A[1] = {0xffff};
    deleteZeros16Bits(A, 1);
    uint16_t Ar[1] = {0xffff};
    assertArrayEqual(A, Ar, 1);

    uint16_t A2[1] = {0xff0f};
    deleteZeros16Bits(A2, 1);
    uint16_t A2r[1] = {0xfff0};
    assertArrayEqual(A2, A2r, 1);

    uint16_t A3[1] = {0x0a03};
    deleteZeros16Bits(A3, 1);
    uint16_t A3r[1] = {0xa300};
    assertArrayEqual(A3, A3r, 1);

    uint16_t A4[3] = {0xf003, 0xaab0, 0x00bd};
    deleteZeros16Bits(A4, 3);
    uint16_t A4r[3] = {0xf3aa, 0xbbd0, 0x0000};
    assertArrayEqual(A4, A4r, 3);

    uint16_t A5[3] = {0x0000, 0x0000, 0x0bd0};
    deleteZeros16Bits(A5, 3);
    uint16_t A5r[3] = {0xbd00, 0x0000, 0x0000};
    assertArrayEqual(A5, A5r, 3);
}

void runTests()
{
    printf("begin tests\n");
    testShift1();
    testDeleteO2n();
    testDeleteOn();
    testDeleteZeros16Bits();
    printf("congrats all tests passed\n");
}
