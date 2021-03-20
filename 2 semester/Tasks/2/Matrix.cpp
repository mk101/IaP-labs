#include "Matrix.h"

Matrix::Matrix(uint n) {
	assert(n > 0);

	this->N = n;
	this->Array = new int[n * n];

	for (uint i = 0; i < n; i++) {
		for (uint j = 0; j < n; j++) {
			this->At(i, j) = 0;
		}
	}
}

Matrix::Matrix(int** arr, uint n) {
	assert(n > 0);

	this->N = n;
	this->Array = new int[n * n];

	for (uint i = 0; i < n; i++) {
		for (uint j = 0; j < n; j++) {
			this->At(i, j) = arr[i][j];
		}
	}
}

Matrix::Matrix(int* arr, uint n) {
	assert(n > 0);

	this->N = n;
	this->Array = new int[n * n];

	for (uint i = 0; i < n; i++) {
		for (uint j = 0; j < n; j++) {
			this->At(i, j) = arr[i * n + j];
		}
	}
}

Matrix::Matrix(const Matrix& m) {
	this->N = m.N;
	this->Array = new int[this->N * this->N];

	for (uint i = 0; i < this->N; i++) {
		for (uint j = 0; j < this->N; j++) {
			this->At(i, j) = m.At(i, j);
		}
	}
}

Matrix::~Matrix() {
	delete[] this->Array;
	this->Array = nullptr;
	this->N = 0;
}

Matrix& Matrix::operator=(const Matrix& m) {
	this->N = m.N;
	this->Array = new int[N * N];

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
			int r = 0;
			for (uint k = 0; k < m.N; k++) {
				r += this->At(i, k) * m.At(k, j);
			}
			res.At(i, j) = r;
		}
	}

	return res;
}

Matrix Matrix::operator*(const int& k) const {
	Matrix res = Matrix(*this);

	for (uint i = 0; i < res.N; i++) {
		for (uint j = 0; j < res.N; j++) {
			res.At(i, j) *= k;
		}
	}

	return res;
}

int& Matrix::At(const uint& i, const uint& j) const {
	assert(i >= 0 && i < this->N);
	assert(j >= 0 && j < this->N);

	return this->Array[i * this->N + j];
}

Matrix Matrix::Transpose() const {
	Matrix m = Matrix(this->N);

	for (int i = 0; i < this->N; i++) {
		for (int j = 0; j < this->N; j++) {
			m.At(i, j) = this->At(j, i);
		}
	}

	return m;
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
	for (int i = 0; i < m.N; i++) {
		out << "| ";
		for (int j = 0; j < m.N; j++) {
			out << m.At(i, j) << " ";
		}
		out << "|" << std::endl;
	}

	return out;
}

std::istream& operator>>(std::istream& in, Matrix& m) {
	in >> m.N;

	delete[] m.Array;
	m.Array = new int[m.N * m.N];
	for (int i = 0; i < m.N; i++) {
		for (int j = 0; j < m.N; j++) {
			in >> m.N;
		}
	}

	return in;
}
