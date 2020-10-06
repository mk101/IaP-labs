#include <locale.h>
#include <float.h>
#include <limits.h>
#include <ncurses.h>
#include "io.c"
#include "iow.c"


#define ARRAY_LEN 	5
#define endl		printw("\n")

// #ifdef _WIN32
// #include <conio.h>
// void clear() {
//     system("cls");
// }
// #elif unix
// void clear() {
//     system("clear");
// }


// #endif

const char* getUi(int stage, int cursor) {
	if (stage == 0) {
		switch (cursor)
		{
			case 0: return "Тесты функций";
			case 1: return "Поиск в массиве";
			case 2: return "Сортировка массива";
			case 3: return "Выход";
			default: return "ERROR";
		}
	} else if (stage == 1) {
		switch (cursor)
		{
			case 0: return "Ввод действительного числа с контролем";
			case 1: return "Ввод целого числа с контролем";
			case 2: return "Ввод действительного массива";
			case 3: return "Вывод действительного массива";
			case 4: return "Ввод целочисленного массива";
			case 5: return "Вывод целочисленного массива";
			case 6: return "Генерация значений действительного массива";
			case 7: return "Генерация значений целочисленного массива";
			case 8: return "Назад";
			default: return "ERROR";
		}
	} else if (stage == 2) {
		switch (cursor)
		{
			case 0: return "Поиск номера максимального элемента действительного массива";
			case 1: return "Поиск номера максимального элемента целочисленного массива";
			case 2: return "Поиск номера минимального элемента действительного массива";
			case 3: return "Поиск номера минимального элемента целочисленного массива";
			case 4: return "Поиск номера заданного элемента действительного массива";
			case 5: return "Поиск номера заданного элемента целочисленного массива";
			case 6: return "Назад";
			default: return "ERROR";
		}
	} else if (stage == 3) {
		switch (cursor)
		{
			case 0: return "Сортировка элементов действительного массива";
			case 1: return "Сортировка элементов целочисленного массива";
			case 2: return "Назад";
			default: return "ERROR";
		}
	}
	else {
		return "ERROR";
	}
}

int getMaxCursor(int stage) {
	if (stage == 0) {
		return 3;
	} else if (stage == 1) {
		return 8;
	} else if (stage == 2) {
		return 6;
	} else if (stage == 3) {
		return 2;
	} else {
		return -1;
	}
}

void printCurStage(int stage, int cursor) {
    clear();
    int maxCursor = getMaxCursor(stage);
	for (int i = 0; i <= maxCursor; i++) {
		if (i != cursor) {
			printw("  ");
		} else {
			printw("> ");
		}
		// printf(ui[i][stage]);
		printw("%s", getUi(stage, i));
		endl;
	}
}

void inputDArray(double* a) {
	printw("Ввод действительного массива длиной %d: ", ARRAY_LEN);
	scanDoubleArrayw(a, ARRAY_LEN);
	printw("Результат: ");
	for (int i = 0; i < ARRAY_LEN; i++) {
		printw("%lf ", a[i]);
	}
	endl;
}

void inputIArray(int* a) {
	printw("Ввод целого массива длиной %d: ", ARRAY_LEN);
	scanIntArrayw(a, ARRAY_LEN);
	printw("Результат: ");
	for (int i = 0; i < ARRAY_LEN; i++) {
		printw("%d ", a[i]);
	}
	endl;
}

