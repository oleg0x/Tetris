#include "tetris.h"
#include "figure.h"
#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <random>

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
	mvprintw(4, 50, "Field: %2dx%2d", height_, width_);

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
	cout << "The program finished.\n";
}



void Tetris::run()
{
	random_device rd;   // Is used to obtain a seed for the random number engine
	mt19937 gen(rd());  // Predefined generator of mersenne_twister_engine
	uniform_int_distribution<int16_t> distr(0, 6);

	field_.redraw();

	while ( true )
	{
		Figure fig(field_, distr(gen));
		fig.show();
		while ( fig.isMoveable() )
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
				case KEY_IC:				// Keypad Ins
					fig.drop();
					break;
				case '/':
					fig.rotateCounterclockwise();
					break;
				case '*':
					fig.rotateClockwise();
					break;
				case 'q':
					return;
				default:
					return;
			} // switch ( ch )
		} // while ( fig.isMoveable() )
	} // while ( true )
}
