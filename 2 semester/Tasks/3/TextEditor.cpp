#include "TextEditor.h"

TextEditor::TextEditor(SHORT x, SHORT y, SHORT width, SHORT offset) : 
	x(x), 
	y(y), 
	width(width), 
	value(NULL), 
	isActive(FALSE),
	offset(offset) {
	assert(offset > 0);
	assert(x >= 0 && y >= 0 && width >= 0);
}

TextEditor::TextEditor() :
	x(0),
	y(0),
	width(0),
	value(NULL),
	isActive(FALSE),
	offset(3) {}

TextEditor::TextEditor(const TextEditor& te) {
	x = te.x;
	y = te.y;
	width = te.width;
	isActive = te.isActive;
	offset = te.offset;

	if (value != NULL) {
		delete[] value;
	}

	if (te.value != NULL) {
		value = new TCHAR[_tcslen(te.value) + 1];
		for (INT i = 0; i < _tcslen(te.value); i++) {
			value[i] = te.value[i];
		}
		value[_tcslen(te.value)] = '\0';
	} else {
		value = NULL;
	}
}

TextEditor::~TextEditor() {
	delete[] value;
	isActive = false;
}

TextEditor& TextEditor::operator=(const TextEditor& te) {
	x = te.x;
	y = te.y;
	width = te.width;
	isActive = te.isActive;
	offset = te.offset;

	if (value != NULL) {
		delete[] value;
	}

	if (te.value != NULL) {
		value = new TCHAR[_tcslen(te.value) + 1];
		for (INT i = 0; i < _tcslen(te.value); i++) {
			value[i] = te.value[i];
		}
		value[_tcslen(te.value)] = '\0';
	} else {
		value = NULL;
	}

	return *this;
}

BOOL TextEditor::Show() {
	CONSOLE_SCREEN_BUFFER_INFO	csbi;
	HANDLE						hStdOut;
	COORD						bufSize, cursorPos, tmpPos;

	if (isActive) {
		return FALSE;
	}

	if (width == 0) {
		return FALSE;
	}

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	bufSize = csbi.dwSize;

	if (bufSize.Y < y + 3 + offset * 2 || bufSize.X < x + width + 5 + offset * 2) {
		return FALSE;
	}

	cursorPos.X = x + offset + 1;
	cursorPos.Y = y + offset + 1;
	SetConsoleCursorPosition(hStdOut, cursorPos);
	

	if (!WriteConsole(hStdOut, TEXT(">"), 1, NULL, NULL)) {
		return FALSE;
	}

	if (value != NULL) {
		if (!WriteConsole(hStdOut, value, _tcslen(value), NULL, NULL)) {
			return FALSE;
		}

		for (SHORT i = 0; i < width - _tcslen(value); i++) {
			if (!WriteConsole(hStdOut, TEXT("_"), 1, NULL, NULL)) {
				return FALSE;
			}
		}
	} else {
		for (SHORT i = 0; i < width; i++) {
			if (!WriteConsole(hStdOut, TEXT("_"), 1, NULL, NULL)) {
				return FALSE;
			}
		}
	}

	// Drawing Border

	tmpPos.X = x;
	tmpPos.Y = y;
	SetConsoleCursorPosition(hStdOut, tmpPos);
	for (SHORT i = 0; i < width + offset * 2 + 3; i++) {
		if (!WriteConsole(hStdOut, TEXT("="), 1, NULL, NULL)) {
			return FALSE;
		}
	}
	tmpPos.X = x;
	tmpPos.Y = y + offset * 2 + 2;
	SetConsoleCursorPosition(hStdOut, tmpPos);
	for (SHORT i = 0; i < width + offset * 2 + 3; i++) {
		if (!WriteConsole(hStdOut, TEXT("="), 1, NULL, NULL)) {
			return FALSE;
		}
	}
	tmpPos.X = x;
	tmpPos.Y = y+1;
	SetConsoleCursorPosition(hStdOut, tmpPos);
	for (SHORT i = 0; i < offset*2 + 1; i++) {
		if (!WriteConsole(hStdOut, TEXT("|"), 1, NULL, NULL)) {
			return FALSE;
		}
		tmpPos.Y++;
		SetConsoleCursorPosition(hStdOut, tmpPos);
	}

	tmpPos.X = x + width + offset*2 + 2;
	tmpPos.Y = y + 1;
	SetConsoleCursorPosition(hStdOut, tmpPos);
	for (SHORT i = 0; i < offset * 2 + 1; i++) {
		if (!WriteConsole(hStdOut, TEXT("|"), 1, NULL, NULL)) {
			return FALSE;
		}
		tmpPos.Y++;
		SetConsoleCursorPosition(hStdOut, tmpPos);
	}

	isActive = TRUE;

	return TRUE;
}

