#pragma once
#include <Windows.h>
#include <tchar.h>
#include <assert.h>

class TextEditor {
private:
	SHORT x, y, width;
	LPTSTR value;
	BOOL isActive;
	SHORT offset;
public:
	TextEditor(SHORT x, SHORT y, SHORT width, SHORT offset=3);
	TextEditor();
	TextEditor(const TextEditor& te);
	~TextEditor();
	TextEditor& operator=(const TextEditor& te);

	BOOL Show();
	BOOL Hide();
	BOOL Input();
	LPCTSTR GetInput();
	BOOL SetNewCords(SHORT x, SHORT y, SHORT width);
	BOOL SetOffset(SHORT offset);
};

BOOL ReadWithLimit(HANDLE hConsoleInput, HANDLE hConsoleOutput, LPTSTR res, SHORT limit, PCTSTR value);