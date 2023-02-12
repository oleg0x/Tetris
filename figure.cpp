#include "figure.h"



Figure::Figure(Field& field, uint8_t figure_type)
	: field_ {field}
	, x_ {6}
	, y_ {0}
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



bool Figure::isMoveable() const
{
	return moveable_;
}



bool Figure::isValidPlacement(int y, int x) const
{
	for ( int i = 0; i < 4; ++i )
		for ( int j = 0; j < 4; ++j )
		{
			if ( fig_.get(i, j) &&
				 y + i >= 0 && y + i < field_.height_ &&
				 x + j >= 0 && x + j < field_.width_ &&
				field_.field_[y+i][x+j] )  return false;
			if ( (y + i < 0 || y + i >= field_.height_ ||
				  x + j < 0 || x + j >= field_.width_ )
				 && fig_.get(i, j) )  return false;
		}
	return true;
}



void Figure::draw() const
{
	for ( int i = 0; i < 4; ++i )
		for ( int j = 0; j < 4; ++j )
			if ( fig_.get(i, j) )
				mvwaddstr(field_.win_, y_+i+1, 2*(x_+j)+1, "  ");
	wrefresh(field_.win_);
}



void Figure::show()
{
	init_pair(3, COLOR_BLACK, color_);
	wattron(field_.win_, COLOR_PAIR(3));
	draw();
}



void Figure::hide() const
{
	init_pair(4, COLOR_BLACK, COLOR_BLACK);
	wattron(field_.win_, COLOR_PAIR(4));
	draw();
}



void Figure::move(int dy, int dx)
{
	if ( isValidPlacement(y_ + dy, x_ + dx) )
	{
		hide();
		y_ += dy;
		x_ += dx;
		show();
		mvprintw(5, 50, "%2dx%2d", y_, x_);
	}
	else if ( dy > 0 && dx == 0 )		// It is invalid move down
	{
		for ( int i = 0; i < 4; ++i )
			for ( int j = 0; j < 4; ++j )
				if ( y_ + i < field_.height_ && x_ + j < field_.width_ )
					field_.field_[y_+i][x_+j] =
						field_.field_[y_+i][x_+j] | fig_.get(i, j);
		moveable_ = false;
		field_.redraw();
	}
}



void Figure::drop()
{
	while ( isMoveable() )
		move(+1, 0);
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
