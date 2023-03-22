#pragma once

#include <cstdint>

enum struct RotationDirection { clockwise, counterclockwise };

RotationDirection& operator !(RotationDirection& rd);



class Bits4x4
{
public:
	Bits4x4() = default;
	explicit Bits4x4(uint8_t value) : data_ {value} {}

	void setBit(uint8_t row, uint8_t col);
	void clearBit(uint8_t row, uint8_t col);
	void flipBit(uint8_t row, uint8_t col);

	bool get(uint8_t row, uint8_t col) const;
	void set(uint8_t row, uint8_t col, bool value);
	void set(uint16_t value) { data_ = value; }

	void rotate(RotationDirection rd);
//	Bits4x4 rotate(RotationDirection rd) const;

private:
	uint16_t data_ = 0;		// Little-endian supposed
};
