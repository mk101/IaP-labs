#include "io.h"
#include <time.h>
#include <stdlib.h>

#ifdef WIN32
#include <conio.h>

void clear() {
	system("cls");
}

int getKey() {
	int ch = _getch();
	if (ch == 224) { // стрелки
		return _getch();
	}
	return ch;
}
void setBufferedInput(bool enable) {}
void clearBuf() {}
#elif unix
#include <termios.h>
#include <unistd.h>

void setBufferedInput(bool enable) {
	static bool enabled = true;
	static struct termios old;
	struct termios new;

	if (enable && !enabled) {
		tcsetattr(STDIN_FILENO, TCSANOW, &old);
		enabled = true;
	}
	else if (!enable && enabled) {
		tcgetattr(STDIN_FILENO, &new);
		old = new;
		new.c_lflag &= (~ICANON & ~ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &new);
		enabled = false;
	}
}

int getKey() {
	return getchar();
}

void clear() {
	system("clear");
}
void clearBuf() {
	int ch;
	do {
		ch = getchar();
	} while (ch != 10);
}
#else
#error Unsupported os
#endif



int __randInit = 0;
void initRandom() {
	if (__randInit) return;

	srand((unsigned int)time(0));
	__randInit = 1;
}

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
	initRandom();

	for (int i = 0; i < length; i++) {
		a[i] = (end - start) * ((double)rand() / RAND_MAX) + start;
	}
}

void fillIntArray(int* a, int length, int start, int end) {
	initRandom();

	for (int i = 0; i < length; i++) {
		a[i] = (int)((end - start) * ((double)rand() / RAND_MAX) + start);
	}
}
