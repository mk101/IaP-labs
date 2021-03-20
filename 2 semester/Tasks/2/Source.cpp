#include "Matrix.h"

int main() {
	int a[] = {1,2,3,4};
	int b[] = { 7,36,12,8 };

	Matrix A = Matrix(a, 2);
	Matrix B = Matrix(b, 2);

	std::cout << A << B;

	std::cout << A + B;
	std::cout << A * B;
	std::cout << A * 5;
	std::cout << A.Transpose();
	std::cout << A.IsDiagonalPredominance();

	return 0;
}
