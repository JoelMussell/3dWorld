#include "pch.h"
#include "Constants.h"

Constants::Constants()
{
	NONE = { -1,-1,-1 };
	BLACK = { 0,0,0 };
	WHITE = { 100,100,100 };
	RED = { 100,0,0 };
	GREEN = { 0,100,0 };
	DARK_GREEN = { 0,50,0 };
	BLUE = { 0,0,100 };
	YELLOW = { 255/2,255/2,0 };
	BROWN = { 150/2,75/2,0 };
	LIGHT_BLUE = { 135 / 2,206 / 2,235 / 2 };
}

Constants::~Constants()
{
}
