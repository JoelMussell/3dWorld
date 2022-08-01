#include "pch.h"
#include "Constants.h"

Constants::Constants()
{
	NONE = { -1,-1,-1 };
	BLACK = { 0,0,0 };
	LIGHTISH_BLACK = { 10,10,10 };
	LIGHT_BLACK = { 20,20,20 };
	WHITE = { 127,127,127 };
	GREEN = { 0,100,0 };
	DARK_GREEN = { 0,50,0 };
	BLUE = { 0,0,100 };
	DARK_BLUE = { 0,0,120 };
	YELLOW = { 127,127,0 };
	ORANGE = { 127,64,0 };
	RED = { 127,0,0 };
	MAGENTA = { 127,0,127 };
	BROWN = { 75, 37, 0 };
	GRAY = { 50,50,50 };
	LIGHT_BLUE = { 67, 103, 117 };
	SKIN_WHITE = { 118, 94, 90 };
	NOSE_WHITE = { 118, 75, 75 };
	SKIN_EAST_ASIAN = { 229 / 2, 155 / 2, 125 / 2 };
	NOSE_EAST_ASIAN = { 229 / 2-5, 155 / 2-10, 125 / 2-7 };
}

Constants::~Constants()
{
}
