#pragma once
#include "TBitField.h"
#include <string>

class TSet {
private:
	uint32_t MaxPower;
	TBitField BitField;
public:
	TSet(int32_t size);
	TSet(const TSet& s);
	TSet(const TBitField& bf);
	operator TBitField();

	uint32_t GetMaxPower() const;
	void InsElem(const uint32_t n);
	void DelElem(const uint32_t n);
	bool IsMember(const uint32_t n) const;

	bool operator==(const TSet& s) const;
	TSet& operator=(const TSet& s);
	TSet operator+(const uint32_t n) const;
	TSet operator-(const uint32_t n) const;
	TSet operator|(const TSet& s) const;
	TSet operator&(const TSet& s) const;
	TSet operator~();

	friend std::istream& operator>>(std::istream& in, TSet& s);
	friend std::ostream& operator<<(std::ostream& out, const TSet& s);
};
