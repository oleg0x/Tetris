#include "tetris.h"
#include "figure.h"
#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <random>
#include <thread>

using namespace std;



Tetris::Tetris(uint16_t height, uint16_t width)
	: height_ {height}
	, width_ {width}
{
	initscr();					// Initialize routines
	cbreak();					// Don't wait Enter
	noecho();					// Disable printing by getch()
	keypad(stdscr, true);		// Activate function keys
	nodelay(stdscr, true);		// Non-blocking getch
	curs_set(0);				// Hide cursor
	start_color();				// Activate color manipulation

	if ( !has_colors() )
	{
		endwin();
		cerr << "The terminal does not support colors\n";
		exit(1);
	}

	mvaddstr(0, 10, "TETRIS");		// From top left corner which is (0,0)
	mvprintw(4, 50, "%d colors", COLORS);
	mvprintw(5, 50, "Field: %2dx%2d", height_, width_);
	win_ = newwin(height_ + 2, 2*width_ + 2, 2, 4);
	refresh();
	field_ = Field(win_, height_, width_);
}



Tetris::~Tetris()
{
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
		jthread fig_thr(&Figure::stepDown, &fig);

		while ( fig.isMoveable() )
		{
			int ch = getch();
			this_thread::sleep_for(10ms);
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
				case KEY_IC:					// Keypad Ins
					fig.moveable_ = false;
					fig_thr.join();
					fig.moveable_ = true;
					fig.drop();
					break;
				case '/':
					fig.rotate(RotationDirection::counterclockwise);
					break;
				case '*':
					fig.rotate(RotationDirection::clockwise);
					break;
				case 'q':
					fig.moveable_ = false;
					fig_thr.join();
					return;
			} // switch ( ch )
		} // while ( fig.isMoveable() )

		field_.makeFigureStatic(fig);
	} // while ( true )
}
