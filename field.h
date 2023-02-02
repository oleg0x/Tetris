#pragma once

#include <cstdint>
#include <ncurses.h>
#include <vector>

using std::vector;



class Field
{
public:
	Field() = default;
	Field(WINDOW* win, uint_fast16_t height, uint_fast16_t width,
		  uint_fast16_t beg_y, uint_fast16_t beg_x);
	void redraw() const;
	bool checkFullRow() const;

private:
	WINDOW* win_;
	uint_fast16_t height_;
	uint_fast16_t width_;
	uint_fast16_t beg_y_;
	uint_fast16_t beg_x_;
	vector<vector<bool>> field_;
};
