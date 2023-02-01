#include "field.h"
#include <iostream>



Field::Field(WINDOW* win, uint_fast16_t height, uint_fast16_t width)
	: win_ {win}
	, height_ {height}
	, width_ {width}
	, field_(height_)
{
	for ( auto& v : field_ )
		v.resize(width_, false);
}



void Field::redraw() const
{
	printw("  %ld %ld", height_, width_);
	printw("  win=%p", win_);

	mvwaddch(win_, 2, 8, '*');
	mvwaddch(win_, 2, 12, '=');
	mvwprintw(win_, 3, 4, "Field::redraw");	// (*win, y, x, *str, ...)
	box(win_, 0, 0);						// (*win, ver_ch, hor_ch)
	wrefresh(win_);
}



bool Field::checkFullRow() const
{
	return false;
}