int main() {
    setlocale(LC_CTYPE, "");

    initscr();
	keypad(stdscr, true);
    int stage = 0; // 0 - home
                   // 1 - test
                   // 2 - search
                   // 3 - sort
                   // 4 - exit
    int cursor = 0;
    int key = -1;
	double* doubleArray = malloc(ARRAY_LEN*sizeof(*doubleArray));
	int* intArray = malloc(ARRAY_LEN*sizeof(*intArray));
    while (stage != 4) {
        printCurStage(stage, cursor);
        key = getch();
		if (key == KEY_DOWN && cursor < getMaxCursor(stage)) {
			cursor++;
		} else if (key == KEY_DOWN) {
			cursor = 0;
		} else if (key == KEY_UP && cursor != 0) {
			cursor--;
		} else if (key == KEY_UP) {
			cursor = getMaxCursor(stage);
		} else if (key == 10) {
			if (stage == 0) {
				switch(cursor) {
				case 0:
					stage = 1;
					cursor = 0;
					break;
				case 1:
					stage = 2;
					cursor = 0;
					break;
				case 2:
					stage = 3;
					cursor = 0;
					break;
				case 3:
					stage = 4;
					cursor = 0;
					break;
				}
			} else if (stage == 1) {
				switch(cursor) {
				case 0:
					clear();
					double testDouble = 0;
					printw("Ввод действительного числа[0,17.8]: ");
					scanDoublew(&testDouble, .0, 17.8);
					printw("Результат: %lf\n", testDouble);
					getch();
					break;
				case 1:
					clear();
					int testInt = 0;
					printw("Ввод целого числа[0,20]: ");
					scanIntw(&testInt, 0, 20);
					printw("Результат: %d\n", testInt);
					getch();
					break;
				case 2:
					clear();
					inputDArray(doubleArray);
					getch();
					break;
				case 3:
					clear();
					printw("Вывод действительного массива длиной %d: ", ARRAY_LEN);
					printDoubleArrayw(doubleArray, ARRAY_LEN, ' ');
					endl;
					getch();
					break;
				case 4:
					clear();
					inputIArray(intArray);
					getch();
					break;
				case 5:
					clear();
					printw("Вывод целого массива длиной %d: ", ARRAY_LEN);
					printIntArrayw(intArray, ARRAY_LEN, ' ');
					endl;
					getch();
					break;
				case 6:
					clear();
					double dstart = -2.2, dend = 42.42;
					printw("Заполнение действительного массива длиной %d в пределах [%lf,%lf]:\n", ARRAY_LEN, dstart, dend);
					fillDoubleArrayw(doubleArray, ARRAY_LEN, dstart, dend);
					printw("Результат: ");
					printDoubleArrayw(doubleArray, ARRAY_LEN, ' ');
					endl;
					getch();
					break;
				case 7:
					clear();
					int istart = -2, iend = 42;
					printw("Заполнение целого массива длиной %d в пределах [%d,%d]:\n", ARRAY_LEN, istart, iend);
					fillIntArrayw(intArray, ARRAY_LEN, istart, iend);
					printw("Результат: ");
					printIntArrayw(intArray, ARRAY_LEN, ' ');
					endl;
					getch();
					break;
				case 8:
					stage = 0;
					cursor = 0;
					break;
				}
			} else if (stage == 2) {
				switch(cursor) {
				case 0:
					clear();
					printw("Поиск номера максимального элемента действительного массива\n");
					inputDArray(doubleArray);
					double dmax = DBL_MIN;
					int dmaxi = -1;
					for (int i = 0; i < ARRAY_LEN; i++) {
						if (dmax < doubleArray[i]) {
							dmax = doubleArray[i];
							dmaxi = i;
						}
					}
					printw("Максимальный элемент действ. массива: %d\n", dmaxi);
					getch();
					break;
				case 1:
					clear();
					printw("Поиск номера максимального элемента целочисленного массива\n");
					inputIArray(intArray);
					int imax = INT_MIN;
					int imaxi = -1;
					for (int i = 0; i < ARRAY_LEN; i++) {
						if (imax < intArray[i]) {
							imax = intArray[i];
							imaxi = i;
						}
					}
					printw("Максимальный элемент цел. массива: %d\n", imaxi);
					getch();
					break;
				case 2:
					clear();
					printw("Поиск номера минимального элемента действительного массива\n");
					inputDArray(doubleArray);
					double dmin = DBL_MAX;
					int dmini = -1;
					for (int i = 0; i < ARRAY_LEN; i++) {
						if (dmin > doubleArray[i]) {
							dmin = doubleArray[i];
							dmini = i;
						}
					}
					printw("Минимальный элемент действ. массива: %d\n", dmini);
					getch();
					break;
				case 3:
					clear();
					printw("Поиск номера минимального элемента целочисленного массива\n");
					inputIArray(intArray);
					int imin = INT_MAX;
					int imini = -1;
					for (int i = 0; i < ARRAY_LEN; i++) {
						if (imin > intArray[i]) {
							imin = intArray[i];
							imini = i;
						}
					}
					printw("Минимальный элемент цел. массива: %d\n", imini);
					getch();
					break;
				case 4:
					clear();
					printw("Поиск номера заданного элемента действительного массива:\n");
					inputDArray(doubleArray);
					double ds = 0;
					int di = INT_MIN;
					printw("Искомое число: ");
					scanw("%lf", &ds);
					for (int i = 0; i < ARRAY_LEN; i++) {
						if (doubleArray[i] == ds) {
							di = i;
							break;
						}
					}
					if (di == DBL_MIN) printw("Элемент %lf не найден\n", ds);
					else			   printw("Номер эл. %d\n", di);
					getch();
					break;
				case 5:
					clear();
					printw("Поиск номера заданного элемента целочисленного массива:\n");
					inputIArray(intArray);
					int ii = INT_MIN, is = 0;
					printw("Искомое число: ");
					scanw("%d", &is);
					for (int i = 0; i < ARRAY_LEN; i++) {
						if (intArray[i] == is) {
							ii = i;
							break;
						}
					}
					if (ii == INT_MIN) printw("Элемент %d не найден\n", is);
					else			   printw("Номер эл. %d\n", ii);
					getch();
					break;
				case 6:
					stage = 0;
					cursor = 0;
					break;
				}
			} else if (stage == 3) {
				switch(cursor) {
				case 0:
					clear();
					printw("Сортировка элементов действительного массива:\n");
					inputDArray(doubleArray);
					for (int i = 0; i < ARRAY_LEN - 1; i++) {
						for (int j = i + 1; j < ARRAY_LEN; j++) {
							if (doubleArray[i] < doubleArray[j]) {
								double k = doubleArray[i];
								doubleArray[i] = doubleArray[j];
								doubleArray[j] = k;
							}
						}
					}
					printDoubleArrayw(doubleArray, ARRAY_LEN, ' ');
					endl;
					getch();
					break;
				case 1:
					clear();
					printw("Сортировка элементов целочисленного массива\n");
					inputIArray(intArray);
					for (int i = 0; i < ARRAY_LEN - 1; i++) {
						for (int j = i + 1; j < ARRAY_LEN; j++) {
							if (intArray[i] < intArray[j]) {
								int k = intArray[i];
								intArray[i] = intArray[j];
								intArray[j] = k;
							}
						}
					}
					printIntArrayw(intArray, ARRAY_LEN, ' ');
					endl;
					getch();
					break;
				case 2:
					stage = 0;
					cursor = 0;
					break;
				}
			}
		}
    }
	free(doubleArray);
	free(intArray);
	endwin();
    return 0;
}

