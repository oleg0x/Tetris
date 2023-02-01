#include "tetris.h"
#include <ncurses.h>



Tetris::Tetris()
{
	initscr();
	start_color();
	noecho();						// Disable printing by getch()
	mvprintw(0, 10, "Tetris");		// From top left corner which is (0,0)
	win_ = newwin(25, 40, 5, 10);	// (nlines, ncols, begin_y, begin_x)
	refresh();
	field_ = Field(win_, 20, 10);
}



Tetris::~Tetris()
{
	getch();
	endwin();
	puts("The program finished");
}



void Tetris::run()
{
	field_.redraw();
}
