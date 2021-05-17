#pragma once
#include "Constants.h"

class BlockComp
{
public:
	BlockComp();

	BlockComp(Constants::RGBcolor color);

	~BlockComp();

	Constants* pConstants;

	static const int xBlocks = 1024;
	static const int yBlocks = 1024;
	static const int zBlocks = 100;
	Constants::RGBcolor block[xBlocks][yBlocks][zBlocks];
	void generateRect(int x1, int x2, int y1, int y2, int z1, int z2, Constants::RGBcolor color);
	void generateBlock(int x, int y, int z, Constants::RGBcolor color);
	void generateTree(int x, int y);
	Constants::RGBcolor getBlock(int x, int y, int z);
	int getAltitude(int x, int y);
};