// Тесты без интерфейса
void legacy() {
    
	double testDouble = 0;
	printf("Ввод действительного числа[0,17.8]: ");
	scanDouble(&testDouble, .0, 17.8);
	printf("Результат: %lf\n", testDouble);

	int testInt = 0;
	printf("Ввод целого числа[0,20]: ");
	scanInt(&testInt, 0, 20);
	printf("Результат: %d\n", testInt);

	double* doubleArray = malloc(ARRAY_LEN*sizeof(*doubleArray));
	printf("Ввод действительного массива длиной %d: ", ARRAY_LEN);
	scanDoubleArray(doubleArray, ARRAY_LEN);
	printf("Результат: ");
	for (int i = 0; i < ARRAY_LEN; i++) {
		printf("%lf ", doubleArray[i]);
	}
	printf("\n");

	printf("Вывод действительного массива длиной %d: ", ARRAY_LEN);
	printDoubleArray(doubleArray, ARRAY_LEN, ' ');
	
	printf("\n");

	int* intArray = malloc(ARRAY_LEN*sizeof(*intArray));
	printf("Ввод целого массива длиной %d: ", ARRAY_LEN);
	scanIntArray(intArray, ARRAY_LEN);
	printf("Результат: ");
	for (int i = 0; i < ARRAY_LEN; i++) {
		printf("%d ", intArray[i]);
	}
	printf("\n");

	printf("Вывод целого массива длиной %d: ", ARRAY_LEN);
	printIntArray(intArray, ARRAY_LEN, ' ');

	printf("\n");

	double dstart = -2.2, dend = 42.42;
	printf("Заполнение действительного массива длиной %d в пределах [%lf,%lf]: ", ARRAY_LEN, dstart, dend);
	fillDoubleArray(doubleArray, ARRAY_LEN, dstart, dend);
	printf("Результат: ");
	printDoubleArray(doubleArray, ARRAY_LEN, ' ');
	printf("\n");

	int istart = -2, iend = 42;
	printf("Заполнение целого массива длиной %d в пределах [%d,%d]: ", ARRAY_LEN, istart, iend);
	fillIntArray(intArray, ARRAY_LEN, istart, iend);
	printf("Результат: ");
	printIntArray(intArray, ARRAY_LEN, ' ');
	printf("\n\n");


	printf("Ввод действительного массива длиной %d: ", ARRAY_LEN);
	scanDoubleArray(doubleArray, ARRAY_LEN);

	double dmax = DBL_MIN, dmin = DBL_MAX;
	int dmaxi = -1, dmini = -1;
	for (int i = 0; i < ARRAY_LEN; i++) {
		if (dmax < doubleArray[i]) {
			dmax = doubleArray[i];
			dmaxi = i;
		}
		if (dmin > doubleArray[i]) {
			dmin = doubleArray[i];
			dmini = i;
		}
	}
	printf("Минимальный элемент действ. массива: %d\nМаксимальный элемент действ. массива: %d\n", dmini, dmaxi);

	int imax = INT_MIN, imin = INT_MAX;
	int imaxi = -1, imini = -1;
	for (int i = 0; i < ARRAY_LEN; i++) {
		if (imax < intArray[i]) {
			imax = intArray[i];
			imaxi = i;
		}
		if (imin > intArray[i]) {
			imin = intArray[i];
			imini = i;
		}
	}
	printf("Минимальный элемент цел. массива: %d\nМаксимальный элемент цел. массива: %d\n", imini, imaxi);

	printf("Поиск номера эл в действ. массиве: ");
	double ds = 0;
    int di = INT_MIN;
	scanDouble(&ds, -2.2, 42.42);
	for (int i = 0; i < ARRAY_LEN; i++) {
		if (doubleArray[i] == ds) {
			di = i;
			break;
		}
	}
	if (di == DBL_MIN) printf("Элемент %lf не найден\n", ds);
	else			   printf("Номер эл. %d\n", di);

	printf("Поиск номера эл в цел. массиве: ");
	int ii = INT_MIN, is = 0;
	scanInt(&is, -2, 42);
	for (int i = 0; i < ARRAY_LEN; i++) {
		if (intArray[i] == is) {
			ii = i;
			break;
		}
	}
	if (ii == INT_MIN) printf("Элемент %d не найден\n", is);
	else			   printf("Номер эл. %d\n", ii);

	printf("Сортировка действ. массива: ");
	for (int i = 0; i < ARRAY_LEN - 1; i++) {
		for (int j = i + 1; j < ARRAY_LEN; j++) {
			if (doubleArray[i] < doubleArray[j]) {
				double k = doubleArray[i];
				doubleArray[i] = doubleArray[j];
				doubleArray[j] = k;
			}
		}
	}
	printDoubleArray(doubleArray, ARRAY_LEN, ' ');
	printf("\n");

	printf("Сортировка цел. массива: ");
	for (int i = 0; i < ARRAY_LEN - 1; i++) {
		for (int j = i + 1; j < ARRAY_LEN; j++) {
			if (intArray[i] < intArray[j]) {
				int k = intArray[i];
				intArray[i] = intArray[j];
				intArray[j] = k;
			}
		}
	}
	printIntArray(intArray, ARRAY_LEN, ' ');
	printf("\n");

	free(doubleArray);
	free(intArray);
}