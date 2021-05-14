#include "Contacts.h"
#include <string>

VOID ClearConsole(HANDLE hStdOut);
BOOL ReadWithLimit(HANDLE hConsoleInput, HANDLE hConsoleOutput, LPTSTR res, SHORT limit, PCTSTR value);
BYTE GetMenuSize(BYTE stage);
BOOL tryParse(const LPTSTR str, PSHORT res);

INT wmain(INT argc, WCHAR* argv[]) {
	HANDLE in, out;
	BYTE state, selectPosition;
	COORD cursorPosition;
	INPUT_RECORD ir;
	DWORD eventNumReaded;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	Contacts contacts = Contacts();
	std::locale::global(std::locale("Russian_Russia"));

	in = GetStdHandle(STD_INPUT_HANDLE);
	out = GetStdHandle(STD_OUTPUT_HANDLE);
	state = 0;
	selectPosition = 0;
	cursorPosition = { 0, 0 };

	while (TRUE) {
		cursorPosition = { 0, 0 };
		if (!SetConsoleCursorPosition(out, cursorPosition)) {
			return GetLastError();
		}

		if (!WriteConsoleW(out, L"========Contacts========\n", 25, NULL, NULL)) {
			return -1;
		}
		switch (state) {
		case 0:
			if (!WriteConsoleW(out, L" Add\n", 5, NULL, NULL)) {
				return GetLastError();
			}
			if (!WriteConsoleW(out, L" Remove by phone\n", 17, NULL, NULL)) {
				return GetLastError();
			}
			if (!WriteConsoleW(out, L" Save to file\n", 14, NULL, NULL)) {
				return GetLastError();
			}
			if (!WriteConsoleW(out, L" Read from file\n", 16, NULL, NULL)) {
				return GetLastError();
			}
			if (!WriteConsoleW(out, L" Find contact by FIO\n", 21, NULL, NULL)) {
				return GetLastError();
			}
			if (!WriteConsoleW(out, L" Find contact by phone\n", 23, NULL, NULL)) {
				return GetLastError();
			} 
			if (!WriteConsoleW(out, L" Get contacts\n", 14, NULL, NULL)) {
				return GetLastError();
			}
			if (!WriteConsoleW(out, L" Get contacts count\n", 20, NULL, NULL)) {
				return GetLastError();
			}
			if (!WriteConsoleW(out, L" Add to favorite\n", 17, NULL, NULL)) {
				return GetLastError();
			}
			if (!WriteConsoleW(out, L" Remove from favorite\n", 22, NULL, NULL)) {
				return GetLastError();
			}
			if (!WriteConsoleW(out, L" Get favorites\n", 15, NULL, NULL)) {
				return GetLastError();
			}
			break;
		
		default:
			return 404;
		}

		cursorPosition = { 0, selectPosition + 1 };

		if (!SetConsoleCursorPosition(out, cursorPosition)) {
			return GetLastError();
		}

		if (!WriteConsoleW(out, L">", 1, NULL, NULL)) {
			return GetLastError();
		}

		if (!ReadConsoleInputW(in, &ir, 1, &eventNumReaded)) {
			return GetLastError();
		}

		if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown) {
			switch (ir.Event.KeyEvent.wVirtualKeyCode) {
			case VK_UP:
				if (selectPosition == 0) break;

				cursorPosition.X = 0;
				cursorPosition.Y = selectPosition--;
				if (!SetConsoleCursorPosition(out, cursorPosition)) {
					return -3;
				}

				if (!WriteConsole(out, TEXT(" "), 1, NULL, NULL)) {
					return -1;
				}

				break;
			case VK_DOWN:
				if (selectPosition == GetMenuSize(state) - 1) break;

				cursorPosition.X = 0;
				cursorPosition.Y = selectPosition++;
				if (!SetConsoleCursorPosition(out, cursorPosition)) {
					return -3;
				}

				if (!WriteConsole(out, TEXT(" "), 1, NULL, NULL)) {
					return -1;
				}

				break;
			case VK_RETURN:
				switch (selectPosition) {
				case 0:
				{
					ClearConsole(out);
					LPWSTR buf = new TCHAR[20];

					LPWSTR name = new TCHAR[20];
					LPWSTR lastName = new TCHAR[20];
					LPWSTR patr = new TCHAR[20];
					LPSTR phone = NULL;
					PDATE date = NULL;
					SHORT day, month;
					SHORT year;

					name[0] = L'\0';
					lastName[0] = L'\0';
					patr[0] = L'\0';
					if (!WriteConsoleW(out, L" Name [___________________]\n", 28, NULL, NULL)) {
						return GetLastError();
					}
					if (!WriteConsoleW(out, L" Last name [___________________]\n", 33, NULL, NULL)) {
						return GetLastError();
					}
					if (!WriteConsoleW(out, L" Patronymic [___________________]\n", 34, NULL, NULL)) {
						return GetLastError();
					}
					if (!WriteConsoleW(out, L" Phone(Can be empty) [___________]\n", 35, NULL, NULL)) {
						return GetLastError();
					}
					if (!WriteConsoleW(out, L" Birthday(Can be empty) [__].[__].[____]\n", 41, NULL, NULL)) {
						return GetLastError();
					}
					cursorPosition = { 7, 0 };
					if (!SetConsoleCursorPosition(out, cursorPosition)) {
						return GetLastError();
					}
					if (!ReadWithLimit(in, out, buf, 19, NULL)) {
						return GetLastError();
					}
					wcscpy_s(name, 20, buf);

					cursorPosition = { 12, 1 };
					if (!SetConsoleCursorPosition(out, cursorPosition)) {
						return GetLastError();
					}
					if (!ReadWithLimit(in, out, buf, 19, NULL)) {
						return GetLastError();
					}
					wcscpy_s(lastName, 20, buf);

					cursorPosition = { 13, 2 };
					if (!SetConsoleCursorPosition(out, cursorPosition)) {
						return GetLastError();
					}
					if (!ReadWithLimit(in, out, buf, 19, NULL)) {
						return GetLastError();
					}
					wcscpy_s(patr, 20, buf);

					cursorPosition = { 22, 3 };
					if (!SetConsoleCursorPosition(out, cursorPosition)) {
						return GetLastError();
					}
					if (!ReadWithLimit(in, out, buf, 11, NULL)) {
						return GetLastError();
					}
					if (buf[0] != L'\0') {
						size_t j;
						phone = new CHAR[14];
						phone[0] = '\0';
						wcstombs_s(&j, phone, (size_t)14, buf, (size_t)14);
					}

					cursorPosition = { 25, 4 };
					if (!SetConsoleCursorPosition(out, cursorPosition)) {
						return GetLastError();
					}
					if (!ReadWithLimit(in, out, buf, 2, NULL)) {
						return GetLastError();
					}
					if (buf[0] != L'\0') {
						if (!tryParse(buf, &day)) {
							return -2;
						}

						cursorPosition = { 30, 4 };
						if (!SetConsoleCursorPosition(out, cursorPosition)) {
							return GetLastError();
						}
						if (!ReadWithLimit(in, out, buf, 2, NULL)) {
							return GetLastError();
						}

						if (buf[0] != L'\0') {
							if (!tryParse(buf, &month)) {
								return -2;
							}

							cursorPosition = { 35, 4 };
							if (!SetConsoleCursorPosition(out, cursorPosition)) {
								return GetLastError();
							}
							if (!ReadWithLimit(in, out, buf, 4, NULL)) {
								return GetLastError();
							}

							if (!tryParse(buf, &year)) {
								return -2;
							}
						} else {
							return -2;
						}

						date = new Date{ (BYTE)day, (BYTE)month, year };
					}

					if (!contacts.AddRecord(name, lastName, patr, phone, date, FALSE)) {
						MessageBox(NULL, TEXT("Can't add contact"), TEXT("Error"), MB_OK);
					}
					ClearConsole(out);
					delete[] name;
					delete[] lastName;
					delete[] patr;
					delete[] phone;
					delete date;

					delete[] buf;
				}
					break;
				case 1:
				{
					LPWSTR buf = new TCHAR[14];
					LPSTR phone = new CHAR[14];
					size_t j;
					phone[0] = '\0';
					ClearConsole(out);
					if (!WriteConsoleW(out, L" Phone [___________]\n", 22, NULL, NULL)) {
						return GetLastError();
					}

					cursorPosition = { 8, 0 };
					if (!SetConsoleCursorPosition(out, cursorPosition)) {
						return GetLastError();
					}
					if (!ReadWithLimit(in, out, buf, 11, NULL)) {
						return GetLastError();
					}
					
					wcstombs_s(&j, phone, (size_t)14, buf, (size_t)14);
					if (!contacts.RemoveByPhone(phone)) {
						MessageBox(NULL, TEXT("Can't remove contact"), TEXT("Error"), MB_OK);
					}
					ClearConsole(out);
					delete[] phone;
					delete[] buf;
				}
					break;
				case 2:
				{
					LPWSTR buf = new TCHAR[19];
					ClearConsole(out);
					if (!WriteConsoleW(out, L" Name [____________]\n", 21, NULL, NULL)) {
						return GetLastError();
					}
					cursorPosition = { 7, 0 };
					if (!SetConsoleCursorPosition(out, cursorPosition)) {
						return GetLastError();
					}
					if (!ReadWithLimit(in, out, buf, 12, NULL)) {
						return GetLastError();
					}

					buf = lstrcatW(buf, L".data");
					if (!contacts.SaveToFile(buf)) {
						MessageBox(NULL, TEXT("Can't save to file"), TEXT("Error"), MB_OK);
					}
					ClearConsole(out);
					delete[] buf;
				}

					break;
				case 3:
				{
					LPWSTR buf = new TCHAR[19];
					ClearConsole(out);
					if (!WriteConsoleW(out, L" Name [____________]\n", 21, NULL, NULL)) {
						return GetLastError();
					}
					cursorPosition = { 7, 0 };
					if (!SetConsoleCursorPosition(out, cursorPosition)) {
						return GetLastError();
					}
					if (!ReadWithLimit(in, out, buf, 12, NULL)) {
						return GetLastError();
					}

					buf = lstrcatW(buf, L".data");
					if (!contacts.ReadFromFile(buf)) {
						MessageBox(NULL, TEXT("Can't read from file"), TEXT("Error"), MB_OK);
					}
					ClearConsole(out);
					delete[] buf;
				}
					break;
				case 4:
				{
					LPWSTR buf = new TCHAR[60];
					PRECORD prec = NULL;
					ClearConsole(out);
					if (!WriteConsoleW(out, L" FIO [___________________________________________________________]\n", 67, NULL, NULL)) {
						return GetLastError();
					}
					cursorPosition = { 6, 0 };
					if (!SetConsoleCursorPosition(out, cursorPosition)) {
						return GetLastError();
					}
					if (!ReadWithLimit(in, out, buf, 59, NULL)) {
						return GetLastError();
					}

					if (!contacts.FindRecord(buf, prec)) {
						MessageBox(NULL, TEXT("Can't find record"), TEXT("Error"), MB_OK);
					} else {
						std::wstring wstr = std::wstring(prec->Name);
						wstr += L" ";
						wstr += prec->LastName;
						wstr += L" ";
						wstr += prec->Patronymic;
						wstr += L"\n";
						if (prec->Phone != NULL) {
							std::string p = std::string(prec->Phone);
							wstr += std::wstring(p.begin(), p.end());
							wstr += L"\n";
						}

						if (prec->BDate != NULL) {
							wstr += std::to_wstring(prec->BDate->Day);
							wstr += L" ";
							wstr += std::to_wstring(prec->BDate->Month);
							wstr += L" ";
							wstr += std::to_wstring(prec->BDate->Year);
							wstr += L"\n";
						}

						wstr += prec->IsFavorite == TRUE ? L"Favorite" : L"Not favorite";
						MessageBox(NULL, wstr.c_str(), TEXT("Result"), MB_OK);
					}

					ClearConsole(out);
					delete[] buf;
				}
					break;
				case 5:
				{
					LPWSTR buf = new TCHAR[14];
					LPSTR phone = new CHAR[14];
					PRECORD prec = NULL;
					size_t j;
					phone[0] = '\0';
					ClearConsole(out);
					if (!WriteConsoleW(out, L" Phone [_____________]\n", 24, NULL, NULL)) {
						return GetLastError();
					}
					cursorPosition = { 8, 0 };
					if (!SetConsoleCursorPosition(out, cursorPosition)) {
						return GetLastError();
					}
					if (!ReadWithLimit(in, out, buf, 11, NULL)) {
						return GetLastError();
					}

					wcstombs_s(&j, phone, (size_t)14, buf, (size_t)14);
					if (!contacts.FindRecord(phone, prec)) {
						MessageBox(NULL, TEXT("Can't find record"), TEXT("Error"), MB_OK);
					} else {
						std::wstring wstr = std::wstring(prec->Name);
						wstr += L" ";
						wstr += prec->LastName;
						wstr += L" ";
						wstr += prec->Patronymic;
						wstr += L"\n";
						if (prec->Phone != NULL) {
							std::string p = std::string(prec->Phone);
							wstr += std::wstring(p.begin(), p.end());
							wstr += L"\n";
						}

						if (prec->BDate != NULL) {
							wstr += std::to_wstring(prec->BDate->Day);
							wstr += L" ";
							wstr += std::to_wstring(prec->BDate->Month);
							wstr += L" ";
							wstr += std::to_wstring(prec->BDate->Year);
							wstr += L"\n";
						}

						wstr += prec->IsFavorite == TRUE ? L"Favorite" : L"Not favorite";
						MessageBox(NULL, wstr.c_str(), TEXT("Result"), MB_OK);
					}
					ClearConsole(out);
					delete[] phone;
					delete[] buf;
				}
					break;
				case 6:
				{
					std::wstring wstr = std::wstring();
					UINT size = 0;
					LPRECORD recs = NULL;
					LPWSTR buf = new TCHAR[2];
					ClearConsole(out);
					if (!WriteConsoleW(out, L" Char [_]\n", 10, NULL, NULL)) {
						return GetLastError();
					}
					cursorPosition = { 7, 0 };
					if (!SetConsoleCursorPosition(out, cursorPosition)) {
						return GetLastError();
					}
					if (!ReadWithLimit(in, out, buf, 1, NULL)) {
						return GetLastError();
					}

					if (!contacts.GetRecords(buf[0], recs, size)) {
						MessageBox(NULL, TEXT("Can't find records"), TEXT("Error"), MB_OK);
					} else {
						for (UINT i = 0; i < size; i++) {
							wstr += L"-----\n";
							wstr += std::wstring(recs[i].Name);
							wstr += L" ";
							wstr += recs[i].LastName;
							wstr += L" ";
							wstr += recs[i].Patronymic;
							wstr += L"\n";
							if (recs[i].Phone != NULL) {
								std::string p = std::string(recs[i].Phone);
								wstr += std::wstring(p.begin(), p.end());
								wstr += L"\n";
							}

							if (recs[i].BDate != NULL) {
								wstr += std::to_wstring(recs[i].BDate->Day);
								wstr += L" ";
								wstr += std::to_wstring(recs[i].BDate->Month);
								wstr += L" ";
								wstr += std::to_wstring(recs[i].BDate->Year);
								wstr += L"\n";
							}

							wstr += recs[i].IsFavorite == TRUE ? L"Favorite\n" : L"Not favorite\n";
						}
						MessageBox(NULL, wstr.c_str(), TEXT("Result"), MB_OK);
					}
					
					ClearConsole(out);
					delete[] buf;
				}
					break;
				case 7:
				{
					std::wstring wstr = std::to_wstring(contacts.GetSize());
					MessageBox(NULL, wstr.c_str(), TEXT("Result"), MB_OK);
				}
				break;
				case 8:
				{
					LPWSTR buf = new TCHAR[60];
					PRECORD prec = NULL;
					ClearConsole(out);
					if (!WriteConsoleW(out, L" FIO [___________________________________________________________]\n", 67, NULL, NULL)) {
						return GetLastError();
					}
					cursorPosition = { 6, 0 };
					if (!SetConsoleCursorPosition(out, cursorPosition)) {
						return GetLastError();
					}
					if (!ReadWithLimit(in, out, buf, 59, NULL)) {
						return GetLastError();
					}
					if (!contacts.MakeFavorite(buf)) {
						MessageBox(NULL, TEXT("Can't make favorite"), TEXT("Error"), MB_OK);
					}
					ClearConsole(out);
					delete[] buf;
				}
					break;
				case 9:
				{
					LPWSTR buf = new TCHAR[60];
					PRECORD prec = NULL;
					ClearConsole(out);
					if (!WriteConsoleW(out, L" FIO [___________________________________________________________]\n", 67, NULL, NULL)) {
						return GetLastError();
					}
					cursorPosition = { 6, 0 };
					if (!SetConsoleCursorPosition(out, cursorPosition)) {
						return GetLastError();
					}
					if (!ReadWithLimit(in, out, buf, 59, NULL)) {
						return GetLastError();
					}
					if (!contacts.RemoveFromFavorite(buf)) {
						MessageBox(NULL, TEXT("Can't remove from favorite"), TEXT("Error"), MB_OK);
					}
					ClearConsole(out);
					delete[] buf;
				}
					break;
				case 10:
				{
					std::wstring wstr = std::wstring();
					UINT size = 0;
					LPRECORD recs = NULL;
					if (!contacts.GetFavorites(recs, size)) {
						MessageBox(NULL, TEXT("Can't find records"), TEXT("Error"), MB_OK);
					} else {
						for (UINT i = 0; i < size; i++) {
							wstr += L"-----\n";
							wstr += std::wstring(recs[i].Name);
							wstr += L" ";
							wstr += recs[i].LastName;
							wstr += L" ";
							wstr += recs[i].Patronymic;
							wstr += L"\n";
							if (recs[i].Phone != NULL) {
								std::string p = std::string(recs[i].Phone);
								wstr += std::wstring(p.begin(), p.end());
								wstr += L"\n";
							}

							if (recs[i].BDate != NULL) {
								wstr += std::to_wstring(recs[i].BDate->Day);
								wstr += L" ";
								wstr += std::to_wstring(recs[i].BDate->Month);
								wstr += L" ";
								wstr += std::to_wstring(recs[i].BDate->Year);
								wstr += L"\n";
							}
						}
						MessageBox(NULL, wstr.c_str(), TEXT("Result"), MB_OK);
						delete[] recs;
					}

					ClearConsole(out);
				}
					break;
				default:
					return 404;
				}
			}
		}
	}


	return 0;
}

