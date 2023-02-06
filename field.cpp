#include "field.h"
#include <iostream>



Field::Field(WINDOW* win, uint16_t height, uint16_t width)
	: win_ {win}
	, height_ {height}
	, width_ {width}
	, field_(height_)
{
	for ( auto& v : field_ )
		v.resize(width_, false);

	field_[0][0] = field_[0][width_-1] = true;
	field_[height_-1][0] = field_[height_-1][width_-1] = true;
//	field_[0][5] = field_[1][5] = field_[2][5] = field_[2][6] = true;
}



void Field::redraw() const
{
//	mvwaddch(win_, 2, 8, '*');

	const short int border_color = COLOR_WHITE;
	const short int fallen_color = 245;		// Gray color

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



bool Field::checkFullRow() const
{
	return false;
}
