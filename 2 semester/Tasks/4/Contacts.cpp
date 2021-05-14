#include "Contacts.h"

extern VOID RecordCpy(PRECORD dest, PCRECORD source) {
	PDATE d = new Date;

	dest->Name = new WCHAR[lstrlenW(source->Name) + 1];
	wcscpy_s(dest->Name, lstrlenW(source->Name) + 1, source->Name);

	dest->LastName = new WCHAR[lstrlenW(source->LastName) + 1];
	wcscpy_s(dest->LastName, lstrlenW(source->LastName) + 1, source->LastName);

	dest->Patronymic = new WCHAR[lstrlenW(source->Patronymic) + 1];
	wcscpy_s(dest->Patronymic, lstrlenW(source->Patronymic) + 1, source->Patronymic);

	if (source->Phone != NULL) {
		dest->Phone = new CHAR[strlen(source->Phone) + 1];
		strcpy_s(dest->Phone, strlen(source->Phone) + 1, source->Phone);
	} else {
		dest->Phone = NULL;
	}
	if (source->BDate != NULL) {
		d->Day = source->BDate->Day;
		d->Month = source->BDate->Month;
		d->Year = source->BDate->Year;
		dest->BDate = d;
	} else {
		delete d;
		dest->BDate = NULL;
	}
	dest->IsFavorite = source->IsFavorite;
}

LPWSTR FormFIO(PCRECORD record) {
	DWORD len = 
		lstrlenW(record->Name) +
		lstrlenW(record->LastName) +
		lstrlenW(record->Patronymic) + 3;
	LPWSTR fio = new WCHAR[len];
	fio[0] = L'\0';

	wcscat_s(fio, len, record->LastName);
	wcscat_s(fio, len, L" ");
	wcscat_s(fio, len, record->Name);
	wcscat_s(fio, len, L" ");
	wcscat_s(fio, len, record->Patronymic);

	return fio;
}

BOOL Contacts::Resize(UINT newSize) {
	if (newSize < Capacity) return FALSE;
	if (newSize == Capacity) return TRUE;

	LPRECORD newData = new Record[newSize];
	for (UINT i = 0; i < Size; i++) {
		RecordCpy(newData + i, Records + i);
	}

	Capacity = newSize;

	delete[] Records;
	Records = newData;
	return TRUE;
}

Contacts::Contacts() {
	Capacity = 10;
	Size = 0;
	Records = new Record[Capacity];
}

Contacts::~Contacts() {
	for (INT i = 0; i < Size; i++) {
		delete[] Records[i].Name;
		delete[] Records[i].LastName;
		delete[] Records[i].Patronymic;
		delete[] Records[i].Phone;
		delete Records[i].BDate;
	}
	delete[] Records;
}

Contacts::Contacts(const Contacts& c) {
	if (Records == c.Records) return;

	Capacity = c.Capacity;
	Size = c.Size;

	Records = new Record[Capacity];
	for (UINT i = 0; i < Size; i++) {
		RecordCpy(&Records[i], &c.Records[i]);
	}
}

Contacts& Contacts::operator=(const Contacts& c) {
	if (Records == c.Records) return *this;

	Capacity = c.Capacity;
	Size = c.Size;

	Records = new Record[Capacity];
	for (UINT i = 0; i < Size; i++) {
		RecordCpy(&Records[i], &c.Records[i]);
	}

	return *this;
}

BOOL Contacts::SaveToFile(LPCWSTR path) {
	std::wofstream file;
	file.open(path);
	if (!file) {
		return FALSE;
	}
	file << Size << std::endl;

	for (UINT i = 0; i < Size; i++) {
		file << Records[i].Name << std::endl;
		file << Records[i].LastName << std::endl;
		file << Records[i].Patronymic << std::endl;
		if (Records[i].Phone != NULL) {
			file << Records[i].Phone << std::endl;
		} else {
			file << "<NULL>" << std::endl;
		}
		if (Records[i].BDate != NULL) {
			file << Records[i].BDate->Day << ' '
				<< Records[i].BDate->Month << ' '
				<< Records[i].BDate->Year << std::endl;
		} else {
			file << "0 0 0" << std::endl;
		}
		file << Records[i].IsFavorite << std::endl;
	}
	file.close();
	return TRUE;
}

BOOL Contacts::ReadFromFile(LPCWSTR path) {
	std::wifstream file;
	file.open(path);
	if (!file) {
		return FALSE;
	}

	if (Capacity != 0) {
		delete[] Records;
	}
	
	file >> Size >> std::skipws;
	Capacity = Size + 2;
	Records = new Record[Capacity];
	LPWSTR buf = new TCHAR[14];
	for (UINT i = 0; i < Size; i++) {
		Records[i].Name = new TCHAR[20];
		file >> Records[i].Name >> std::skipws;
		Records[i].LastName = new TCHAR[20];
		file >> Records[i].LastName >> std::skipws;
		Records[i].Patronymic = new TCHAR[20];
		file >> Records[i].Patronymic >> std::skipws;

		file >> buf >> std::skipws;
		if (wcscmp(buf, L"<NULL>") != 0) {
			Records[i].Phone = new char[14];
			size_t j = 0;
			wcstombs_s(&j, Records[i].Phone, (size_t)14, buf, (size_t)14);
		} else {
			Records[i].Phone = NULL;
		}

		int day, month, year;
		file >> day >> month >> year >> std::skipws;
		if (day == 0) {
			Records[i].BDate = NULL;
		} else {
			PDATE d = new Date;
			d->Day = (BYTE)day;
			d->Month = (BYTE)month;
			d->Year = (SHORT)year;
			Records[i].BDate = d;
		}

		file >> day >> std::skipws;
		Records[i].IsFavorite = (BOOL)day;
	}
	
	return TRUE;
}

