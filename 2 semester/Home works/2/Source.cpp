#include "ArrController.h"
#include "Fraction.h"

int main() {
	Fraction f[2];
	f[0] = Fraction(2, 3);
	f[1] = Fraction(5, 50);
	int d[2] = { 2, 1 };
	ArrController<Fraction, int> a = ArrController<Fraction, int>(f, d, 2);

	std::cout << a.Calculate() << std::endl;

	system("pause");
	return 0;
}