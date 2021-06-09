#include "pch.h"
#include "Constants.h"

Constants::Constants()
{
	NONE = { -1,-1,-1 };
	BLACK = { 0,0,0 };
	LIGHT_BLACK = { 20,20,20 };
	WHITE = { 127,127,127 };
	GREEN = { 0,100,0 };
	DARK_GREEN = { 0,50,0 };
	BLUE = { 0,0,100 };
	YELLOW = { 127,127,0 };
	ORANGE = { 127,64,0 };
	RED = { 127,0,0 };
	MAGENTA = { 127,0,127 };
	BROWN = { 150 / 2,75 / 2,0 };
	GRAY = { 50,50,50 };
	LIGHT_BLUE = { 135 / 2,206 / 2,235 / 2 };
	SKIN_WHITE = { 236 / 2, 188 / 2, 180 / 2 };
	LIP_WHITE = { 236 / 2, 150 / 2, 150 / 2 };
}

Constants::~Constants()
{
}
