#include "io.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

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
	struct termios _new;

	if (enable && !enabled) {
		tcsetattr(STDIN_FILENO, TCSANOW, &old);
		enabled = true;
	}
	else if (!enable && enabled) {
		tcgetattr(STDIN_FILENO, &_new);
		old = _new;
		_new.c_lflag &= (~ICANON & ~ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &_new);
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

void printFor(char ch, int time) {
    for (int i = 0; i < time; i++) {
        printf("%c", ch);
    }
}

void listToFile(const List* list, const char* fileName) {
    int k = 0;
	FILE* file = fopen(fileName, "wb");
	ListEntry* entry = NULL;
	ListEntry* entries = (ListEntry*)malloc(list->size * sizeof(ListEntry));

	if (list->size == 0) {
		fclose(file);
		return;
	}

	entry = list->body;
	entries[k++] = *entry;
	for (int i = 1; i < list->size; i++) {
		entry = entry->next;
		entries[k++] = *entry;
	}

	fwrite(&list->size, sizeof(list->size), 1, file);
	fwrite(entries, sizeof(ListEntry), list->size, file);

	free(entries);
	fclose(file);
}

void listFromFile(List* list, const char* fileName) {
	uint size;
	ListEntry* entries;
	ListEntry *e = NULL, *nxt = NULL;
	FILE* file = fopen(fileName, "rb");
	
	if (file == NULL) 
		return;
	
	fread(&size, sizeof(size), 1, file);
	entries = (ListEntry*)malloc(size*sizeof(ListEntry));
	fread(entries, sizeof(ListEntry), size, file);
	
	list->size = size;
	list->body = (ListEntry*)malloc(sizeof(ListEntry));
	list->body->date = entries[0].date;
	strcpy(list->body->name, entries[0].name);
	strcpy(list->body->value, entries[0].value);
	list->body->next = NULL;
	e = list->body;
	for (int i = 1; i < size; i++) {
		nxt = (ListEntry*)malloc(sizeof(ListEntry));
		nxt->date = entries[i].date;
		strcpy(nxt->name, entries[i].name);
		strcpy(nxt->value, entries[i].value);
		nxt->next = NULL;
		e->next = nxt;
		e = nxt;
	}
	free(entries);
	fclose(file);
}
