#include "field.h"
#include <ncurses.h>



class Tetris
{
public:
	Tetris();
	~Tetris();

	void run();

private:
	WINDOW* win_;
	Field field_;
};
