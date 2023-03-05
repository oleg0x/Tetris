#pragma once

#include "field.h"



class Tetris
{
public:
	Tetris(uint16_t height, uint16_t width);
	~Tetris();

	void run();

private:
	uint16_t height_;
	uint16_t width_;
	WINDOW* win_;
	Field field_;
};
