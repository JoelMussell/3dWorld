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
	
	Constants();
	~Constants();

	enum jump_2 {
		completed,
		not_ready,
		ready
	};
};