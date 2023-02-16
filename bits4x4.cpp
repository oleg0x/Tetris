#include "bits4x4.h"



RotationDirection& operator !(RotationDirection& rd)
{
	if ( rd == RotationDirection::clockwise )
		return (rd = RotationDirection::counterclockwise);
	return (rd = RotationDirection::clockwise);
}



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



void Bits4x4::rotate(RotationDirection rd)
{
    const uint16_t n = 3;
    bool a, b, c, d;
	for ( uint16_t i = 0; i < 2; ++i )
		for ( uint16_t j = i; j < 3 - i; ++j )
		{
			a = get(i, j);
			b = get(j, n - i);
			c = get(n - i, n - j);
			d = get(n - j, i);
			if ( rd == RotationDirection::clockwise )
			{
				set(i, j, d);
				set(j, n - i, a);
				set(n - i, n - j, b);
				set(n - j, i, c);
			}
			else
			{
				set(i, j, b);
				set(j, n - i, c);
				set(n - i, n - j, d);
				set(n - j, i, a);
			}
		}
}



/*Bits4x4 Bits4x4::rotate(RotationDirection rd) const
{
	Bits4x4 res;
	for ( uint16_t i = 0; i < 4; ++i )
		for ( uint16_t j = 0; j < 4; ++j )
		{
			const bool b = get(i, j);
			if ( rd == RotationDirection::clockwise )
				res.set(j, 3 - i, b);
			else
				res.set(3 - j, i, b);
		}
	return res;
}*/
