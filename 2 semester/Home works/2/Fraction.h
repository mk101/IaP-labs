#pragma once

#include <iostream>
#include <cassert>
#include <algorithm>

class Fraction {
private:
	int Denum;
public:
	int Num;

	Fraction();
	Fraction(int num, int denum);
	Fraction(const Fraction& f);

	void SetDenum(int value);
	int GetDenum() const;

	Fraction Reduce() const;

	Fraction operator=(const Fraction& f);
	Fraction operator=(int number);

	Fraction operator+(const Fraction& f);
	Fraction operator+(int number);

	Fraction operator-(const Fraction& f);
	Fraction operator-(int number);

	Fraction operator*(const Fraction& f);
	Fraction operator*(int number);

	Fraction operator/(const Fraction& f);
	Fraction operator/(int number);

	Fraction operator++();
	Fraction operator++(int);

	Fraction operator--();
	Fraction operator--(int);

	friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
	friend std::istream& operator>>(std::istream& in, Fraction& f);

	Fraction operator+=(const Fraction& f);
	Fraction operator-=(const Fraction& f);
	Fraction operator*=(const Fraction& f);
	Fraction operator/=(const Fraction& f);

	bool operator==(const Fraction& f);
	bool operator!=(const Fraction& f);
	bool operator>(const Fraction& f);
	bool operator>=(const Fraction& f);
	bool operator<(const Fraction& f);
	bool operator<=(const Fraction& f);

	Fraction operator[](int power);
};