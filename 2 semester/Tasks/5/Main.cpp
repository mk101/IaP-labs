#include <iostream>
#include "Cashbox.h"

int wmain(int argc, wchar_t* argv[]) {
	Cashbox cashbox;

	std::locale::global(std::locale("Russian_Russia"));

	cashbox.Scan("0000");
	cashbox.Scan("0001");
	cashbox.Scan("0002");
	cashbox.Scan("0001");
	cashbox.Scan("0002");

	std::wcout << cashbox.GetReceipt().ToString() << std::endl;

	cashbox.Remove("0002");
	std::wcout << cashbox.GetReceipt().ToString() << std::endl;

	std::wcout << cashbox.GetCost();
	return 0;
}