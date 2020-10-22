#include "io.h"
#include "utils.h"
#include "sort.h"
#include <locale.h>
#include <limits.h>
#include <stdbool.h>
#include <float.h>

#define MAX_LEN 10000

const char* getUI(int stage, int cursor) {
	if (stage == 0) {
		switch (cursor) {
			case 0: return "n = 5";
			case 1: return "n = 10";
			case 2: return "n = 15";
			case 3: return "n = 20";
			case 4: return "Ввести своё значение";
			default: return '\0';
		}
	} else if (stage == 2) {
		switch (cursor) {
			case 0: return "Сортировка выбором";
			case 1: return "Сортировка пузырьком";
			case 2: return "Сортировка вставками";
			case 3: return "Шейкерная сортировка";
			case 4: return "Сортировка расчёской";
			case 5: return "Пирамидальная сортировка";
			case 6: return "Выбрать";
			default: return '\0';
		}
	} else if (stage == 3) {
		switch (cursor) {
		case 0: return "Да";
		case 1: return "Нет";
		default: return '\0';
		}
	} else {
		return "\0";
	}
}

int maxCursor(stage) {
	switch (stage)
	{
	case 0:
		return 4;
	case 2:
		return SORTS_COUNT;
	default:
		return -1;
	}
}

int main() {
	int a[MAX_LEN], b[MAX_LEN];
	int n = 0, key;
	int stage = 0, cursor = 0;
	int start, end;
	bool selectedSorts[SORTS_COUNT] = { 0 };
	int csr[SORTS_COUNT] = { 0 }, cper[SORTS_COUNT] = { 0 };
	double ctime[SORTS_COUNT] = { 0 };
	int selectedCount = 0;
	bool showSort = true;
	int check = 0, k = 1, minT;
	double t;
	bool flag = true;
	double st = 0, ed = 0;

	setlocale(LC_CTYPE, "Russian");
	key = 0;
	setBufferedInput(false);
	while (key != KEY_QUIT) {
		clear();
		// ui
		switch (stage) {
		case 0:
			printf("Выберите размер массива [1, %d]\n", MAX_LEN);
			for (int i = 0; i <= maxCursor(stage); i++) {
				printf("%s%s\n", i == cursor ? "> " : "  ", getUI(stage, i));
			}
			break;
		case 1:
			setBufferedInput(true);
			printf("Ввод границ значений массива.\n");
			printf("Введите левую границу: ");
			scanInt(&start, INT_MIN, INT_MAX);
			printf("Введите правую границу: ");
			scanInt(&end, INT_MIN, INT_MAX);
			printf("Сгенерированный массив: ");
			fillIntArray(a, n, start, end);
			printIntArray(a, n, ' ');
			copy(a, b, n);
			clearBuf();
			setBufferedInput(false);
			printf("\nНажмите ENTER, чтобы продолжить\n");
			break;
		case 2:
			printf("Выберите нужные сортировки\n");
			for (int i = 0; i < SORTS_COUNT; i++) {
				if (selectedSorts[i]) {
					printf("%s\033[1;32m%s\033[0m\n", i == cursor ? "> " : "  ", getUI(stage, i));
				} else {
					printf("%s\033[1;31m%s\033[0m\n", i == cursor ? "> " : "  ", getUI(stage, i));
				}
			}
			printf("%s%s\n", cursor == SORTS_COUNT ? "> " : "  ", getUI(stage, SORTS_COUNT));
			break;
		case 3:
			for (int i = 0; i < SORTS_COUNT; i++) {
				if (selectedSorts[i]) {
					switch (i) {
					case SELECTION:
						selection(b, n, &csr[i], &cper[i], &ctime[i]); break;
					case BUBBLE:
						bubble(b, n, &csr[i], &cper[i], &ctime[i]); break;
					case INSERTION:
						insertion(b, n, &csr[i], &cper[i], &ctime[i]); break;
					case SHAKER:
						shaker(b, n, &csr[i], &cper[i], &ctime[i]); break;
					case COMB:
						comb(b, n, &csr[i], &cper[i], &ctime[i]); break;
					case HEAP:
						heap(b, n, &csr[i], &cper[i], &ctime[i]); break;
					}
					wait(200);
					printf("Проверка");
					check = testSort(b, n);
					if (check == 0) {
						printf("\rПроверка...ОК\n");
					} else {
						printf("\rПроверка...Ошибка\nУпорядоченность нарушается на %d элементе", check + 1);
					}
					copy(a, b, n);
				}
			}
			printf("\nНажмите ENTER, чтобы продолжить\n");
			break;
		case 4:
			printf("Результаты:\n");
			printf("%10s %24s %20s %17s %21s\n", "Номер", "Название", "Кол-во перестановок", "Кол-во сравнений", "Время");
			k = 1;
			flag = true;
			while (flag) {
				minT = 0;		// index
				t = DBL_MAX;	// value
				flag = false;
				for (int i = 0; i < SORTS_COUNT; i++) {
					if (selectedSorts[i]) {
						if (t > ctime[i]) {
							minT = i;
							t = ctime[i];
							flag = true;
						}
					}
				}
				if (t != DBL_MAX) {
					selectedSorts[minT] = false;
					printf("%10d %24s %20d %17d %.16g\n", k++, getName(minT), cper[minT], csr[minT], ctime[minT]);
				}
			}
			printf("Нажмите ENTER, чтобы выйти");
			break;
		}
		
		key = getKey();
		if (key == KEY_UP && cursor != 0) {
			cursor--;
		} else if (key == KEY_DOWN && cursor < maxCursor(stage)) {
			cursor++;
		} else if (key == KEY_ENTER) {
			if (stage == 0) {
				switch (cursor) {
				case 0: 
					n = 5;
					cursor = 0;
					stage = 1;
					break;
				case 1: 
					n = 10; 
					cursor = 0;
					stage = 1;
					break;
				case 2:
					n = 15;
					cursor = 0;
					stage = 1;
					break;
				case 3: 
					n = 20;
					cursor = 0;
					stage = 1;
					break;
				case 4: 
					setBufferedInput(true);
					scanInt(&n, 1, MAX_LEN);
					setBufferedInput(false);
					cursor = 0;
					stage = 1;
					break;
				}
			} else if (stage == 1) {
				stage = 2;
			} else if (stage == 2) {
				if (cursor != SORTS_COUNT) {
					selectedSorts[cursor] = !selectedSorts[cursor];
				} else {
					for (int i = 0; i < SORTS_COUNT; i++) {
						selectedCount += selectedSorts[i];
					}

					if (selectedCount > 0) {
						stage = 3;
						cursor = 0;
					}
				}
			} else if (stage == 3) {
				stage = 4;
			}
			else if (stage == 4) {
				break;
			}
		}
	}

	setBufferedInput(true);
	return 0;
}