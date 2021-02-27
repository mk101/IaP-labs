#pragma once

#include <stdio.h>
#include <stdbool.h>

#ifdef WIN32

#define KEY_UP		72
#define KEY_DOWN	80
#define KEY_QUIT	113 // q
#define KEY_ENTER	13

#elif unix

#define KEY_UP		65
#define KEY_DOWN	66
#define KEY_QUIT	'q' // q
#define KEY_ENTER	'\n'

#endif

void scanDouble(double* value, double start, double end);
void scanInt(int* value, int start, int end);
void scanDoubleArray(double* a, int length);
void printDoubleArray(double* a, int length, char sufix);
void scanIntArray(int* a, int length);
void printIntArray(int* a, int length, char sufix);
void fillDoubleArray(double* a, int length, double start, double end);
void fillIntArray(int* a, int length, int start, int end);

// ui

void clear();
int getKey();
void setBufferedInput(bool enable); // for linux