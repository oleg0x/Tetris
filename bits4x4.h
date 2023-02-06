#pragma once

#include <cstdint>



class Bits4x4
{
public:
	Bits4x4() = default;
	Bits4x4(uint8_t value) : data_ {value} {}

	void setBit(uint8_t row, uint8_t col);
	void clearBit(uint8_t row, uint8_t col);
	void flipBit(uint8_t row, uint8_t col);

	bool get(uint8_t row, uint8_t col) const;
	void set(uint8_t row, uint8_t col, bool value);
	void set(uint16_t value) { data_ = value; }

private:
	uint16_t data_ = 0;		// Little-endian supposed
};
