#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void scanDouble(double* value, double start, double end) {
	do {
		scanf("%lf", value);
	} while ((*value) < start || (*value) > end);
}

void scanInt(int* value, int start, int end) {
	do {
		scanf("%d", value);
	} while ((*value) < start || (*value) > end);
}

void scanDoubleArray(double* a, int length) {
	for (int i = 0; i < length; i++) {
		scanf("%lf", &a[i]);
	}
}

void printDoubleArray(double* a, int length, char sufix) {
	for (int i = 0; i < length; i++) {
		printf("%lf%c", a[i], sufix);
	}
}

void scanIntArray(int* a, int length) {
	for (int i = 0; i < length; i++) {
		scanf("%d", &a[i]);
	}
}

void printIntArray(int* a, int length, char sufix) {
	for (int i = 0; i < length; i++) {
		printf("%d%c", a[i], sufix);
	}
}

void fillDoubleArray(double* a, int length, double start, double end) {
	srand((unsigned int)time(0));

	for (int i = 0; i < length; i++) {
		a[i] = (end - start) * ((double)rand() / RAND_MAX) + start;
	}
}

void fillIntArray(int* a, int length, int start, int end) {
	srand((unsigned int)time(0));

	for (int i = 0; i < length; i++) {
		a[i] = (int)((end - start) * ((double)rand() / RAND_MAX) + start);
	}
}
