#pragma once

void scanDouble(double* value, double start, double end);
void scanInt(int* value, int start, int end);
void scanDoubleArray(double* a, int length);
void printDoubleArray(double* a, int length, char sufix);
void scanIntArray(int* a, int length);
void printIntArray(int* a, int length, char sufix);
void fillDoubleArray(double* a, int length, double start, double end);
void fillIntArray(int* a, int length, int start, int end);

void scanIntMatrix(int** a, int m, int n);
void printIntMatrix(int** a, int m, int n);