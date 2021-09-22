#include "TBitField.h"

int32_t TBitField::GetMemIndex(const int32_t n) const {
	return n >> 5;
}

uint32_t TBitField::GetMemMask(const int32_t n) const {
	return 1 << (n & (8 * sizeof(uint32_t) - 1));
}


TBitField::TBitField(uint32_t len) : BitLen(len) {
	assert(len > 0);
	MemLen = (len + 8 * sizeof(uint32_t) - 1) >> (sizeof(uint32_t) + 1);
	pMem = new uint32_t[MemLen];
	for (uint32_t i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf) {
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;

	this->pMem = new uint32_t[bf.MemLen];
	for (uint32_t i = 0; i < bf.MemLen; i++) {
		this->pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField() {
	delete[] pMem;
}

uint32_t TBitField::GetLength() const {
	return BitLen;
}

void TBitField::SetBit(const int32_t n) {
	assert(n < BitLen);
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClearBit(const int32_t n) {
	assert(n < BitLen);
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

uint32_t TBitField::GetBit(const int32_t n) const {
	assert(n < BitLen);
	return (uint32_t)((pMem[GetMemIndex(n)] & GetMemMask(n)) > 0);
}

bool TBitField::operator==(const TBitField& bf) const {
	if (pMem != bf.pMem) {
		return false;
	}
	for (uint32_t i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i])
			return false;
	}

	return true;
}

TBitField& TBitField::operator=(const TBitField& bf) {
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	delete[] this->pMem;

	this->pMem = new uint32_t[bf.MemLen];
	for (uint32_t i = 0; i < bf.MemLen; i++) {
		this->pMem[i] = bf.pMem[i];
	}

	return *this;
}

TBitField TBitField::operator&(const TBitField& bf) const {
	assert(MemLen == bf.MemLen);
	assert(BitLen == bf.BitLen);

	TBitField buf = TBitField(*this);
	for (uint32_t i = 0; i < MemLen; i++) {
		buf.pMem[i] &= bf.pMem[i];
	}

	return buf;
}

TBitField TBitField::operator|(const TBitField& bf) const {
	assert(MemLen == bf.MemLen);
	assert(BitLen == bf.BitLen);

	TBitField buf = TBitField(*this);
	for (uint32_t i = 0; i < MemLen; i++) {
		buf.pMem[i] |= bf.pMem[i];
	}

	return buf;
}

TBitField TBitField::operator~() const {
	TBitField buf = TBitField(*this);
	for (uint32_t i = 0; i < MemLen; i++) {
		buf.pMem[i] = ~(buf.pMem[i]);
	}

	return buf;
}

void updateMem(uint32_t*& mem, uint32_t parts) {
	assert(parts != 0);
	uint32_t* buf = new uint32_t[parts];
	for (uint32_t i = 0; i < parts - 1; i++) {
		buf[i] = mem[i];
	}
	buf[parts - 1] = 0;
	delete[] mem;
	mem = buf;
}

std::istream& operator>>(std::istream& in, TBitField& bf) {
	uint32_t* mem = new uint32_t[1];
	mem[0] = 0;
	uint32_t size = 0;
	char input;
	do {
		in >> input;
		if (input == '1') {
			mem[size >> 5] |= 1 << (size & (8 * sizeof(uint32_t) - 1));
		} else if (input != '0') {
			break;
		}
		//		std::cout << mem[0] << std::endl;
		size++;
		if (size % 32 == 0) {

			updateMem(mem, (size >> 5) + 1);
		}
	} while (input == '0' || input == '1');

	bf = TBitField(size);
	delete[] bf.pMem;
	bf.pMem = mem;

	return in;
}

std::ostream& operator<<(std::ostream& out, const TBitField& bf) {
	for (uint32_t i = 0; i < bf.BitLen; i++) {
		out << bf.GetBit(i);
		if (i % (8 * sizeof(uint32_t)) == 0 && i != 0) {
			out << ' ';
		}
	}

	return out;
}