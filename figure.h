#pragma once

#include <array>



class Figure
{
public:
	/*virtual*/ void rotate();

private:
	array<array<char, 4>, 4> fig;
	static Field& field;
};



class FigureSquare
{
public:

private:

};



class FigureStraight
{
public:

private:

};



class FigureL
{
public:

private:

};



class FigureLMirrored
{
public:

private:

};



class FigureZ
{
public:

private:

};



class FigureZMirrored
{
public:

private:

};
