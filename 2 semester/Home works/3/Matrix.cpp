#include "Matrix.h"
#include <iostream>

Matrix::Matrix(uint n) {
	assert(n > 0);

	this->N = n;
	this->Array = new double[n * n];

	for (uint i = 0; i < n; i++) {
		for (uint j = 0; j < n; j++) {
			this->At(i, j) = 0;
		}
	}
}

Matrix::Matrix(double** arr, uint n) {
	assert(n > 0);

	this->N = n;
	this->Array = new double[n * n];

	for (uint i = 0; i < n; i++) {
		for (uint j = 0; j < n; j++) {
			this->At(i, j) = arr[i][j];
		}
	}
}

Matrix::Matrix(double* arr, uint n) {
	assert(n > 0);

	this->N = n;
	this->Array = new double[n * n];
	std::cout << Array << std::endl;

	for (uint i = 0; i < n; i++) {
		for (uint j = 0; j < n; j++) {
			this->At(i, j) = arr[i * n + j];
		}
	}
}

Matrix::Matrix(const Matrix& m) {
	this->N = m.N;
	this->Array = new double[this->N * this->N];

	for (uint i = 0; i < this->N; i++) {
		for (uint j = 0; j < this->N; j++) {
			this->At(i, j) = m.At(i, j);
		}
	}
}

Matrix::~Matrix() {
	std::cout << Array << std::endl;
	delete[] this->Array;
	this->Array = nullptr;
	this->N = 0;
}

Matrix& Matrix::operator=(const Matrix& m) {
	this->N = m.N;
	this->Array = new double[N * N];

	for (uint i = 0; i < this->N; i++) {
		for (uint j = 0; j < this->N; j++) {
			this->At(i, j) = m.At(i, j);
		}
	}

	return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
	assert(this->N == m.N);

	Matrix res = Matrix(*this);
	for (uint i = 0; i < this->N; i++) {
		for (uint j = 0; j < this->N; j++) {
			res.At(i, j) += m.At(i, j);
		}
	}

	return res;
}

Matrix Matrix::operator*(const Matrix& m) const {
	assert(this->N == m.N);
	Matrix res = Matrix(m.N);

	for (uint i = 0; i < m.N; i++) {
		for (uint j = 0; j < m.N; j++) {
			double r = 0;
			for (uint k = 0; k < m.N; k++) {
				r += this->At(i, k) * m.At(k, j);
			}
			res.At(i, j) = r;
		}
	}

	return res;
}

Matrix Matrix::operator*(const double& k) const {
	Matrix res = Matrix(*this);

	for (uint i = 0; i < res.N; i++) {
		for (uint j = 0; j < res.N; j++) {
			res.At(i, j) *= k;
		}
	}

	return res;
}

Matrix Matrix::operator/(const Matrix& m) const {
	Matrix res = Matrix(*this);
	Matrix inv = m.Inverse();
	
	return res*inv;
}

double& Matrix::At(const uint& i, const uint& j) const {
	assert(i >= 0 && i < this->N);
	assert(j >= 0 && j < this->N);

	return this->Array[i * this->N + j];
}


double Matrix::Det() const {
	if (this->N == 1) {
		return At(0, 0);
	}
	else if (this->N == 2) {
		return At(0, 0) * At(1, 1) - At(0, 1) * At(1, 0);
	}
	else if (this->N == 3) {
		return At(0, 0) * At(1, 1) * At(2, 2) + At(0, 2) * At(1, 0) * At(2, 1) + At(2, 0) * At(0, 1) * At(1, 2) - (At(2, 0) * At(1, 1) * At(0, 2) + At(0, 0) * At(2, 1) * At(1, 2) + At(2, 2) * At(1, 0) * At(0, 1));
	}

	int sign = 1;
	double res = 0;
	for (int i = 0; i < N; i++) {
		res += sign * At(0,i) * Minor(0, i).Det();
		sign *= -1;
	}

	return res;
}


Matrix Matrix::Minor(uint x, uint y) const {
	Matrix m = Matrix(N - 1);
	uint ki = 0, kj = 0;
	for (uint i = 0; i < N; i++) {
		if (i == x) continue;
		for (uint j = 0; j < N; j++) {
			if (j == y) continue;
			m.At(ki, kj) = At(i, j);
			kj++;
		}
		kj = 0;
		ki++;
	}

	return m;
}

Matrix Matrix::Transpose() const {
	Matrix m = Matrix(this->N);

	for (uint i = 0; i < this->N; i++) {
		for (uint j = 0; j < this->N; j++) {
			m.At(i, j) = this->At(j, i);
		}
	}

	return m;
}

Matrix Matrix::Inverse() const {
	Matrix A = Matrix(N);
	int sign = 1;
	for (uint i = 0; i < N; i++) {
		for (uint j = 0; j < N; j++) {
			sign = pow(-1, i + j);
			A.At(i, j) = sign * Minor(i, j).Det();
		}
	}

	A = A.Transpose() * (1 / Det());
	return A;
}

bool Matrix::IsDiagonalPredominance() const {
	int sum = 0;

	for (uint i = 0; i < this->N; i++) {
		sum = 0;
		for (uint j = 0; j < this->N; j++) {
			if (i != j) {
				sum += std::abs(this->At(i, j));
			}
		}
		if (std::abs(this->At(i, i)) < sum) {
			return false;
		}
	}

	return true;
}

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
	out << std::endl;
	for (uint i = 0; i < m.N; i++) {
		out << "| ";
		for (uint j = 0; j < m.N; j++) {
			out << m.At(i, j) << " ";
		}
		out << "|" << std::endl;
	}

	return out;
}

std::istream& operator>>(std::istream& in, Matrix& m) {
	in >> m.N;

	delete[] m.Array;
	m.Array = new double[m.N * m.N];
	for (uint i = 0; i < m.N; i++) {
		for (uint j = 0; j < m.N; j++) {
			in >> m.N;
		}
	}

	return in;
}
