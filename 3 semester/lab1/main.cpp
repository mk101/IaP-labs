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
		std::cout << "================���������================" << std::endl << "������� ���������: ";
		if (set) {
			std::cout << *set << std::endl;
		} else {
			std::cout << "��������� �� ����������������" << std::endl;
		}

		std::cout
			<< "1.  ������� ��������� �� ������" << std::endl
			<< "2.  ������� ������ ���������" << std::endl
			<< "3.  �������� �������" << std::endl
			<< "4.  ������� �������" << std::endl
			<< "5.  ���������� ���������" << std::endl
			<< "6.  �������� ���������" << std::endl
			<< "-1. �����" << std::endl
			<< "������� �����: ";
		std::cin >> menuValue;

		switch (menuValue) {
		case 1:
			std::cout << "��������: ";
			std::cin >> menuValue;
			set = std::make_unique<TSet>(menuValue);
			std::cout << "���������: ";
			std::cin >> *set;
			break;
		case 2:
			std::cout << "��������: ";
			std::cin >> menuValue;
			set = std::make_unique<TSet>(menuValue);
			break;
		case 3:
			std::cout << "��������: ";
			std::cin >> menuValue;
			set->InsElem(static_cast<uint32_t>(menuValue));
			break;
		case 4:
			std::cout << "��������: ";
			std::cin >> menuValue;
			set->DelElem(static_cast<uint32_t>(menuValue));
			break;
		case 5:
			std::cout << "���������: ";
			sBuf = TSet(set->GetMaxPower());
			std::cin >> sBuf;
			*set = *set | sBuf;
			break;
		case 6:
			std::cout << "���������: ";
			sBuf = TSet(set->GetMaxPower());
			std::cin >> sBuf;
			*set = *set & sBuf;
			break;
		}
	} while (menuValue != -1);

	return 0;
}
