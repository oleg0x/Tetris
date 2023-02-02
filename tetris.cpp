#include "tetris.h"
#include <ncurses.h>
#include <cstdlib>
#include <iostream>

using namespace std;



Tetris::Tetris()
{
	initscr();					// Initialize routines
	curs_set(0);				// Hide cursor
	noecho();					// Disable printing by getch()
	keypad(stdscr, true);		// Activate function keys
	start_color();				// Activate color manipulation

	if ( !can_change_color() )
	{
		endwin();
		cout << "The terminal does not support color change\n";
		exit(1);
	}

	mvprintw(0, 10, "TETRIS");		// From top left corner which is (0,0)
	uint_fast16_t beg_y = 2;
	uint_fast16_t beg_x = 4;
	win_ = newwin(height_ + 2, 2*width_ + 2, beg_y, beg_x);	// (nlines, ncols, begin_y, begin_x)
	refresh();
	field_ = Field(win_, height_, width_, beg_y+1, beg_x+1);
}



Tetris::~Tetris()
{
	getch();
	endwin();
	cout << "The program finished\n";
}



void Tetris::run()
{
	field_.redraw();
}
