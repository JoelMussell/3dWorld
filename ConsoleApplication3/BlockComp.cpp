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

bool BlockComp::checkForOccupiedBlocks(int x1, int x2, int y1, int y2, int z1, int z2)
{
	for (int x = x1; x <= x2; x++)
	{
		for (int y = y1; y <= y2; y++)
		{
			for (int z = z1; z <= z2; z++)
			{
				if (BlockComp::block[x][y][z].green != -1)
					return true;
			}
		}
	}
	return false;
}

void BlockComp::generatePerson(int x, int y, int z)
{
	generateRect(x / 2 - 2, x / 2 - 1, y / 2 - 1, y / 2 + 1, 14, 14, pConstants->BLACK);
	generateRect(x / 2 + 1, x / 2 + 2, y / 2 - 1, y / 2 + 1, 14, 14, pConstants->BLACK);
	generateRect(x / 2 - 2, x / 2 - 1, y / 2, y / 2 + 1, 15, 17, pConstants->BLUE);
	generateRect(x / 2 + 1, x / 2 + 2, y / 2, y / 2 + 1, 15, 18, pConstants->BLUE);
	generateRect(x / 2 - 2, x / 2 + 2, y / 2 - 1, y / 2 + 2, 18, 18, pConstants->BLUE);
	generateRect(x / 2 - 2, x / 2 + 2, y / 2 - 1, y / 2 + 2, 19, 22, pConstants->RED);
	generateRect(x / 2 - 3, x / 2 - 3, y / 2 - 4, y / 2 + 1, 18, 18, pConstants->BROWN);
	generateRect(x / 2 - 3, x / 2 - 3, y / 2 - 5, y / 2 - 5, 17, 19, pConstants->GRAY);
	generateBlock(x / 2 - 3, y / 2 - 4, 16, pConstants->GRAY);
	generateBlock(x / 2 - 3, y / 2 - 4, 20, pConstants->GRAY);
	generateRect(x / 2 + 3, x / 2 + 3, y / 2, y / 2, 19, 22, pConstants->RED);
	generateBlock(x / 2 + 3, y / 2, 18, pConstants->SKIN_WHITE);
	generateRect(x / 2 - 3, x / 2 - 3, y / 2, y / 2, 19, 22, pConstants->RED);
	generateBlock(x / 2 - 3, y / 2, 18, pConstants->SKIN_WHITE);
	generateRect(x / 2, x / 2, y / 2, y / 2, 23, 23, pConstants->SKIN_WHITE);
	generateRect(x / 2 - 1, x / 2 + 1, y / 2 - 2, y / 2 + 2, 24, 24, pConstants->SKIN_WHITE);
	generateRect(x / 2 - 2, x / 2 + 2, y / 2 - 1, y / 2 + 1, 24, 24, pConstants->SKIN_WHITE);
	generateRect(x / 2 - 2, x / 2 + 2, y / 2 - 2, y / 2 + 2, 25, 27, pConstants->SKIN_WHITE);
	generateRect(x / 2 - 2, x / 2 + 2, y / 2 + 1, y / 2 + 2, 25, 26, pConstants->BROWN);
	generateRect(x / 2 - 2, x / 2 + 2, y / 2, y / 2 + 2, 27, 28, pConstants->BROWN);
	generateRect(x / 2 - 2, x / 2 + 2, y / 2 - 2, y / 2 + 2, 28, 28, pConstants->BROWN);
	generateRect(x / 2 - 1, x / 2 + 1, y / 2 - 2, y / 2 + 2, 29, 29, pConstants->BROWN);
	generateRect(x / 2 - 2, x / 2 + 2, y / 2 - 1, y / 2 + 1, 29, 29, pConstants->BROWN);
	generateRect(x / 2 - 1, x / 2 + 1, y / 2 - 2, y / 2 - 2, 28, 28, pConstants->SKIN_WHITE);
	generateRect(x / 2 - 1, x / 2 + 1, y / 2 - 2, y / 2 - 2, 25, 25, pConstants->BLACK);
	generateBlock(x / 2 - 1, y / 2 - 2, 27, pConstants->BLACK);
	generateBlock(x / 2 + 1, y / 2 - 2, 27, pConstants->BLACK);
	generateBlock(x / 2, y / 2 - 3, 26, pConstants->LIP_WHITE);
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

void BlockComp::generateFlower(int x, int y, int z, int height, Constants::RGBcolor color, Constants::RGBcolor color2)
{
	if (!checkForOccupiedBlocks(x - 3, x + 3, y - 3, y + 3, z + height - 3, z + height + 3))
	{
		generateStem(x, y, z, height - 2, pConstants->DARK_GREEN);
		//generateRect(x - 2, x + 2, y - 2, y + 2, z + height - 1, z + height - 1, color);
		generateRect(x - 1, x + 1, y + 3, y + 3, z + height, z + height, color);
		generateRect(x - 3, x - 3, y - 1, y + 1, z + height, z + height, color);
		generateRect(x - 1, x + 1, y - 3, y - 3, z + height, z + height, color);
		generateRect(x + 3, x + 3, y - 1, y + 1, z + height, z + height, color);
		generateRect(x - 1, x + 1, y + 2, y + 2, z + height - 1, z + height - 1, color);
		generateRect(x - 2, x - 2, y - 1, y + 1, z + height - 1, z + height - 1, color);
		generateRect(x - 1, x + 1, y - 2, y - 2, z + height - 1, z + height - 1, color);
		generateRect(x + 2, x + 2, y - 1, y + 1, z + height - 1, z + height - 1, color);
		generateRect(x - 2, x - 2, y - 2, y - 2, z + height, z + height, color);
		generateRect(x + 2, x + 2, y + 2, y + 2, z + height, z + height, color);
		generateRect(x + 2, x + 2, y - 2, y - 2, z + height, z + height, color);
		generateRect(x - 2, x - 2, y + 2, y + 2, z + height, z + height, color);
		generateRect(x - 1, x + 1, y - 1, y + 1, z + height, z + height, color2);
		//generateBlock(x, y, z + height - 1, pConstants->YELLOW);
	}
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
		generateFlower(rand() % xLength + 3 + x1, rand() % yLength + 3 + y1, z, rand() % heightRange + minHeight, pConstants->YELLOW, pConstants->LIGHT_BLACK);
		generateFlower(rand() % xLength + 3 + x1, rand() % yLength + 3 + y1, z, rand() % heightRange + minHeight, pConstants->RED, pConstants->LIGHT_BLACK);
		generateFlower(rand() % xLength + 3 + x1, rand() % yLength + 3 + y1, z, rand() % heightRange + minHeight, pConstants->RED, pConstants->YELLOW);
		generateFlower(rand() % xLength + 3 + x1, rand() % yLength + 3 + y1, z, rand() % heightRange + minHeight, pConstants->ORANGE, pConstants->YELLOW);
		generateFlower(rand() % xLength + 3 + x1, rand() % yLength + 3 + y1, z, rand() % heightRange + minHeight, pConstants->MAGENTA, pConstants->YELLOW);
		generateFlower(rand() % xLength + 3 + x1, rand() % yLength + 3 + y1, z, rand() % heightRange + minHeight, pConstants->BLUE, pConstants->YELLOW);
		generateFlower(rand() % xLength + 3 + x1, rand() % yLength + 3 + y1, z, rand() % heightRange + minHeight, pConstants->WHITE, pConstants->YELLOW);
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