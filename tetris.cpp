#include "tetris.h"
#include "figure.h"
#include <ncurses.h>
#include <cstdlib>
#include <iostream>

using namespace std;



Tetris::Tetris()
{
	initscr();					// Initialize routines
	cbreak();
	curs_set(0);				// Hide cursor
	noecho();					// Disable printing by getch()
	keypad(stdscr, true);		// Activate function keys
	start_color();				// Activate color manipulation

	if ( !has_colors() )
	{
		endwin();
		cout << "The terminal does not support colors\n";
		exit(1);
	}

	mvaddstr(0, 10, "TETRIS");		// From top left corner which is (0,0)
	uint16_t beg_y = 2;
	uint16_t beg_x = 4;
	win_ = newwin(height_ + 2, 2*width_ + 2, beg_y, beg_x);
	refresh();
	field_ = Field(win_, height_, width_);
}



Tetris::~Tetris()
{
//	getch();
	endwin();
	cout << "The program finished\n";
}



void Tetris::run()
{
	field_.redraw();
	Figure fig(field_, 6);
	fig.show();

	while ( true )
	{
		int ch = getch();
		switch ( ch )
		{
			case KEY_LEFT:
				fig.move(0, -1);
				break;
			case KEY_RIGHT:
				fig.move(0, +1);
				break;
			case KEY_UP:
				fig.move(-1, 0);
				break;
			case KEY_DOWN:
				fig.move(+1, 0);
				break;
			case 'k':
				fig.rotateCounterclockwise();
				break;
			case 'l':
				fig.rotateClockwise();
				break;
			case 'q':
				return;
			default:
				return;
		}
	}
}
