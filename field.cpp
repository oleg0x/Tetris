#include "field.h"
#include "figure.h"
#include <algorithm>
#include <iostream>

using namespace std;



Field::Field(WINDOW* win, int height, int width)
	: win_ {win}
	, height_ {height}
	, width_ {width}
	, field_(height_, vector(width_, false))
{}



WINDOW* Field::getWindow() const
{
	return win_;
}



void Field::redraw() const
{
	wclear(win_);

	const short int border_color = COLOR_WHITE;
	init_pair(1, border_color, border_color);		// (id, fg, bg)
	wattron(win_, COLOR_PAIR(1));
	wborder(win_, 0, 0, ' ', 0, 0, 0, 0, 0);
	wattroff(win_, COLOR_PAIR(1));
	wrefresh(win_);


	init_pair(2, fallen_color, fallen_color);		// (id, fg, bg)
	wattron(win_, COLOR_PAIR(2));
	for ( uint16_t i = 0; i < height_; ++i )
		for ( uint16_t j = 0; j < width_; ++j )
			if ( field_[i][j] )
				mvwprintw(win_, i + 1, 2*j + 1, "  ");
	wrefresh(win_);
	wattroff(win_, COLOR_PAIR(2));
}



void Field::eraseFullRows()
{
	for ( int i = 0; i < height_; )
		if ( !any_of(field_[i].cbegin(), field_[i].cend(), [](bool x){ return !x; }) )
		{
			mvprintw(6, 50, "%d", i);
			auto it = next(field_.begin(), i);
			field_.erase(it);
			field_.insert(field_.begin(), vector<bool>(width_, false));
			--i;
		}
		else
			++i;
}



void Field::makeFigureStatic(const Figure& fig)
{
	auto [y, x] = fig.getYX();
	for ( int i = 0; i < 4; ++i )
		for ( int j = 0; j < 4; ++j )
			if ( y + i < height_ && x + j < width_ )
				field_[y+i][x+j] = field_[y+i][x+j] | fig.getBit(i, j);
	eraseFullRows();
	redraw();
}



bool Field::isValidPlacement(const Figure& fig, int dy, int dx) const
{
	auto [y, x] = fig.getYX();
	for ( int i = 0; i < 4; ++i )
		for ( int j = 0; j < 4; ++j )
		{
			if ( fig.getBit(i, j) &&
				 y + dy + i >= 0 && y + dy + i < height_ &&
				 x + dx + j >= 0 && x + dx + j < width_ &&
				field_[y+dy+i][x+dx+j] )  return false;
			if ( (y + dy + i < 0 || y + dy + i >= height_ ||
				  x + dx + j < 0 || x + dx + j >= width_ )
				 && fig.getBit(i, j) )  return false;
		}
	return true;
}
