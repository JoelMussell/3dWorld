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
	RGBcolor LIGHT_BLACK;
	RGBcolor WHITE;
	RGBcolor GREEN;
	RGBcolor DARK_GREEN;
	RGBcolor BLUE;
	RGBcolor YELLOW;
	RGBcolor ORANGE;
	RGBcolor RED;
	RGBcolor MAGENTA;
	RGBcolor BROWN;
	RGBcolor GRAY;
	RGBcolor LIGHT_BLUE;
	RGBcolor SKIN_WHITE;
	RGBcolor LIP_WHITE;
	
	Constants();
	~Constants();

	enum jump_2 {
		completed,
		not_ready,
		ready
	};
};