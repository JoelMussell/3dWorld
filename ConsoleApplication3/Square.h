#pragma once
class Square
{
public:
	struct RGBcolor {
		short red = 0;
		short green = 0;
		short blue = 0;
	};

	Square(const char * squareName, Square::RGBcolor squareColor);
	~Square();
	void jump();
	void resetJump();
	void down();
	void right();
	void left();
	int getx();
	int gety();
	void gravity();
	int ground();

	enum jump_2 {
		completed,
		not_ready,
		ready
	};

	int speed;
	int x;
	int y;
	int v;
	int j;
};

