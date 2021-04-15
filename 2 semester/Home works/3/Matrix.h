#pragma once

#include <cassert>
#include <iostream>
#include <cmath>

typedef unsigned int uint;

class Matrix {
private:
	double* Array;
	uint N;
public:
	Matrix(uint n);
	Matrix(double** arr, uint n);
	Matrix(double* arr, uint n);
	Matrix(const Matrix& m);
	~Matrix();

	Matrix& operator=(const Matrix& m);
	Matrix operator+(const Matrix& m) const;
	Matrix operator*(const Matrix& m) const;
	Matrix operator*(const double& k) const;
	Matrix operator/(const Matrix& m) const;

	double& At(const uint& i, const uint& j) const;
	double Det() const;

	Matrix Minor(uint x, uint y) const;
	Matrix Transpose() const;
	Matrix Inverse() const;
	bool IsDiagonalPredominance() const;

	friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
	friend std::istream& operator>>(std::istream& in, Matrix& m);
};
