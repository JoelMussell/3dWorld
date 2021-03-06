#include "pch.h"
#include "Square.h"

Square::Square(const char * squareName, Square::RGBcolor squareColor)
{
	speed = 3;
	x = 10;
	y = 400;
	v = 0;
	j = completed;
}

Square::~Square()
{
}

void Square::jump() {
	if (y <= ground())
	{
		v = 50;
		j = not_ready;
	}
	else if (j == ready) {
		v = 50;
		j = completed;
	}
}

void Square::resetJump() {
	if (j == not_ready) {
		j = ready;
	}
}

void Square::down() {
	y = y - speed;
}

void Square::right() {
	x = x + speed;
}

void Square::left() {
	x = x - speed;
}

int Square::getx() {
	return x;
}

int Square::gety() {
	return y;
}

void Square::gravity() {
	if (y == ground() && 440 < x && x < 490) {
		v = 60;
	}
	if (v > 0) {
		y = y + v;
		v = v - 5;
	}
	else if (y + v > ground()) {
		y = y + v;
		v = v - 5;
	}
	else if (y >= ground()) {
		y = ground();
		v = 0;
	}
}

int Square::ground() {
	return 0;
}