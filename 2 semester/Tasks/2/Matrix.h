#pragma once

#include <cassert>
#include <iostream>
#include <cmath>

typedef unsigned int uint;

class Matrix {
private:
	int* Array;
	uint N;
public:
	Matrix(uint n);
	Matrix(int** arr, uint n);
	Matrix(int* arr, uint n);
	Matrix(const Matrix& m);
	~Matrix();

	Matrix& operator=(const Matrix& m);
	Matrix operator+(const Matrix& m) const;
	Matrix operator*(const Matrix& m) const;
	Matrix operator*(const int& k) const;

	int& At(const uint& i, const uint& j) const;

	Matrix Transpose() const;
	bool IsDiagonalPredominance() const;

	friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
	friend std::istream& operator>>(std::istream& in, Matrix& m);
};
