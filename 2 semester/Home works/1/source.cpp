#include "Fraction.h"

int main() {

	Fraction a = Fraction(1,64);
	a = 167;
	std::cout << a << std::endl;

	Fraction f = Fraction(6, 4);
	Fraction f2 = Fraction(f);
	f2.Num = 10;
	std::cout << f2 << std::endl;

	std::cout << f + f2 << std::endl;
	std::cout << f - f2 << std::endl;
	std::cout << f * f2 << std::endl;
	std::cout << f / f2 << std::endl;
	//std::cout << f / 0 << std::endl;
	std::cout << f * 0 << std::endl;

	Fraction t = Fraction(1, 2);
	std::cout << ++t << std::endl;
	t = Fraction(1, 2);
	std::cout << t++ << ' ' << t << std::endl;

	std::cout << --t << std::endl;
	t = Fraction(3, 2);
	std::cout << t-- << ' ' << t << std::endl;

	std::cin >> t;
	std::cout << t << std::endl;

	std::cout << std::endl;

	f += t;
	std::cout << f << std::endl;
	f -= t;
	std::cout << f << std::endl;
	f *= t;
	std::cout << f << std::endl;
	f /= t;
	std::cout << f << std::endl;

	std::cout << std::endl;

	f = Fraction(4, 2);
	t = Fraction(6, 4);

	std::cout << "f = t: " << (f == t) << std::endl;
	std::cout << "f != t: " << (f != t) << std::endl;
	std::cout << "f > t: " << (f > t) << std::endl;
	std::cout << "f >= t: " << (f >= t) << std::endl;
	std::cout << "f < t: " << (f < t) << std::endl;
	std::cout << "f <= t: " << (f <= t) << std::endl;

	std::cout << "f^3: " << f[3] << std::endl;

	system("pause");

	return 0;
}
