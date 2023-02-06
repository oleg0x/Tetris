#pragma once

#include "bits4x4.h"
#include <ncurses.h>

//enum struct HorizMove {left = -1, right = +1};



class Figure
{
public:
	Figure(WINDOW* win, uint8_t figure_type);

	void show() ;
	void hide() const;

	void moveLeft();
	void moveRight();
	void moveDown();
	void moveUp();
	void drop();

	void rotateClockwise();
	void rotateCounterclockwise();

private:
	void draw() const;

	WINDOW* const win_;
	Bits4x4 fig_;
	short int color_;
	uint16_t x_, y_;
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
