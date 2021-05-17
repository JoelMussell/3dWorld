#pragma once
class Constants
{
public:
	struct RGBcolor {
		short red = 0;
		short green = 0;
		short blue = 0;
	};

	RGBcolor NONE;
	RGBcolor BLACK;
	RGBcolor WHITE;
	RGBcolor RED;
	RGBcolor GREEN;
	RGBcolor DARK_GREEN;
	RGBcolor BLUE;
	RGBcolor YELLOW;
	RGBcolor BROWN;
	RGBcolor LIGHT_BLUE;

	/*
	WHITE.red = 100;
	WHITE.green = 100;
	WHITE.blue = 100;
	RED.red = 100;
	GREEN.green = 100;
	BLUE.blue = 100;
	LIGHT_BLUE.red = 135 / 2;
	LIGHT_BLUE.green = 206 / 2;
	LIGHT_BLUE.blue = 235 / 2;
*/
	Constants();
	~Constants();

	enum jump_2 {
		completed,
		not_ready,
		ready
	};
};