BYTE GetMenuSize(BYTE stage) {
	switch (stage) {
	case 0:
		return 11;
	default:
		exit(-1);
		break;
	}
}

VOID ClearConsole(HANDLE hStdOut) {
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		exit(GetLastError());
	}

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(hStdOut, L' ', dwConSize, coordScreen, &cCharsWritten)) {
		exit(GetLastError());
	}

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		exit(GetLastError());
	}

	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)) {
		exit(GetLastError());
	}

	SetConsoleCursorPosition(hStdOut, coordScreen);
}

BOOL ReadWithLimit(HANDLE hConsoleInput, HANDLE hConsoleOutput, LPTSTR res, SHORT limit, PCTSTR value) {
	INPUT_RECORD lastRecord;
	SHORT curLength = 0;
	DWORD eventsRead;
	COORD curPos;
	DWORD localXPos;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (limit <= 0) {
		return FALSE;
	}
	localXPos = 0;

	if (value != NULL) {
		curLength = _tcslen(value);
		localXPos = curLength;
		_tcscpy_s(res, limit + 1, value);
	}


	/*GetConsoleMode(hConsoleInput, &mode);
	mode &= ~ENABLE_INSERT_MODE;
	mode &= ~ENABLE_LINE_INPUT;
	SetConsoleMode(hConsoleInput, mode);*/

	FlushConsoleInputBuffer(hConsoleInput); // Clear input buffer

	while (true) {
		if (!ReadConsoleInput(hConsoleInput, &lastRecord, 1, &eventsRead)) {
			return FALSE;
		}

		if (lastRecord.EventType == KEY_EVENT && lastRecord.Event.KeyEvent.bKeyDown) {
			if (TCharUnion(lastRecord) == TEXT('\r')) {
				res[curLength] = TEXT('\0');
				break;
			}

			if (TCharUnion(lastRecord) == TEXT('\b')) {
				PTCHAR s, e;

				if (localXPos == 0) {
					continue;
				}

				res[curLength] = TEXT('\0');
				s = &res[localXPos - 1];
				e = s + 1;

				while (e != &res[curLength]) {
					*s++ = *e++;
				}

				curLength--;
				localXPos--;

				res[curLength] = TEXT('\0');

				if (!GetConsoleScreenBufferInfo(hConsoleOutput, &csbi)) {
					return FALSE;
				}

				curPos = csbi.dwCursorPosition;
				curPos.X -= localXPos + 1;

				if (!SetConsoleCursorPosition(hConsoleOutput, curPos)) {
					return FALSE;
				}

				if (!WriteConsole(hConsoleOutput, res, curLength, NULL, NULL)) {
					return FALSE;
				}

				for (SHORT i = 0; i < limit - curLength; i++) {
					if (!WriteConsole(hConsoleOutput, TEXT("_"), 1, NULL, NULL)) {
						return FALSE;
					}
				}
				if (!GetConsoleScreenBufferInfo(hConsoleOutput, &csbi)) {
					return FALSE;
				}
				curPos = csbi.dwCursorPosition;

				curPos.X -= (limit - localXPos);

				if (!SetConsoleCursorPosition(hConsoleOutput, curPos)) {
					return FALSE;
				}

				continue;
			}

			switch (lastRecord.Event.KeyEvent.wVirtualKeyCode) {
			case VK_LEFT:
				if (localXPos != 0) {
					localXPos--;
					if (!GetConsoleScreenBufferInfo(hConsoleOutput, &csbi)) {
						return FALSE;
					}

					curPos = csbi.dwCursorPosition;
					curPos.X--;

					if (!SetConsoleCursorPosition(hConsoleOutput, curPos)) {
						return FALSE;
					}
				}
				continue;
			case VK_RIGHT:
				if (localXPos < curLength) {
					localXPos++;
					if (!GetConsoleScreenBufferInfo(hConsoleOutput, &csbi)) {
						return FALSE;
					}

					curPos = csbi.dwCursorPosition;
					curPos.X++;

					if (!SetConsoleCursorPosition(hConsoleOutput, curPos)) {
						return FALSE;
					}
				}
				continue;
			}

			if (curLength == limit) {
				continue;
			}
			if (TCharUnion(lastRecord) != TEXT('\0')) {
				PTSTR s = new TCHAR[curLength - localXPos + 1];
				PTCHAR c;

				res[curLength] = TEXT('\0');
				_tcscpy_s(s, curLength - localXPos + 1, &res[localXPos]);
				res[localXPos] = TCharUnion(lastRecord);
				c = &res[localXPos + 1];
				while (*s != TEXT('\0')) {
					*c++ = *s++;
				}
				*c = TEXT('\0');

				curLength++;
				localXPos++;

				if (!GetConsoleScreenBufferInfo(hConsoleOutput, &csbi)) {
					return FALSE;
				}

				curPos = csbi.dwCursorPosition;
				curPos.X -= localXPos - 1;

				if (!SetConsoleCursorPosition(hConsoleOutput, curPos)) {
					return FALSE;
				}

				if (!WriteConsole(hConsoleOutput, res, curLength, NULL, NULL)) {
					return FALSE;
				}

				for (SHORT i = 0; i < limit - curLength; i++) {
					if (!WriteConsole(hConsoleOutput, TEXT("_"), 1, NULL, NULL)) {
						return FALSE;
					}
				}
				if (!GetConsoleScreenBufferInfo(hConsoleOutput, &csbi)) {
					return FALSE;
				}
				curPos = csbi.dwCursorPosition;

				curPos.X -= (limit - localXPos);

				if (!SetConsoleCursorPosition(hConsoleOutput, curPos)) {
					return FALSE;
				}

				s -= curLength - localXPos;

				delete[] s;

				/*if (!WriteConsole(hConsoleOutput, &TCharUnion(lastRecord), 1, NULL, NULL)) {
					return FALSE;
				}
				if (curLength != limit) {
					res[curLength++] = TCharUnion(lastRecord);
					localXPos++;
				}*/


			}
		}
	}
	//SetConsoleMode(hConsoleInput, ENABLE_EXTENDED_FLAGS | ENABLE_QUICK_EDIT_MODE);

	return TRUE;
}

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