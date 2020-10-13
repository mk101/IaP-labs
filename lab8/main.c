#include "io.c"
#include <locale.h>

#define ARRAY_LEN 100

void clear(int a[], int len) {
	for (int i = 0; i < len; i++) {
		a[i] = 0;
	}
}

void sort(int a[], int len) {
	int k = 0;
	for (int i = 0; i < len-1; i++) {
		for (int j = i + 1; j < len; j++) {
			if (a[i] > a[j]) {
				k = a[i];
				a[i] = a[j];
				a[j] = k;
			}
		}
	}
}

int dizunkchia(int a[], int lenA, int b[], int lenB, int res[]) {
	int lenRes = lenA + lenB;
	clear(res, lenRes);
	
	for (int i = 0; i < lenA; i++) {
		res[i] = a[i];
	}

	for (int i = 0; i < lenB; i++) {
		res[lenA + i] = b[i];
	}

	sort(res, lenRes);

	return lenRes;

}

int main() {
	int a[ARRAY_LEN], b[ARRAY_LEN], res[ARRAY_LEN];
	int n, m, len;

	setlocale(LC_CTYPE, "Russian");

	printf("Введите n: ");
	scanInt(&n, 0, ARRAY_LEN / 2);
	printf("Введите массив a: ");
	scanIntArray(a, n);
	printf("Введите m: ");
	scanInt(&m, 0, ARRAY_LEN / 2);
	printf("Введите массив b: ");
	scanIntArray(b, m);

	printf("Массив res: ");
	len = dizunkchia(a, n, b, m, res);
	printIntArray(res, len, ' ');
	printf("\n");
	return 0;
}
