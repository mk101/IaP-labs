#include <bitset>
#include "TSet.h"
#include <iostream>
#include <locale>
#include <memory>

int main() {
	setlocale(LC_ALL, "Russian");
	std::unique_ptr<TSet> set(nullptr);
	TSet sBuf(1);
	int32_t menuValue;

	do {
		system("cls");
		std::cout << "================Множество================" << std::endl << "Текущее множество: ";
		if (set) {
			std::cout << *set << std::endl;
		} else {
			std::cout << "Множество не инициализировано" << std::endl;
		}

		std::cout
			<< "1.  Создать множество по строке" << std::endl
			<< "2.  Создать пустое множество" << std::endl
			<< "3.  Добавить элемент" << std::endl
			<< "4.  Удалить элемент" << std::endl
			<< "5.  Объединить множнство" << std::endl
			<< "6.  Пересечь множество" << std::endl
			<< "-1. Выйти" << std::endl
			<< "Введите номер: ";
		std::cin >> menuValue;

		switch (menuValue) {
		case 1:
			std::cout << "Мощность: ";
			std::cin >> menuValue;
			set = std::make_unique<TSet>(menuValue);
			std::cout << "Множество: ";
			std::cin >> *set;
			break;
		case 2:
			std::cout << "Мощность: ";
			std::cin >> menuValue;
			set = std::make_unique<TSet>(menuValue);
			break;
		case 3:
			std::cout << "Значение: ";
			std::cin >> menuValue;
			set->InsElem(static_cast<uint32_t>(menuValue));
			break;
		case 4:
			std::cout << "Значение: ";
			std::cin >> menuValue;
			set->DelElem(static_cast<uint32_t>(menuValue));
			break;
		case 5:
			std::cout << "Множество: ";
			sBuf = TSet(set->GetMaxPower());
			std::cin >> sBuf;
			*set = *set | sBuf;
			break;
		case 6:
			std::cout << "Множество: ";
			sBuf = TSet(set->GetMaxPower());
			std::cin >> sBuf;
			*set = *set & sBuf;
			break;
		}
	} while (menuValue != -1);

	return 0;
}
