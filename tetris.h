#include "field.h"
#include <ncurses.h>



class Tetris
{
public:
	Tetris();
//	Tetris(uint_fast16_t height, uint_fast16_t width);
	~Tetris();

	void run();

private:
	uint_fast16_t height_ = 30;
	uint_fast16_t width_ = 16;
	WINDOW* win_;
	Field field_;
};
