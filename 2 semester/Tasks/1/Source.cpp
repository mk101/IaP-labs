#include "Vector3D.h"

int main() {
	Vector3D i = Vector3D(1);
	Vector3D j = Vector3D(0, 1);
	Vector3D k = Vector3D(0, 0, 1);

	Vector3D a = Vector3D(1, 7, 2.4);
	Vector3D b = Vector3D(7, 3.5, 1);

	std::cout << "i + j + k: " << i + j + k << std::endl;
	std::cout << "a * b: " << a * b << std::endl;
	std::cout << "a - b: " << a - b << std::endl;
	std::cout << "a * 6: " << a * 6 << std::endl;
	std::cout << "a * 4.2: " << a * 4.2 << std::endl;

	Vector3D temp = a;
	std::cout << "temp * a: " << temp * a << std::endl;

	std::cout << "lenght a: " << a.Lenght() << std::endl;
	std::cout << "lenght b: " << b.Lenght() << std::endl;

	std::cout << "a > b: " << (a > b) << std::endl;
	std::cout << "a >= b: " << (a >= b) << std::endl;
	std::cout << "a < b: " << (a < b) << std::endl;
	std::cout << "a <= b: " << (a <= b) << std::endl;
	std::cout << "a == b: " << (a == b) << std::endl;
	std::cout << "a != b: " << (a != b) << std::endl;

	system("pause");
	return 0;
}