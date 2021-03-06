#include "Vector3D.h"
#include <algorithm>

Vector3D::Vector3D(double x, double y, double z) {
	this->X = x;
	this->Y = y;
	this->Z = z;
}

Vector3D::Vector3D(double x, double y) {
	this->X = x;
	this->Y = y;
	this->Z = 0;
}

Vector3D::Vector3D(double x) {
	this->X = x;
	this->Y = 0;
	this->Z = 0;
}

Vector3D::Vector3D() {
	this->X = 0;
	this->Y = 0;
	this->Z = 0;
}

Vector3D::Vector3D(const Vector3D& v) {
	this->X = v.X;
	this->Y = v.Y;
	this->Z = v.Z;
}

void Vector3D::SetCoordinates(double x, double y, double z) {
	this->X = x;
	this->Y = y;
	this->Z = z;
}

void Vector3D::SetX(double value) {
	this->X = value;
}

void Vector3D::SetY(double value) {
	this->Y = value;
}

void Vector3D::SetZ(double value) {
	this->Z = value;
}

double Vector3D::GetX() const {
	return this->X;
}

double Vector3D::GetY() const {
	return this->Y;
}

double Vector3D::GetZ() const {
	return this->Z;
}

double Vector3D::Lenght() const {
	return std::sqrt(std::pow(this->X, 2.0) + std::pow(this->Y, 2.0) + std::pow(this->Z, 2.0));
}

Vector3D& Vector3D::operator=(const Vector3D& v) {
	if (*this == v) {
		return *this;
	}

	this->X = v.X;
	this->Y = v.Y;
	this->Z = v.Z;

	return *this;
}

Vector3D Vector3D::operator+(const Vector3D& v) const {
	return Vector3D(this->X + v.X, this->Y + v.Y, this->Z + v.Z);
}

Vector3D Vector3D::operator-(const Vector3D& v) const {
	return *this + v * (-1);
}

double Vector3D::operator*(const Vector3D& v) const {
	return this->X * v.X + this->Y * v.Y + this->Z * v.Z;
}

Vector3D Vector3D::operator*(int value) const {
	return Vector3D(this->X * value, this->Y * value, this->Z * value);
}

Vector3D Vector3D::operator*(double value) const {
	return Vector3D(this->X * value, this->Y * value, this->Z * value);
}

bool Vector3D::operator>(const Vector3D& v) const {
	return this->Lenght() > v.Lenght();
}

bool Vector3D::operator>=(const Vector3D& v) const {
	return this->Lenght() >= v.Lenght();
}

bool Vector3D::operator<(const Vector3D& v) const {
	return this->Lenght() < v.Lenght();
}

bool Vector3D::operator<=(const Vector3D& v) const {
	return this->Lenght() <= v.Lenght();
}

bool Vector3D::operator==(const Vector3D& v) const {
	return this->Lenght() == v.Lenght();
}

bool Vector3D::operator!=(const Vector3D& v) const {
	return this->Lenght() != v.Lenght();
}

std::istream& operator>>(std::istream& in, Vector3D& v) {
	in >> v.X;
	in >> v.Y;
	in >> v.Z;

	return in;
}

std::ostream& operator<<(std::ostream& out, const Vector3D& v) {
	out << "{ " << v.X << ", " << v.Y << ", " << v.Z << " }";
	
	return out;
}
