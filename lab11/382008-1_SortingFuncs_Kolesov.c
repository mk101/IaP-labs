#include "382008-1_SortingFuncs_Kolesov.h"
#include <limits.h>
#include <stdio.h>
#include <omp.h>

void selection(int* a, int len, int* csr, int* cper, double* tm) {
	double st = 0, end = 0;
	int min = INT_MAX;
	int imin = -1;
	int k = 0, ik = 0;
	st = omp_get_wtime();
	printf("Сортировка выбором");
	for (int i = 0; i < len - 1; i++) {
		min = INT_MAX;
		imin = -1;
		for (int j = i; j < len; j++) {
			(*csr)++;
			if (a[j] < min) {
				imin = j;
				min = a[j];
			}
		}
		(*cper)++;
		k = a[i];
		a[i] = min;
		a[imin] = k;
	}
	end = omp_get_wtime();
	*tm = end - st;
	printf("\rСортировка выбором...ОК\n");
}

void bubble(int* a, int len, int* csr, int* cper, double* tm) {
	int k = 0, ik = 0;
	double st = 0, end = 0;
	printf("Сортировка пузырьком");
	st = omp_get_wtime();
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - 1 - i; j++) {
			(*csr)++;
			if (a[j] > a[j + 1]) {
				(*cper)++;
				k = a[j];
				a[j] = a[j + 1];
				a[j + 1] = k;
			}
		}
	}
	end = omp_get_wtime();
	*tm = end - st;
	printf("\rСортировка пузырьком...ОК\n");
}

void insertion(int* a, int len, int* csr, int* cper, double* tm) {
	int j = 0, k = 0, ik = 0;
	double st = 0, end = 0;
	printf("Сортировка вставками");
	st = omp_get_wtime();
	for (int i = 1; i < len; i++) {
		j = i;
		while (j > 0 && a[j] < a[j - 1]) {
			(*csr)++;
			(*cper)++;
			k = a[j];
			a[j] = a[j - 1];
			a[j - 1] = k;
			j--;
		}
	}
	end = omp_get_wtime();
	*tm = end - st;
	printf("\rСортировка вставками...ОК\n");
}

void shaker(int* a, int len, int* csr, int* cper, double* tm) {
	double st = 0, end = 0;
	int left = 0, right = len - 1;
	int k = 0;

	printf("Шейкерная сортировка");
	st = omp_get_wtime();

	while (left <= right) {
		for (int i = right; i > left; i--) {
			(*csr)++;
			if (a[i - 1] > a[i]) {
				(*cper)++;
				k = a[i - 1];
				a[i - 1] = a[i];
				a[i] = k;
			}
		}
		left++;
		for (int i = left; i < right; ++i) {
			(*csr)++;
			if (a[i] > a[i + 1]) {
				(*cper)++;
				k = a[i + 1];
				a[i + 1] = a[i];
				a[i] = k;
			}
		}
		--right;
	}
	end = omp_get_wtime();
	*tm = end - st;
	printf("\rШейкерная сортировка...ОК\n");
}

void comb(int* a, int len, int* csr, int* cper, double* tm) {
	const double factor = 1.247;
	double step = len - 1;
	double st = 0, end = 0;
	int k = 0;
	printf("Сортировка расчёской");
	st = omp_get_wtime();
	while (step >= 1) {
		for (int i = 0; i + step < len; i++) {
			(*csr)++;
			if (a[i] > a[i + (int)step]) {
				(*cper)++;
				k = a[i + (int)step];
				a[i + (int)step] = a[i];
				a[i] = k;
			}
		}
		step /= factor;
	}
	end = omp_get_wtime();
	*tm = end - st;
	printf("\rСортировка расчёской...ОК\n");
}

void siftDown(int* a, int root, int bottom, int* csr, int* cper) {
	int maxChild = 0;
	int done = 0;
	int k = 0;

	(*csr)++;
	while ((root * 2 <= bottom) && !done) {
		(*csr)++;
		(*csr)++;
		if (root * 2 == bottom)
			maxChild = root * 2;
		else if (a[root * 2] > a[root * 2 + 1])
			maxChild = root * 2;
		else
			maxChild = root * 2 + 1;
		(*csr)++;
		if (a[root] < a[maxChild]) {
			(*cper)++;
			k = a[root];
			a[root] = a[maxChild];
			a[maxChild] = k;
			root = maxChild;
		}
		else
			done = 1;
	}
}

void heap(int* a, int len, int* csr, int* cper, double* tm) {
	double st = 0, end = 0;
	int k = 0;
	printf("Пирамидальная сортировка");
	st = omp_get_wtime();

	for (int i = (len / 2) - 1; i >= 0; i--) {
		siftDown(a, i, len - 1, csr, cper);
	}

	for (int i = len - 1; i >= 1; i--) {
		(*cper)++;
		k = a[0];
		a[0] = a[i];
		a[i] = k;
		siftDown(a, 0, i - 1, csr, cper);
	}

	end = omp_get_wtime();
	*tm = end - st;
	printf("\rПирамидальная сортировка...ОК\n");
}