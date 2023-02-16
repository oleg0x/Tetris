#pragma once

#include "bits4x4.h"
#include "field.h"
#include <ncurses.h>
#include <utility>



class Figure
{
public:
	Figure(Field& field, uint8_t figure_type);

	std::pair<int, int> getYX() const;
	bool getBits(int i, int j) const;

	bool isMoveable() const;

	void show() const;
	void hide() const;

	void move(int dy, int dx);		// dy, dx should only be -1, +1
	void drop();

	void rotate(RotationDirection rd);

//private:
	void draw() const;

	Field& field_;
	Bits4x4 fig_;
	int x_, y_;
	short int color_;
	bool moveable_ = true;
};
