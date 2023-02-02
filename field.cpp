#include "field.h"
#include <iostream>



Field::Field(WINDOW* win, uint_fast16_t height, uint_fast16_t width,
			 uint_fast16_t beg_y, uint_fast16_t beg_x)
	: win_ {win}
	, height_ {height}
	, width_ {width}
	, beg_y_ {beg_y}
	, beg_x_ {beg_x}
	, field_(height_)
{
	for ( auto& v : field_ )
		v.resize(width_, false);

	field_[0][0] = field_[0][width_-1] = true;
	field_[0][5] = field_[1][5] = field_[2][5] = field_[2][6] = true;
	field_[height_-1][0] = field_[height_-1][width_-1] = true;
}



void Field::redraw() const
{
	mvwaddch(win_, 2, 8, '*');
	mvwprintw(win_, 3, 4, "Field::redraw");	// (*win, y, x, *str, ...)

	const short int border_color = COLOR_WHITE;
	const short int fallen_color = 245;		// Gray color

	init_pair(1, border_color, border_color);		// (id, fg, bg)
	wattron(win_, COLOR_PAIR(1));
	wborder(win_, 0, 0, ' ', 0, 0, 0, 0, 0);
	wattroff(win_, COLOR_PAIR(1));
	wrefresh(win_);

	init_pair(2, fallen_color, fallen_color);		// (id, fg, bg)
	attron(COLOR_PAIR(2));
	for ( unsigned int i = 0; i < height_; ++i )
		for ( unsigned int j = 0; j < width_; ++j )
			if ( field_[i][j] )
				mvprintw(beg_y_ + i, beg_x_ + 2*j, "  ");
	attroff(COLOR_PAIR(2));
}



bool Field::checkFullRow() const
{
	return false;
}
