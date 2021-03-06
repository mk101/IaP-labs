#pragma once
#include <iostream>

class Vector3D {
private:
	double X, Y, Z;
public:
	Vector3D(double x, double y, double z);
	Vector3D(double x, double y);
	Vector3D(double x);
	Vector3D();
	Vector3D(const Vector3D& v);

	void SetCoordinates(double x, double y, double z);
	
	void SetX(double value);
	void SetY(double value);
	void SetZ(double value);

	double GetX() const;
	double GetY() const;
	double GetZ() const;

	double Lenght() const;

	Vector3D& operator=(const Vector3D& v);

	Vector3D operator+(const Vector3D& v) const;
	Vector3D operator-(const Vector3D& v) const;

	double operator*(const Vector3D& v) const;
	Vector3D operator*(int value) const;
	Vector3D operator*(double value) const;

	bool operator>(const Vector3D& v) const;
	bool operator>=(const Vector3D& v) const;
	bool operator<(const Vector3D& v) const;
	bool operator<=(const Vector3D& v) const;
	bool operator==(const Vector3D& v) const;
	bool operator!=(const Vector3D& v) const;

	friend std::istream& operator>>(std::istream& in, Vector3D& v);
	friend std::ostream& operator<<(std::ostream& out, const Vector3D& v);
};
