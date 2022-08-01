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
	RGBcolor LIGHTISH_BLACK;
	RGBcolor LIGHT_BLACK;
	RGBcolor WHITE;
	RGBcolor GREEN;
	RGBcolor DARK_GREEN;
	RGBcolor BLUE;
	RGBcolor DARK_BLUE;
	RGBcolor YELLOW;
	RGBcolor ORANGE;
	RGBcolor RED;
	RGBcolor MAGENTA;
	RGBcolor BROWN;
	RGBcolor GRAY;
	RGBcolor LIGHT_BLUE;
	RGBcolor SKIN_WHITE;
	RGBcolor NOSE_WHITE;
	RGBcolor SKIN_EAST_ASIAN;
	RGBcolor NOSE_EAST_ASIAN;
	
	Constants();
	~Constants();

	enum jump_2 {
		completed,
		not_ready,
		ready
	};
};