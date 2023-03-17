#include "figure.h"
#include "field.h"
#include <iostream>
#include <random>
#include <thread>

using namespace std;



Figure::Figure(Field& field, uint8_t figure_type)
	: field_ {field}
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
			endwin();
			cerr << "In Figure::Figure: wrong figure number!\n";
			exit(1);
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<short int> distr(1, COLORS);
	do {
		color_ = distr(gen);
	} while ( abs(color_ - field_.fallen_color) < 10 );
}



pair<int, int> Figure::getYX() const
{
	return {y_, x_};
}



bool Figure::getBit(int i, int j) const
{
	return fig_.get(i, j);
}



bool Figure::isMoveable() const
{
	return moveable_;
}



void Figure::draw() const
{
	for ( int i = 0; i < 4; ++i )
		for ( int j = 0; j < 4; ++j )
			if ( fig_.get(i, j) )
				mvwaddstr(field_.getWindow(), y_+i+1, 2*(x_+j)+1, "  ");
	wrefresh(field_.getWindow());
}



void Figure::show() const
{
	init_pair(3, COLOR_BLACK, color_);
	wattron(field_.getWindow(), COLOR_PAIR(3));
	draw();
}



void Figure::hide() const
{
	init_pair(4, COLOR_BLACK, COLOR_BLACK);
	wattron(field_.getWindow(), COLOR_PAIR(4));
	draw();
}



void Figure::move(int dy, int dx)
{
	lock_guard<mutex> lg(fig_mutex_);
	if ( field_.isValidPlacement(*this, dy, dx) )
	{
		hide();
		y_ += dy;
		x_ += dx;
		show();
		mvprintw(6, 50, "%02dx%02d", y_, x_);
	}
	else if ( dy > 0 && dx == 0 )		// It is invalid move down
		moveable_ = false;
}



void Figure::drop()
{
	while ( moveable_ )
		move(1, 0);
}



void Figure::stepDown()
{
	while ( true )
	{
		for ( int i = 0; i < 10; ++i )
		{   // Divide the pause for faster thread cancellation
			if ( !moveable_ )  return;
			this_thread::sleep_for(50ms);
		}
		move(1, 0);
	}
}



void Figure::rotate(RotationDirection rd)
{
	lock_guard<mutex> lg(fig_mutex_);
	fig_.rotate(rd);
	if ( field_.isValidPlacement(*this, 0, 0) )
	{
		fig_.rotate(!rd);
		hide();
		fig_.rotate(!rd);
		show();
	}
	else	// Invalid placement
		fig_.rotate(!rd);
}
