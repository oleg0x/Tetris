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
	WINDOW* getWindow() const;
	void redraw() const;
	void eraseFullRows();
	void makeFigureStatic(const Figure& fig);
	bool isValidPlacement(const Figure& fig, int dy, int dx) const;

	static const short int fallen_color = 245;			// Gray color

private:
	WINDOW* win_;
	int height_;
	int width_;
	vector<vector<bool>> field_;
};
