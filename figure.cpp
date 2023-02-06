#include "figure.h"



Figure::Figure(WINDOW* win, uint8_t figure_type)
	: win_ {win}
	, x_ {6}
	, y_ {1}
{
	switch ( figure_type )
	{
		case 0:
			fig_.set(0b0000011001100000);		// Square
			break;
		case 1:
			fig_.set(0b0010001000100010);		// Straight
			break;
		case 2:
			fig_.set(0b0000110001100000);		// Z-like
			break;
		case 3:
			fig_.set(0b0000001101100000);		// Mirrored Z-like
			break;
		case 4:
			fig_.set(0b0100010001100000);		// L-like
			break;
		case 5:
			fig_.set(0b0010001001100000);		// Mirrored L-like
			break;
		case 6:
			fig_.set(0b0000010011100000);		// T-like
			break;
		default:

			break;
	}
	color_ = COLOR_GREEN;
}



void Figure::draw() const
{
	for ( uint16_t i = 0; i < 4; ++i )
		for ( uint16_t j = 0; j < 4; ++j )
			if ( fig_.get(i, j) )
				mvwaddstr(win_, y_ + i, 2*(x_ + j), "  ");
//				mvprintw(i+5, j+40, "%d", fig_.get(i, j));
	wrefresh(win_);
}



void Figure::show()
{
	init_pair(3, color_, color_);
	wattron(win_, COLOR_PAIR(3));
	draw();
}



void Figure::hide() const
{
	init_pair(4, COLOR_BLACK, COLOR_BLACK);
	wattron(win_, COLOR_PAIR(4));
	draw();
}



void Figure::moveLeft()
{
	hide();
	--x_;
	show();
}



void Figure::moveRight()
{
	hide();
	++x_;
	show();
}



void Figure::moveDown()
{
	hide();
	++y_;
	show();
}



void Figure::moveUp()
{
	hide();
	--y_;
	show();
}



void Figure::rotateClockwise()
{
	hide();
    const uint16_t n = 3;
    bool a, b, c, d;
	for ( uint16_t i = 0; i < 2; ++i )
		for ( uint16_t j = i; j < 3 - i; ++j )
		{
			a = fig_.get(i, j);
			b = fig_.get(j, n - i);
			c = fig_.get(n - i, n - j);
			d = fig_.get(n - j, i);

			fig_.set(i, j, d);
			fig_.set(j, n - i, a);
			fig_.set(n - i, n - j, b);
			fig_.set(n - j, i, c);
		}
	show();
}



void Figure::rotateCounterclockwise()
{
	hide();
    const uint16_t n = 3;
    bool a, b, c, d;
	for ( uint16_t i = 0; i < 2; ++i )
		for ( uint16_t j = i; j < 3 - i; ++j )
		{
			a = fig_.get(i, j);
			b = fig_.get(j, n - i);
			c = fig_.get(n - i, n - j);
			d = fig_.get(n - j, i);
			fig_.set(i, j, b);
			fig_.set(j, n - i, c);
			fig_.set(n - i, n - j, d);
			fig_.set(n - j, i, a);
		}
	show();
}
