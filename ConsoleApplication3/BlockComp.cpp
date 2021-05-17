#include "pch.h"
#include "BlockComp.h"
#include "Constants.h"
#include <math.h>

BlockComp::BlockComp()
{
	pConstants = new Constants();
	generateRect(0, xBlocks - 1, 0, yBlocks - 1, 0, zBlocks - 1, pConstants->BLUE);
}

BlockComp::BlockComp(Constants::RGBcolor color)
{
	pConstants = new Constants();
	generateRect(0, xBlocks - 1, 0, yBlocks - 1, 0, zBlocks - 1, color);
}

BlockComp::~BlockComp()
{
}

void BlockComp::generateRect(int x1, int x2, int y1, int y2, int z1, int z2, Constants::RGBcolor color)
{
	for (int x = x1; x <= x2 && x < BlockComp::xBlocks; x++)
	{
		for (int y = y1; y <= y2 && y < BlockComp::yBlocks; y++)
		{
			for (int z = z1; z <= z2 && z < BlockComp::zBlocks; z++)
			{
				BlockComp::block[x][y][z] = color;
			}
		}
	}
}

void BlockComp::generateBlock(int x, int y, int z, Constants::RGBcolor color)
{
	BlockComp::block[x][y][z] = color;
}

void BlockComp::generateTree(int x, int y)
{
	generateRect(x-4, x+4, y, y + 20, 2, 2, pConstants->BROWN);
	generateRect(x - 20, x + 20, y + 20, y + 50, 2, 2, pConstants->DARK_GREEN);
}

Constants::RGBcolor BlockComp::getBlock(int x, int y, int z)
{
	return BlockComp::block[x][y][z];
}

int BlockComp::getAltitude(int x, int y)
{
	if (y - x > 0 && y + x > 509 << 1 && y > 513)
		return 4;
	if (x > 513)
		return 3;
	if (x < 505)
		return 2;
	if (x == 512 && y == 512)
		return 2;
	return 0;
}