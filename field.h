#pragma once

#include <cstdint>
#include <ncurses.h>
#include <vector>

using std::vector;

class Figure;



class Field
{
public:
	Field() = default;
	Field(WINDOW* win, int height, int width);
	void redraw() const;
	void eraseFullRows();
	void makeFigureStatic(Figure& fig);
	bool isValidPlacement(const Figure& fig, int dy, int dx) const;

private:
	WINDOW* win_;
	int height_;
	int width_;
	vector<vector<bool>> field_;
	friend Figure;
};
