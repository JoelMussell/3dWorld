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
	bool checkForOccupiedBlocks(int x1, int x2, int y1, int y2, int z1, int z2);
	void generateStem(int x, int y, int z, int height, Constants::RGBcolor color);
	void generateGrassField(int x1, int x2, int y1, int y2, int z, int maxHeight);
	void generateFlower(int x, int y, int z, int height, Constants::RGBcolor color, Constants::RGBcolor color2);
	void generateFlowerField(int x1, int x2, int y1, int y2, int z, int minHeight, int maxHeight);
	void generateTree(int x, int y);
	Constants::RGBcolor getBlock(int x, int y, int z);
};