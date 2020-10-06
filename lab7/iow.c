#pragma once

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

// io.c но вместо pintf, scanf  printw и scanw

void scanDoublew(double* value, double start, double end) {
	do {
		scanw("%lf", value);
	} while ((*value) < start || (*value) > end);
}

void scanIntw(int* value, int start, int end) {
	do {
		scanw("%d", value);
	} while ((*value) < start || (*value) > end);
}

void scanDoubleArrayw(double* a, int length) {
	for (int i = 0; i < length; i++) {
		scanw("%lf", &a[i]);
	}
}

void printDoubleArrayw(double* a, int length, char sufix) {
	for (int i = 0; i < length; i++) {
		printw("%lf%c", a[i], sufix);
	}
}

void scanIntArrayw(int* a, int length) {
	for (int i = 0; i < length; i++) {
		scanw("%d", &a[i]);
	}
}

void printIntArrayw(int* a, int length, char sufix) {
	for (int i = 0; i < length; i++) {
		printw("%d%c", a[i], sufix);
	}
}

void fillDoubleArrayw(double* a, int length, double start, double end) {
	srand((unsigned int)time(0));

	for (int i = 0; i < length; i++) {
		a[i] = (end - start) * ((double)rand() / RAND_MAX) + start;
	}
}

void fillIntArrayw(int* a, int length, int start, int end) {
	srand((unsigned int)time(0));

	for (int i = 0; i < length; i++) {
		a[i] = (int)((end - start) * ((double)rand() / RAND_MAX) + start);
	}
}
