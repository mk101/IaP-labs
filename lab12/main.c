#include <stdio.h>
#include <stdlib.h>

#include "io.h"

// ====Lab 5====

int getSign(int n) {
    return n >= 0 ? 1 : -1;
}

int signCount(int* a, int len) {
    int count = 0, curSign = getSign(a[0]);
    for (int i = 1; i < len; i++) {
        if (getSign(a[i]) != curSign) {
            count++;
            curSign = getSign(a[i]);
        }
    }
    return count;
}

// ====Lab 6====

int unite(int* a, int lenA, int* b, int lenB, int* res) {
    int i = 0, j = 0, k = 0;
    int len = lenA + lenB;

    while (i < len) {
        if (j < lenA && k < lenB) {
            if (a[j] < b[k]) {
                res[i++] = a[j++];
            } else {
                res[i++] = b[k++];
            }
        } else {
            if (j < lenA) {
                res[i++] = a[j++];
            } else {
                res[i++] = b[k++];
            }
        }
    }

    return len;
}

// ====Lab 12====

void transpose(int** a, int n, int** res) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[j][i] = a[i][j];
        }
    }
}

int main() {
    int *a, *b, *res;
    int lenA, lenB, lenRes;
    int **matrix, **matrixT;
    int n;
    printf("====Lab 5====\n");
    printf("Input array length: ");
    scanInt(&lenA, 1, 20);
    a = (int*)malloc(lenA * sizeof(int));
    printf("Input array: ");
    scanIntArray(a, lenA);
    printf("Sign change count: %d\n", signCount(a, lenA));
    free(a);

    printf("====Lab 6====\n");
    printf("Input first array length: ");
    scanInt(&lenA, 1, 20);
    a = (int*)malloc(lenA * sizeof(int));
    printf("Input first array: ");
    scanIntArray(a, lenA);

    printf("Input second array length: ");
    scanInt(&lenB, 1, 20);
    b = (int*)malloc(lenB * sizeof(int));
    printf("Input second array: ");
    scanIntArray(b, lenB);
    res = (int*)malloc((lenA + lenB)*sizeof(int));
    printf("United array: ");
    lenRes = unite(a, lenA, b, lenB, res);
    printIntArray(res, lenRes, ' ');
    printf("\n");

    free(a);
    free(b);
    free(res);
    printf("====Lab 12====\n");
    matrix = (int**)malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n*sizeof(int));
    }
    matrixT = (int**)malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrixT[i] = (int*)malloc(n*sizeof(int));
    }

    printf("Input n: ");
    scanInt(&n, 1, 100);
    printf("Input matrix %d*%d\n", n, n);
    scanIntMatrix(matrix, n, n);
    transpose(matrix, n, matrixT);
    printf("Transposed matrix:\n");
    printIntMatrix(matrixT, n, n);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    for (int i = 0; i < n; i++) {
        free(matrixT[i]);
    }
    free(matrixT);
    return 0;
}
