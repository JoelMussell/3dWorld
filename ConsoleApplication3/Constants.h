#pragma once
class Constants
{
public:
	struct RGBcolor {
		int red = 0;
		int green = 0;
		int blue = 0;
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
	RGBcolor GRAY;
	RGBcolor LIGHT_BLUE;
	
	Constants();
	~Constants();

	enum jump_2 {
		completed,
		not_ready,
		ready
	};
};