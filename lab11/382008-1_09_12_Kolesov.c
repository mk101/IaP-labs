#include <stdio.h>
#include <locale.h>
#include "382008-1_ServiceFuncs_Kolesov.h"
#include "382008-1_SortingFuncs_Kolesov.h"

#define LEN 10000
typedef void(*sortFunc)(int*, int, int*, int*, double*);

#ifdef WIN32
#include <Windows.h>

void wait(unsigned int ms) {
	Sleep(ms);
}

#elif unix
#include <time.h>

void wait(unsigned int ms) {
	struct timespec ts;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;
	nanosleep(&ts, NULL);
}
#endif 

int testSort(int arr[], int count) {
	int min = arr[0];
	for (int i = 1; i < count; i++) {
		if (arr[i] < min)
			return i + 1;
		min = arr[i];
	}

	return 0;
}

void copy(int* from, int* to, int len) {
	for (int i = 0; i < len; i++) {
		to[i] = from[i];
	}
}

void test(sortFunc func, int* b, int n, const char* name) {
	int per = 0, sr = 0;
	double time = 0;
	int check = 0;
	func(b, n, &sr, &per, &time);
	wait(200);
	printf("Проверка");
	check = testSort(b, n);
	if (check == 0) {
		printf("\rПроверка...ОК\n");
		printf("%s: перестановок = %10d, время: %15.10lf\n", name, per, time);
	}
	else {
		printf("\rПроверка...Ошибка\nУпорядоченность нарушается на %d элементе", check + 1);
	}

}

int main() {
	int a[LEN], b[LEN];
	int n, left, right;

	setlocale(LC_CTYPE, "Russian");

	printf("Введите длину массива: ");
	scanf("%d", &n);
	printf("Введите левую границу значений массива: ");
	scanf("%d", &left);
	printf("Введите правую границу значений массива: ");
	scanf("%d", &right);
	printf("-----------------------------------------------------------------------------\n");
	fillIntArray(a, n, left, right);
	printf("Сгенерированный массив: ");
	printIntArray(a, n, ' ');
	printf("-----------------------------------------------------------------------------\n");
	test(selection, b, n, "Сортировка выбором");
	copy(a, b, n);
	test(bubble, b, n, "Сортировка пузырьком");
	copy(a, b, n);
	test(insertion, b, n, "Сортировка вставками");
	copy(a, b, n);
	test(shaker, b, n, "Шейкерная сортировка");
	copy(a, b, n);
	test(comb, b, n, "Сортировка расчёской");
	copy(a, b, n);
	test(heap, b, n, "Пирамидальная сортировка");

	return 0;
}