BOOL TextEditor::Hide() {
	HANDLE hStdIn, hStdOut;
	COORD cursorPos;
	
	if (!isActive) {
		return FALSE;
	}

	hStdIn	= GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	cursorPos.X = x;
	cursorPos.Y = y;
	SetConsoleCursorPosition(hStdOut, cursorPos);

	for (SHORT i = 0; i < width + offset * 2 + 3; i++) {
		if (!WriteConsole(hStdOut, TEXT(" "), 1, NULL, NULL)) {
			return FALSE;
		}
	}

	cursorPos.X = x;
	cursorPos.Y = y + offset * 2 + 2;
	SetConsoleCursorPosition(hStdOut, cursorPos);
	for (SHORT i = 0; i < width + offset * 2 + 3; i++) {
		if (!WriteConsole(hStdOut, TEXT(" "), 1, NULL, NULL)) {
			return FALSE;
		}
	}

	cursorPos.X = x;
	cursorPos.Y = y + 1;
	SetConsoleCursorPosition(hStdOut, cursorPos);
	for (SHORT i = 0; i < offset * 2 + 1; i++) {
		if (!WriteConsole(hStdOut, TEXT(" "), 1, NULL, NULL)) {
			return FALSE;
		}
		cursorPos.Y++;
		SetConsoleCursorPosition(hStdOut, cursorPos);
	}

	cursorPos.X = x + width + offset * 2 + 2;
	cursorPos.Y = y + 1;
	SetConsoleCursorPosition(hStdOut, cursorPos);
	for (SHORT i = 0; i < offset * 2 + 1; i++) {
		if (!WriteConsole(hStdOut, TEXT(" "), 1, NULL, NULL)) {
			return FALSE;
		}
		cursorPos.Y++;
		SetConsoleCursorPosition(hStdOut, cursorPos);
	}

	cursorPos.X = x;
	cursorPos.Y = y + offset + 1;
	SetConsoleCursorPosition(hStdOut, cursorPos);

	for (SHORT i = 0; i < width + offset * 2 + 3; i++) {
		if (!WriteConsole(hStdOut, TEXT(" "), 1, NULL, NULL)) {
			return FALSE;
		}
	}

	isActive = FALSE;

	return TRUE;
}

#ifdef UNICODE
#define TCharUnion(u) u.Event.KeyEvent.uChar.UnicodeChar
#else
#define TCharUnion(u) u.Event.KeyEvent.uChar.AsciiChar
#endif // UNICODE


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
				s = &res[localXPos-1];
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

BOOL TextEditor::Input() {
	HANDLE	hStdIn, hStdOut;
	COORD	cursorPos;
	DWORD	valueCount;

	if (!isActive) {
		return FALSE;
	}

	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	cursorPos.X = x + offset + 2;
	cursorPos.Y = y + offset + 1;
	if (value != NULL) {
		cursorPos.X += _tcslen(value);
	}
	SetConsoleCursorPosition(hStdOut, cursorPos);
	LPTSTR buf = new TCHAR[width+1];

	if (!ReadWithLimit(hStdIn, hStdOut, buf, width, value)) {
		return FALSE;
	}

	/*if (!ReadConsole(hStdIn, buf, width, &valueCount, NULL)) {
		return FALSE;
	}*/

	if (value != NULL) {
		delete[] value;
	}

	value = buf;

	if (_tcslen(value) > width) {
		return FALSE;
	}

	return TRUE;
}

LPCTSTR TextEditor::GetInput() {
	if (!isActive) {
		return FALSE;
	}

	return value;
}

BOOL TextEditor::SetNewCords(SHORT x, SHORT y, SHORT width) {
	if (isActive) {
		return FALSE;
	}

	this->x = x;
	this->y = y;
	this->width = width;

	return TRUE;
}

BOOL TextEditor::SetOffset(SHORT offset) {
	if (isActive) {
		return FALSE;
	}

	this->offset = offset;
	return TRUE;
}
