#pragma once

#include "bits4x4.h"
#include <ncurses.h>
#include <utility>

class Field;


class Figure
{
public:
	Figure(Field& field, uint8_t figure_type);

	std::pair<int, int> getYX() const;
	bool getBit(int i, int j) const;

	bool isMoveable() const;

	void show() const;
	void hide() const;

	void move(int dy, int dx);		// dy, dx should only be -1, +1
	void drop();

	void rotate(RotationDirection rd);

private:
	void draw() const;

	Field& field_;
	Bits4x4 fig_;
	int x_ = 6;
	int y_ = 0;
	short int color_;
	bool moveable_ = true;
};
