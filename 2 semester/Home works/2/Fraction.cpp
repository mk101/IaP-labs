#include "Fraction.h"

Fraction::Fraction() {
	this->Num = 0;
	this->Denum = 1;
}

Fraction::Fraction(int num, int denum) {
	assert(denum != 0);

	this->Num = num;
	this->Denum = denum;
}

Fraction::Fraction(const Fraction& f) {
	this->Num = f.Num;
	this->Denum = f.Denum;
}

void Fraction::SetDenum(int value) {
	assert(value != 0);

	this->Denum = value;
}

int Fraction::GetDenum() const {
	return this->Denum;
}

Fraction Fraction::Reduce() const {
	Fraction f = Fraction(this->Num, this->Denum);
	int i = 2;

	while (i <= std::min(std::abs(f.Num), f.Denum)) {
		if (f.Num % i == 0 && f.Denum % i == 0) {
			f.Num /= i;
			f.Denum /= i;
			i = 2;
			continue;
		}
		i++;
	}

	return f;
}

Fraction Fraction::operator=(const Fraction& f) {
	this->Num = f.Num;
	this->Denum = f.Denum;

	return *this;
}

Fraction Fraction::operator=(int number) {
	this->Num = number;
	this->Denum = 1;
	return *this;
}

Fraction Fraction::operator+(const Fraction& f) {
	if (this->Denum == f.Denum) {
		return Fraction(this->Num + f.Num, this->Denum).Reduce();
	}
	else {
		return Fraction(this->Num * f.Denum + f.Num * this->Denum, this->Denum * f.Denum).Reduce();
	}
}

Fraction Fraction::operator+(int number) {
	return Fraction(this->Num + number * this->Denum, this->Denum);
}

Fraction Fraction::operator-(const Fraction& f) {
	return Fraction(this->Num * f.Denum - f.Num * this->Denum, this->Denum * f.Denum).Reduce();
}

Fraction Fraction::operator-(int number) {
	return Fraction(this->Num - this->Denum, this->Denum).Reduce();
}

Fraction Fraction::operator*(const Fraction& f) {
	return Fraction(this->Num * f.Num, this->Denum * f.Denum).Reduce();
}

Fraction Fraction::operator*(int number) {
	return Fraction(this->Num * number, this->Denum).Reduce();
}

Fraction Fraction::operator/(const Fraction& f) {
	assert(f.Num != 0);
	return Fraction(this->Num * f.Denum, this->Denum * f.Num).Reduce();
}

Fraction Fraction::operator/(int number) {
	assert(number != 0);
	return Fraction(this->Num, this->Denum * number).Reduce();
}

Fraction Fraction::operator++() {
	this->Num += this->Denum;
	return *this;
}

Fraction Fraction::operator++(int) {
	Fraction old = Fraction(this->Num, this->Denum);

	++(*this);
	return old;
}

Fraction Fraction::operator--() {
	this->Num -= this->Denum;
	return *this;
}

Fraction Fraction::operator--(int) {
	Fraction old = Fraction(this->Num, this->Denum);

	--(*this);
	return old;
}

Fraction Fraction::operator+=(const Fraction& f) {
	*this = *this + f;
	return *this;
}

Fraction Fraction::operator-=(const Fraction& f) {
	*this = *this - f;
	return *this;
}

Fraction Fraction::operator*=(const Fraction& f) {
	*this = *this * f;
	return *this;
}

Fraction Fraction::operator/=(const Fraction& f) {
	*this = *this / f;
	return *this;
}

bool Fraction::operator==(const Fraction& f) {
	if (this->Denum == f.Denum && this->Num == f.Num) {
		return true;
	}
	else if (this->Denum != f.Denum && (this->Num * f.Denum) == (f.Num * this->Denum)) {
		return true;
	}
	else {
		return false;
	}
}

bool Fraction::operator!=(const Fraction& f) {
	if (this->Denum == f.Denum && this->Num != f.Num) {
		return true;
	}
	else if (this->Denum != f.Denum && (this->Num * f.Denum) != (f.Num * this->Denum)) {
		return true;
	}
	else {
		return false;
	}
}

bool Fraction::operator>(const Fraction& f) {
	if (this->Denum == f.Denum && this->Num > f.Num) {
		return true;
	}
	else if (this->Denum != f.Denum && (this->Num * f.Denum) > (f.Num * this->Denum)) {
		return true;
	}
	else {
		return false;
	}
}

bool Fraction::operator>=(const Fraction& f) {
	if (this->Denum == f.Denum && this->Num >= f.Num) {
		return true;
	}
	else if (this->Denum != f.Denum && (this->Num * f.Denum) >= (f.Num * this->Denum)) {
		return true;
	}
	else {
		return false;
	}
}

bool Fraction::operator<(const Fraction& f) {
	if (this->Denum == f.Denum && this->Num < f.Num) {
		return true;
	}
	else if (this->Denum != f.Denum && (this->Num * f.Denum) < (f.Num * this->Denum)) {
		return true;
	}
	else {
		return false;
	}
}

bool Fraction::operator<=(const Fraction& f) {
	if (this->Denum == f.Denum && this->Num <= f.Num) {
		return true;
	}
	else if (this->Denum != f.Denum && (this->Num * f.Denum) <= (f.Num * this->Denum)) {
		return true;
	}
	else {
		return false;
	}
}

Fraction Fraction::operator[](int power) {
	return Fraction(int(std::pow(this->Num, power)), int(std::pow(this->Denum, power)));
}

std::ostream& operator<<(std::ostream& out, const Fraction& f) {
	out << f.Num << '/' << f.Denum;
	return out;
}

std::istream& operator>>(std::istream& in, Fraction& f) {
	char separator;
	in >> f.Num >> separator;
	assert(separator == '/');
	in >> f.Denum;

	return in;
}