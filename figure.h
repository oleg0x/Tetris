#pragma once

#include "bits4x4.h"
#include "field.h"
#include <ncurses.h>

//enum struct HorizMove {left = -1, right = +1};



class Figure
{
public:
	Figure(Field& field, uint8_t figure_type);

	bool isMoveable() const;

	void show() ;
	void hide() const;

	void move(int dy, int dx);		// dy, dx should only be -1, +1
	void drop();

	void rotateClockwise();
	void rotateCounterclockwise();

private:
	bool isValidPlacement(int y, int x) const;
	void draw() const;

	Field& field_;
	Bits4x4 fig_;
	int x_, y_;
	short int color_;
	bool moveable_ = true;
};


/*
class FigureSquare
{
public:

private:

};



class FigureStraight
{
public:

private:

};



class FigureL
{
public:

private:

};



class FigureLMirrored
{
public:

private:

};



class FigureZ
{
public:

private:

};



class FigureZMirrored
{
public:

private:

};
*/
