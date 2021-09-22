#include "TSet.h"

TSet::TSet(int32_t size) : MaxPower(size), BitField(size) {}

TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField() {
	TBitField tmp(this->BitField);
	return tmp;
}

uint32_t TSet::GetMaxPower() const {
	return MaxPower;
}

void TSet::InsElem(const uint32_t n) {
	BitField.SetBit(n);
}

void TSet::DelElem(const uint32_t n) {
	BitField.ClearBit(n);
}

bool TSet::IsMember(const uint32_t n) const {
	return BitField.GetBit(n) > 0;
}

bool TSet::operator==(const TSet& s) const {
	return MaxPower == s.MaxPower && BitField == s.BitField;
}

TSet& TSet::operator=(const TSet& s) {
	BitField = s.BitField;
	MaxPower = s.MaxPower;

	return *this;
}

TSet TSet::operator+(const uint32_t n) const {
	TSet s(*this);
	s.InsElem(n);
	return s;
}

TSet TSet::operator-(const uint32_t n) const {
	TSet s(*this);
	s.DelElem(n);
	return s;
}

TSet TSet::operator|(const TSet& s) const {
	return TSet(BitField | s.BitField);
}

TSet TSet::operator&(const TSet& s) const {
	return TSet(BitField & s.BitField);
}

TSet TSet::operator~() {
	return TSet(~BitField);
}

std::istream& operator>>(std::istream& in, TSet& s) {
	int32_t temp;
	char ch = '\0';

	s.BitField = TBitField(s.MaxPower);

	do {
		in >> ch;
	} while (ch != '{');

	do {
		in >> temp;
		s.InsElem(temp);
		do { in >> ch; } while (ch != ',' && ch != '}');
	} while (ch != '}');

	return in;
}

std::ostream& operator<<(std::ostream& out, const TSet& s) {
	out << '{';
	std::string buf;
	for (int32_t i = 0; i < s.GetMaxPower(); i++) {
		if (s.IsMember(i)) {
			buf += std::to_string(i);
			buf += ", ";
		}
	}

	out << (!buf.empty() ? std::string(buf.begin(), buf.end() - 2) : std::string(" ")) << '}';

	return out;
}
