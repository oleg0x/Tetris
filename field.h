#pragma once

#include <cstdint>
#include <ncurses.h>
#include <vector>

using std::vector;



class Field
{
public:
	Field() = default;
	Field(WINDOW* win, uint16_t height, uint16_t width);
	void redraw() const;
	bool checkFullRow() const;

private:
	WINDOW* win_;
	uint16_t height_;
	uint16_t width_;
	vector<vector<bool>> field_;
};