BOOL Contacts::AddRecord(LPCWSTR name, LPCWSTR lastName, LPCWSTR patronymic, LPCSTR phone, PDATE date, BOOL isFavorite) {
	Record r;
	PDATE d = new Date();
	if (name == NULL || lastName == NULL || patronymic == NULL) {
		return FALSE;
	}
	r.Name = new WCHAR[lstrlenW(name)+1];
	wcscpy_s(r.Name, lstrlenW(name) + 1, name);

	r.LastName = new WCHAR[lstrlenW(lastName) + 1];
	wcscpy_s(r.LastName, lstrlenW(lastName) + 1, lastName);

	r.Patronymic = new WCHAR[lstrlenW(patronymic) + 1];
	wcscpy_s(r.Patronymic, lstrlenW(patronymic) + 1, patronymic);

	if (phone != NULL) {
		r.Phone = new CHAR[strlen(phone) + 1];
		strcpy_s(r.Phone, strlen(phone) + 1, phone);
	} else {
		r.Phone = NULL;
	}

	if (date != NULL) {
		d->Day = date->Day;
		d->Month = date->Month;
		d->Year = date->Year;
		r.BDate = d;
	} else {
		delete d;
		d = NULL;
		r.BDate = NULL;
	}
	r.IsFavorite = isFavorite;

	if (Size >= Capacity) {
		if (!Resize(Capacity + 5)) {
			delete[] r.Name;
			delete[] r.LastName;
			delete[] r.Patronymic;
			delete[] r.Phone;
			delete d;
			return FALSE;
		}
	}
	Records[Size++] = r;

	return TRUE;
}

BOOL Contacts::FindRecord(LPCWSTR fio, PRECORD& record) {
	LPWSTR buf;
	record = NULL;
	for (UINT i = 0; i < Size; i++) {
		buf = FormFIO(Records + i);
		if (wcscmp(buf, fio) == 0) {
			record = Records + i;
			delete[] buf;
			return TRUE;
		}
		delete[] buf;
	}

	return FALSE;
}

BOOL Contacts::FindRecord(LPCSTR phone, PRECORD& record) {
	record = NULL;
	for (UINT i = 0; i < Size; i++) {
		if (Records[i].Phone != NULL && strcmp(phone, Records[i].Phone) == 0) {
			record = Records + i;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL Contacts::GetRecords(CONST WCHAR ch, LPRECORD& records, UINT& size) {
	records = NULL;
	UINT resSize = 0;
	for (UINT i = 0; i < Size; i++) {
		if (Records[i].LastName[0] == ch) {
			resSize++;
		}
	}
	size = resSize;
	if (resSize == 0) {
		return FALSE;
	}
	records = new Record[resSize];
	resSize = 0;
	for (UINT i = 0; i < Size; i++) {
		if (Records[i].LastName[0] == ch) {
			RecordCpy(&records[resSize++], Records + i);
		}
	}
	return TRUE;
}

UINT Contacts::GetSize() {
	return Size;
}

BOOL Contacts::MakeFavorite(LPCWSTR fio) {
	PRECORD rec;
	if (!FindRecord(fio, rec)) {
		return FALSE;
	}

	if (rec->IsFavorite) {
		return FALSE;
	}

	rec->IsFavorite = TRUE;
	return TRUE;
}

BOOL Contacts::RemoveFromFavorite(LPCWSTR fio) {
	PRECORD rec;
	if (!FindRecord(fio, rec)) {
		return FALSE;
	}

	if (!rec->IsFavorite) {
		return FALSE;
	}

	rec->IsFavorite = FALSE;
	return TRUE;
}

BOOL Contacts::GetFavorites(LPRECORD& records, UINT& size) {
	UINT favSize = 0;
	records = NULL;

	for (UINT i = 0; i < Size; i++) {
		if (Records[i].IsFavorite) {
			favSize++;
		}
	}
	size = favSize;
	if (favSize == 0) {
		return FALSE;
	}

	records = new Record[favSize];
	favSize = 0;
	for (UINT i = 0; i < Size; i++) {
		if (Records[i].IsFavorite) {
			RecordCpy(&records[favSize++], Records + i);
		}
	}
	return TRUE;
}

BOOL Contacts::RemoveByPhone(LPCSTR phone) {
	for (UINT i = 0; i < Size; i++) {
		if (Records[i].Phone != NULL && strcmp(phone, Records[i].Phone) == 0) {
			if (!RemoveAt(i)) {
				return FALSE;
			}
			return TRUE;
		}
	}

	return FALSE;
}

BOOL Contacts::RemoveAt(UINT index) {
	PRECORD s, e;
	if (index < 0 || index >= Size) {
		return FALSE;
	}
	
	s = Records + index;
	e = s + 1;

	while (e != Records + Size) {
		RecordCpy(s++, e++);
	}

	Size--;

	return TRUE;
}
