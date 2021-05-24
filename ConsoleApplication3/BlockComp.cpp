#include "pch.h"
#include "BlockComp.h"
#include "Constants.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>       

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

void BlockComp::generateStem(int x, int y, int z, int height, Constants::RGBcolor color)
{
	generateRect(x, x, y, y, z, z + height, color);
}

void BlockComp::generateGrassField(int x1, int x2, int y1, int y2, int z, int maxHeight)
{
	for (int x = x1; x < x2; x += 2)
	{
		for (int y = y1; y < y2; y += 2)
		{
			generateStem(x, y, z, rand() % maxHeight, pConstants->GREEN);
			generateStem(x + 1, y, z, rand() % maxHeight >> 1, pConstants->GREEN);
			generateStem(x, y + 1, z, rand() % maxHeight >> 1, pConstants->GREEN);
			generateStem(x + 1, y + 1, z, rand() % maxHeight >> 2, pConstants->GREEN);
		}
	}
}

void BlockComp::generateFlower(int x, int y, int z, int height, Constants::RGBcolor color)
{
	generateStem(x, y, z, height - 2, pConstants->DARK_GREEN);
	generateRect(x - 3, x + 3, y - 1, y + 1, z + height - 1, z + height - 1, color);
	generateRect(x - 1, x + 1, y - 3, y + 3, z + height - 1, z + height - 1, color);
	generateRect(x - 2, x + 2, y - 2, y + 2, z + height - 1, z + height - 1, color);
	generateRect(x - 1, x + 1, y - 1, y + 1, z + height - 1, z + height, pConstants->YELLOW);
	//generateBlock(x, y, z + height - 1, pConstants->YELLOW);
}

void BlockComp::generateFlowerField(int x1, int x2, int y1, int y2, int z, int minHeight, int maxHeight)
{
	generateGrassField(x1, x2, y1, y2, z, 5);
	int xLength = x2 - x1 - 6;
	int yLength = y2 - y1 - 6;
	int heightRange = maxHeight - minHeight;
	int area = xLength * yLength;
	for (int i = 0; i < (area >> 10); i++)
	{
		generateFlower(rand() % xLength + 3 + x1, rand() % yLength + 3 + y1, z, rand() % heightRange + minHeight, pConstants->RED);
		generateFlower(rand() % xLength + 3 + x1, rand() % yLength + 3 + y1, z, rand() % heightRange + minHeight, pConstants->BLUE);
		generateFlower(rand() % xLength + 3 + x1, rand() % yLength + 3 + y1, z, rand() % heightRange + minHeight, pConstants->WHITE);
	}
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