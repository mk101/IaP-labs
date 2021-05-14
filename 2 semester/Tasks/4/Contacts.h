#pragma once
#include <Windows.h>
#include <tchar.h>
#include <fstream>

#ifndef UNICODE
#error Unicode is requared
#endif
#define TCharUnion(u) u.Event.KeyEvent.uChar.UnicodeChar

struct Date {
	BYTE Day;
	BYTE Month;
	SHORT Year;
};

typedef Date* PDATE;

struct Record {
	LPWSTR Name;
	LPWSTR LastName;
	LPWSTR Patronymic;
	LPSTR Phone;
	PDATE BDate;
	BOOL IsFavorite;
};


typedef Record* PRECORD, * LPRECORD;
typedef const Record* PCRECORD, * LPCRECORD;

class Contacts {
private:
	LPRECORD Records;
	UINT Size;
	UINT Capacity;

	BOOL Resize(UINT newSize);
public:
	Contacts();
	~Contacts();
	Contacts(const Contacts& c);
	Contacts& operator=(const Contacts& c);

	BOOL SaveToFile(LPCWSTR path);
	BOOL ReadFromFile(LPCWSTR path);
	BOOL AddRecord(LPCWSTR name, LPCWSTR lastName, LPCWSTR patronymic, LPCSTR phone, PDATE date, BOOL isFavorite);
	BOOL FindRecord(LPCWSTR fio, PRECORD& record);
	BOOL FindRecord(LPCSTR phone, PRECORD& record);
	BOOL GetRecords(CONST WCHAR ch, LPRECORD& records, UINT& size);
	UINT GetSize();
	BOOL MakeFavorite(LPCWSTR fio);
	BOOL RemoveFromFavorite(LPCWSTR fio);
	BOOL GetFavorites(LPRECORD& records, UINT& size);
	BOOL RemoveByPhone(LPCSTR phone);
	BOOL RemoveAt(UINT index);
};
