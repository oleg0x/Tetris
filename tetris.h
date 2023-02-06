#include "field.h"



class Tetris
{
public:
	Tetris();
//	Tetris(uint_fast16_t height, uint_fast16_t width);
	~Tetris();

	void run();

private:
	uint16_t height_ = 30;
	uint16_t width_ = 16;
	WINDOW* win_;
	Field field_;
};
