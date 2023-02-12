#pragma once

#include <cstdint>
#include <ncurses.h>
#include <vector>

class Figure;

using std::vector;



class Field
{
public:
	Field() = default;
	Field(WINDOW* win, int height, int width);
	void redraw() const;
	bool checkFullRow() const;

private:
	WINDOW* win_;
	int height_;
	int width_;
	vector<vector<bool>> field_;
	friend Figure;
};
