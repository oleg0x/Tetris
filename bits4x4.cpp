#include "bits4x4.h"



void Bits4x4::setBit(uint8_t row, uint8_t col)
{
	const uint8_t n = 4*(3-row) + 3-col;
	data_ |= (uint16_t)1 << n;
}



void Bits4x4::clearBit(uint8_t row, uint8_t col)
{
	const uint8_t n = 4*(3-row) + 3-col;
	data_ &= ~((uint16_t)1 << n);
}



void Bits4x4::flipBit(uint8_t row, uint8_t col)
{
	const uint8_t n = 4*(3-row) + 3-col;
	data_ ^= (uint16_t)1 << n;
}



bool Bits4x4::get(uint8_t row, uint8_t col) const
{
	const uint8_t n = 4*(3-row) + 3-col;
	bool res = (data_ >> n) & (uint16_t)1;
	return res;
}



void Bits4x4::set(uint8_t row, uint8_t col, bool value)
{
	const uint8_t n = 4*(3-row) + 3-col;
	data_ = (data_ & ~((uint16_t)1 << n)) | ((uint16_t)value << n);
}
