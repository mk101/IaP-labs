#include "TextEditor.h"
#define MENU_SIZE 5

// Parse unsigned short
BOOL tryParse(const LPTSTR str, PSHORT res) {
	PTCHAR end;
	DWORD a;
	PTCHAR minus = _tcsrchr(str, TEXT('-'));
	if (minus != NULL) {
		return FALSE;
	}

	a = _tcstol(str, &end, 10);
	if (*end != TEXT('\0')) {
		return FALSE;
	}
	*res = a;
	return TRUE;
}

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hStdIn, hStdOut;
	COORD cursorPosition;
	SHORT selectPosition;
	INPUT_RECORD ir;
	DWORD eventNumRead;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	TextEditor te = TextEditor();

	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	selectPosition = 0;

	while (TRUE) {
		cursorPosition.X = 1;
		cursorPosition.Y = 0;

		if (!SetConsoleCursorPosition(hStdOut, cursorPosition)) {
			return -3;
		}

		GetConsoleScreenBufferInfo(hStdOut, &csbi);
		for (SHORT i = 0; i < MENU_SIZE; i++) {
			for (SHORT j = 0; j < csbi.dwSize.X; j++) {
				if (!WriteConsole(hStdOut, TEXT(" "), 1, NULL, NULL)) {
					return -1;
				}
			}
			cursorPosition.X = 0;
			cursorPosition.Y++;
			if (!SetConsoleCursorPosition(hStdOut, cursorPosition)) {
				return -3;
			}
		}

		cursorPosition.X = 1;
		cursorPosition.Y = 0;

		if (!SetConsoleCursorPosition(hStdOut, cursorPosition)) {
			return -3;
		}

		if (!WriteConsole(hStdOut, TEXT("Ввод положения и размера окна\n Показать редактор\n Закрыть редактор\n Ввести/Отредактировать текст\n Завершить работу"), 114, NULL, NULL)) {
			return -1;
		}

		cursorPosition.X = 0;
		cursorPosition.Y = selectPosition;
		if (!SetConsoleCursorPosition(hStdOut, cursorPosition)) {
			return -3;
		}

		if (!WriteConsole(hStdOut, TEXT(">"), 1, NULL, NULL)) {
			return -1;
		}

		if (!ReadConsoleInput(hStdIn, &ir, 1, &eventNumRead)) {
			return -2;
		}

		if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown) {
			switch (ir.Event.KeyEvent.wVirtualKeyCode) {
			case VK_UP:
				if (selectPosition == 0) break;

				cursorPosition.X = 0;
				cursorPosition.Y = selectPosition--;
				if (!SetConsoleCursorPosition(hStdOut, cursorPosition)) {
					return -3;
				}

				if (!WriteConsole(hStdOut, TEXT(" "), 1, NULL, NULL)) {
					return -1;
				}

				break;
			case VK_DOWN:
				if (selectPosition == MENU_SIZE - 1) break;

				cursorPosition.X = 0;
				cursorPosition.Y = selectPosition++;
				if (!SetConsoleCursorPosition(hStdOut, cursorPosition)) {
					return -3;
				}

				if (!WriteConsole(hStdOut, TEXT(" "), 1, NULL, NULL)) {
					return -1;
				}

				break;
			case VK_RETURN:
				switch (selectPosition) {
				case 0:
					LPTSTR buf;
					SHORT val, x, y, width;

					cursorPosition.X = 0;
					cursorPosition.Y = 0;
					buf = new TCHAR[6];
					if (!SetConsoleCursorPosition(hStdOut, cursorPosition)) {
						delete[] buf;
						return -3;
					}
					GetConsoleScreenBufferInfo(hStdOut, &csbi);
					for (SHORT i = 0; i < MENU_SIZE; i++) {
						for (SHORT j = 0; j < csbi.dwSize.X; j++) {
							if (!WriteConsole(hStdOut, TEXT(" "), 1, NULL, NULL)) {
								delete[] buf;
								return -1;
							}
						}
						cursorPosition.X = 0;
						cursorPosition.Y++;
						if (!SetConsoleCursorPosition(hStdOut, cursorPosition)) {
							delete[] buf;
							return -3;
						}
					}

					cursorPosition.X = 0;
					cursorPosition.Y = 0;

					if (!SetConsoleCursorPosition(hStdOut, cursorPosition)) {
						delete[] buf;
						return -3;
					}

					if (!WriteConsole(hStdOut, TEXT("Введите Координаты: X:[___] Y:[___]\nВведите размер строки: [___]"), 64, NULL, NULL)) {
						delete[] buf;
						return -1;
					}

					cursorPosition.X = 23;
					cursorPosition.Y = 0;
					if (!SetConsoleCursorPosition(hStdOut, cursorPosition)) {
						delete[] buf;
						return -3;
					}

					if (!ReadWithLimit(hStdIn, hStdOut, buf, 3, NULL)) {
						delete[] buf;
						return -2;
					}

					
					if (!tryParse(buf, &val)) {
						MessageBox(NULL, TEXT("Неверное значение"), TEXT("Ошибка"), MB_OK);
						delete[] buf;
						break;
					}

					x = val;
					if (x > csbi.dwSize.X) {
						MessageBox(NULL, TEXT("X > размер окна"), TEXT("Ошибка"), MB_OK);
						delete[] buf;
						break;
					}
					cursorPosition.X = 31;
					cursorPosition.Y = 0;
					if (!SetConsoleCursorPosition(hStdOut, cursorPosition)) {
						delete[] buf;
						return -3;
					}

					if (!ReadWithLimit(hStdIn, hStdOut, buf, 3, NULL)) {
						delete[] buf;
						return -2;
					}

					if (!tryParse(buf, &val)) {
						MessageBox(NULL, TEXT("Неверное значение"), TEXT("Ошибка"), MB_OK);
						delete[] buf;
						break;
					}
					y = val;

					cursorPosition.X = 24;
					cursorPosition.Y = 1;
					if (!SetConsoleCursorPosition(hStdOut, cursorPosition)) {
						delete[] buf;
						return -3;
					}

					if (!ReadWithLimit(hStdIn, hStdOut, buf, 3, NULL)) {
						delete[] buf;
						return -2;
					}

					if (!tryParse(buf, &val)) {
						MessageBox(NULL, TEXT("Неверное значение"), TEXT("Ошибка"), MB_OK);
						delete[] buf;
						break;
					}
					width = val;

					if (!te.SetNewCords(x, y, width)) {
						MessageBox(NULL, TEXT("Не удалось применить новое значение"), TEXT("Ошибка"), MB_OK);
						delete[] buf;
						break;
					}

					delete[] buf;
					break;
				case 1:
					if (!te.Show()) {
						MessageBox(NULL, TEXT("Редактор уже открыт или имеет 0 размер"), TEXT("Не удалось выполнить команду"), MB_OK);
						break;
					}
					break;
				case 2:
					if (!te.Hide()) {
						MessageBox(NULL, TEXT("Редактор уже Закрыт"), TEXT("Не удалось выполнить команду"), MB_OK);
						break;
					}
					break;
				case 3:
					if (!te.Input()) {
						MessageBox(NULL, TEXT("Не удалось считать текст"), TEXT("Не удалось выполнить команду"), MB_OK);
						break;
					}
					break;
				case 4:
					return 0;
				}
			}
		}


	}


	return 0;
}
