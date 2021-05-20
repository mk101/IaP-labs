#include "GameManager.h"

int wmain(int argc, wchar_t* argv[]) {
	std::locale::global(std::locale("Russian_Russia"));
	GameManager gm(10, 10, 4, 4, 2, 1000);

	gm.StartLoop();

	return 0;
}
