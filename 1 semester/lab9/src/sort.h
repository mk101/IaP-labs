#pragma once

#include <stdbool.h>

#define	SELECTION	0
#define	BUBBLE		1
#define	INSERTION	2
#define	SHAKER		3
#define COMB		4
#define HEAP		5

#define SORTS_COUNT	6

const char* getName(int s);

void selection(int* a, int len, int* csr, int* cper, double* tm);
void bubble(int* a, int len, int* csr, int* cper, double* tm);
void insertion(int* a, int len, int* csr, int* cper, double* tm);

void shaker(int* a, int len, int* csr, int* cper, double* tm);
void comb(int* a, int len, int* csr, int* cper, double* tm);
void heap(int* a, int len, int* csr, int* cper, double* tm);