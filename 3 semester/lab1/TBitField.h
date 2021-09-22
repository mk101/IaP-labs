#pragma once
#include <iostream>
#include <algorithm>
#include <bitset>
#include <cassert>

class TBitField {
private:
	uint32_t BitLen;
	uint32_t MemLen;
	uint32_t* pMem;
	int32_t GetMemIndex(const int32_t n) const;
	uint32_t GetMemMask(const int32_t n) const;
public:
	TBitField(uint32_t len);
	TBitField(const TBitField& bf);
	~TBitField();

	uint32_t GetLength() const;
	void SetBit(const int32_t n);
	void ClearBit(const int32_t n);
	uint32_t GetBit(const int32_t n) const;

	bool operator==(const TBitField& bf) const;
	TBitField& operator=(const TBitField& bf);
	TBitField operator&(const TBitField& bf) const;
	TBitField operator|(const TBitField& bf) const;
	TBitField operator~() const;

	friend std::istream& operator>> (std::istream& in, TBitField& bf);
	friend std::ostream& operator<< (std::ostream& out, const TBitField& bf);
};
