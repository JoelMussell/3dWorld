// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Constants.h"
#include "BlockComp.h"
#include <iostream>
//#include "stdafx.h"
#include <string>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <sstream>
#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "GL/freeglut.h"
#pragma comment(lib, "OpenGL32.lib")

void draw();
void setUp();
void update(int value);
void enable2D(int width, int height);
void drawText(float x, float y, std::string text, Constants::RGBcolor squareColor);
std::string int2str(int x);
void drawRect(int x1, int y1, int x2, int y2, Constants::RGBcolor squareColor);
void drawFront(int x1o, int x1i, int y1, int x2o, int x2i, int y2, Constants::RGBcolor squareColor, int colorOffset);
void drawSide(int x1, int y1t, int y1b, int x2, int y2t, int y2b, Constants::RGBcolor squareColor, int colorOffset);
void calculateCoordinates();
void keyboard();

Constants* pConstants;
BlockComp* pBlockComp;


// window size and update rate (60 fps)
const int width = 1300;
const int height = 700;
const int interval = 1000 / 60;

const int chunkSize = 1024;
const int xBlocks = chunkSize;
const int yBlocks = chunkSize;
const int zBlocks = 100;

int blockSize;
int blockSlant;

int xLocation;
int yLocation;
int zLocation;

int adjacentBlockDirection = 1;
int direction = 1;

const int xCoordinatesSize = 500;
const int yCoordinatesSize = 500;
const int zCoordinatesSize = 51;

int xCoordinates[xCoordinatesSize][yCoordinatesSize][zCoordinatesSize + 1];
int yCoordinates[xCoordinatesSize][yCoordinatesSize][zCoordinatesSize + 1];

// program entry point
int main(int argc, char** argv) {
	// initialize opengl (via glut)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Jump");

	// Register callback functions  
	glutDisplayFunc(draw);
	glutTimerFunc(interval, update, 0);

	// setup scene to 2d mode and set draw color to white
	enable2D(width, height);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	setUp();
	// start the whole thing
	glutMainLoop();
	return 0;
}

void setUp() {
	pConstants = new Constants();
	pBlockComp = new BlockComp(pConstants->NONE);
	blockSize = 3;
	blockSlant = 5;
	xLocation = xBlocks / 2;
	yLocation = yBlocks / 2;
	zLocation = 9;//zBlocks / 2;
	calculateCoordinates();
	/*pBlockComp->generateBlock(1, 5, 0, pConstants->RED);
	pBlockComp->generateBlock(8, 5, 0, pConstants->BLACK);
	pBlockComp->generateRect(0, xBlocks, yBlocks / 2 + 4, yBlocks / 2 + 10, 0, zBlocks, pConstants->GREEN);
	//pBlockComp->generateRect(0, xBlocks, 0, yBlocks / 2 + 3, pConstants->BROWN);
	pBlockComp->generateRect(14, 15, xBlocks / 2 + 9, yBlocks / 2 + 10, 0, zBlocks, pConstants->YELLOW);
	//pBlockComp->generateTree(0, yBlocks / 2 + 5);
	pBlockComp->generateTree(xBlocks / 2 + 10, yBlocks / 2 + 5);
	pBlockComp->generateTree(xBlocks / 2 + 100, yBlocks / 2 + 5);
	pBlockComp->generateTree(xBlocks / 2 + 150, yBlocks / 2 + 5);
	pBlockComp->generateTree(xBlocks / 2 + 200, yBlocks / 2 + 5);
	pBlockComp->generateTree(xBlocks / 2 + 400, yBlocks / 2 + 5);
	pBlockComp->generateBlock(xBlocks / 2, yBlocks / 2, 0, pConstants->RED);*/
	pBlockComp->generateFlowerField(0, 1023, 0, 1023, 11, 9, 13);
	//pBlockComp->generateFlower(500, 500, 11, 10, pConstants->RED);
	//pBlockComp->generateRect(505, 507, 505, 507, 14, 16, pConstants->DARK_GREEN);
	//pBlockComp->generateRect(506, 506, 506, 506, 10, 13, pConstants->BROWN);
	pBlockComp->generateRect(0, 1023, 0, 1023, 0, 4, pConstants->GRAY);
	pBlockComp->generateRect(0, 1023, 0, 1023, 5, 9, pConstants->BROWN);
	pBlockComp->generateRect(0, 1023, 0, 1023, 10, 10, pConstants->GREEN);
	pBlockComp->generateBlock(xBlocks / 2, yBlocks / 2, 5, pConstants->RED);
	pBlockComp->generateBlock(xBlocks / 2, yBlocks / 2, 1, pConstants->RED);
	pBlockComp->generateBlock(xBlocks / 2, yBlocks / 2, 2, pConstants->GREEN);
	pBlockComp->generateBlock(xBlocks / 2, yBlocks / 2, 3, pConstants->BLUE);
	pBlockComp->generateBlock(xBlocks / 2, yBlocks / 2, 6, pConstants->BLUE);
	pBlockComp->generateRect(xBlocks / 2 - 20, xBlocks / 2 + 20, yBlocks / 2 - 20, yBlocks / 2 + 20, 11, 25, pConstants->NONE);

	pBlockComp->generateRect(xBlocks / 2 - 2, xBlocks / 2 - 1, yBlocks / 2 - 1, yBlocks / 2 + 1, 14, 14, pConstants->BLACK);
	pBlockComp->generateRect(xBlocks / 2 + 1, xBlocks / 2 + 2, yBlocks / 2 - 1, yBlocks / 2 + 1, 14, 14, pConstants->BLACK);
	pBlockComp->generateRect(xBlocks / 2 - 2, xBlocks / 2 - 1, yBlocks / 2, yBlocks / 2 + 1, 15, 17, pConstants->BLUE);
	pBlockComp->generateRect(xBlocks / 2 + 1, xBlocks / 2 + 2, yBlocks / 2, yBlocks / 2 + 1, 15, 18, pConstants->BLUE);
	pBlockComp->generateRect(xBlocks / 2 - 2, xBlocks / 2 + 2, yBlocks / 2 - 1, yBlocks / 2 + 2, 18, 18, pConstants->BLUE);
	pBlockComp->generateRect(xBlocks / 2 - 2, xBlocks / 2 + 2, yBlocks / 2 - 1, yBlocks / 2 + 2, 19, 22, pConstants->RED);
	pBlockComp->generateRect(xBlocks / 2 - 3, xBlocks / 2 - 3, yBlocks / 2 - 4, yBlocks / 2 + 1, 18, 18, pConstants->BROWN);
	pBlockComp->generateRect(xBlocks / 2 - 3, xBlocks / 2 - 3, yBlocks / 2 - 5, yBlocks / 2 - 5, 17, 19, pConstants->GRAY);
	pBlockComp->generateBlock(xBlocks / 2 - 3, yBlocks / 2 - 4, 16, pConstants->GRAY);
	pBlockComp->generateBlock(xBlocks / 2 - 3, yBlocks / 2 - 4, 20, pConstants->GRAY);
	pBlockComp->generateRect(xBlocks / 2 + 3, xBlocks / 2 + 3, yBlocks / 2, yBlocks / 2, 19, 22, pConstants->RED);
	pBlockComp->generateBlock(xBlocks / 2 + 3, yBlocks / 2, 18, pConstants->SKIN_WHITE);
	pBlockComp->generateRect(xBlocks / 2 - 3, xBlocks / 2 - 3, yBlocks / 2, yBlocks / 2, 19, 22, pConstants->RED);
	pBlockComp->generateBlock(xBlocks / 2 - 3, yBlocks / 2, 18, pConstants->SKIN_WHITE);
	pBlockComp->generateRect(xBlocks / 2, xBlocks / 2, yBlocks / 2, yBlocks / 2, 23, 23, pConstants->SKIN_WHITE);
	pBlockComp->generateRect(xBlocks / 2 - 1, xBlocks / 2 + 1, yBlocks / 2 - 2, yBlocks / 2 + 2, 24, 24, pConstants->SKIN_WHITE);
	pBlockComp->generateRect(xBlocks / 2 - 2, xBlocks / 2 + 2, yBlocks / 2 - 1, yBlocks / 2 + 1, 24, 24, pConstants->SKIN_WHITE);
	pBlockComp->generateRect(xBlocks / 2 - 2, xBlocks / 2 + 2, yBlocks / 2 - 2, yBlocks / 2 + 2, 25, 27, pConstants->SKIN_WHITE);
	pBlockComp->generateRect(xBlocks / 2 - 2, xBlocks / 2 + 2, yBlocks / 2 + 1, yBlocks / 2 + 2, 25, 26, pConstants->BROWN);
	pBlockComp->generateRect(xBlocks / 2 - 2, xBlocks / 2 + 2, yBlocks / 2, yBlocks / 2 + 2, 27, 28, pConstants->BROWN);
	pBlockComp->generateRect(xBlocks / 2 - 2, xBlocks / 2 + 2, yBlocks / 2 - 2, yBlocks / 2 + 2, 28, 28, pConstants->BROWN);
	pBlockComp->generateRect(xBlocks / 2 - 1, xBlocks / 2 + 1, yBlocks / 2 - 2, yBlocks / 2 + 2, 29, 29, pConstants->BROWN);
	pBlockComp->generateRect(xBlocks / 2 - 2, xBlocks / 2 + 2, yBlocks / 2 - 1, yBlocks / 2 + 1, 29, 29, pConstants->BROWN);
	pBlockComp->generateRect(xBlocks / 2 - 1, xBlocks / 2 + 1, yBlocks / 2 - 2, yBlocks / 2 - 2, 28, 28, pConstants->SKIN_WHITE);
	pBlockComp->generateRect(xBlocks / 2 - 1, xBlocks / 2 + 1, yBlocks / 2 - 2, yBlocks / 2 - 2, 25, 25, pConstants->BLACK);
	pBlockComp->generateBlock(xBlocks / 2 - 1, yBlocks / 2 - 2, 27, pConstants->BLACK);
	pBlockComp->generateBlock(xBlocks / 2 + 1, yBlocks / 2 - 2, 27, pConstants->BLACK);
	pBlockComp->generateBlock(xBlocks / 2, yBlocks / 2 - 3, 26, pConstants->LIP_WHITE);
}

void update(int value) {
	// input handling
	keyboard();

	// Call update() again in 'interval' milliseconds
	glutTimerFunc(interval, update, 0);

	// Redisplay frame
	glutPostRedisplay();
}

void draw() {
	// clear (has to be done at the beginning)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// draw squares
	int xBlocksRadius = (width >> blockSize >> 1);
	int yBlocksRadius = (height >> blockSize >> 1);
	int xOffset = (width >> 1);
	int yOffset = (height >> 1);
	int yCoordinate;
	int yReverseCoordinate;
	int xCoordinate;
	int xReverseCoordinate;
	for (int y = yBlocksRadius; y >= -yBlocksRadius; y--)
	{
		if (direction == 1)
		{
			yCoordinate = adjacentBlockDirection * y + yLocation;
			yReverseCoordinate = adjacentBlockDirection * y + yLocation;
		}
		else
		{
			xCoordinate = -adjacentBlockDirection * y + yLocation;
			xReverseCoordinate = -adjacentBlockDirection * y + yLocation;
		}
		for (int x = xBlocksRadius; x >= 0; x--)
		{
			if (direction == 1)
			{
				xCoordinate = adjacentBlockDirection * x + xLocation;
				xReverseCoordinate = -adjacentBlockDirection * (x + 1) + xLocation;
			}
			else
			{
				yCoordinate = adjacentBlockDirection * x + xLocation;
				yReverseCoordinate = -adjacentBlockDirection * (x + 1) + xLocation;
			}
			for (int z = 1; z < 50; z++)
			{
				int zCoordinate = z + zLocation;
				Constants::RGBcolor blockColor = pBlockComp->getBlock(xCoordinate, yCoordinate, zCoordinate);
				Constants::RGBcolor aboveBlockColor = pBlockComp->getBlock(xCoordinate, yCoordinate, zCoordinate + 1);
				Constants::RGBcolor frontBlockColor;
				Constants::RGBcolor sideBlockColor;
				if (direction == 1)
				{
					frontBlockColor = pBlockComp->getBlock(xCoordinate, yCoordinate - adjacentBlockDirection, zCoordinate);
					sideBlockColor = pBlockComp->getBlock(xCoordinate - adjacentBlockDirection, yCoordinate, zCoordinate);
				}
				else
				{
					sideBlockColor = pBlockComp->getBlock(xCoordinate, yCoordinate - adjacentBlockDirection, zCoordinate);
					frontBlockColor = pBlockComp->getBlock(xCoordinate + adjacentBlockDirection, yCoordinate, zCoordinate);
				}
				if (blockColor.green != pConstants->NONE.green)
				{
					int inside = xCoordinates[x][y + yBlocksRadius][z + 1];
					int outside = xCoordinates[x + 1][y + yBlocksRadius][z + 1];
					int front = yCoordinates[x][y + yBlocksRadius][z + 1];
					int back = yCoordinates[x][y + yBlocksRadius + 1][z + 1];
					int bottomInside = xCoordinates[x][y + yBlocksRadius][z];
					int bottomOutside = xCoordinates[x + 1][y + yBlocksRadius][z];
					int bottomFront = yCoordinates[x][y + yBlocksRadius][z];
					int bottomBack = yCoordinates[x][y + yBlocksRadius + 1][z];

					if (aboveBlockColor.green == pConstants->NONE.green)
					{
						drawRect(xOffset + inside,
							yOffset + back,
							xOffset + outside,
							yOffset + front,
							blockColor);
					}
					if (frontBlockColor.green == pConstants->NONE.green)
					{
						drawFront(xOffset + outside,
							xOffset + inside,
							yOffset + front,
							xOffset + bottomOutside,
							xOffset + bottomInside,
							yOffset + bottomFront,
							blockColor, 10);
					}
					if (sideBlockColor.green == pConstants->NONE.green)
					{
						drawSide(xOffset + inside,
							yOffset + back,
							yOffset + front,
							xOffset + bottomInside,
							yOffset + bottomBack,
							yOffset + bottomFront,
							blockColor, 20);
					}
				}
				blockColor = pBlockComp->getBlock(xReverseCoordinate, yReverseCoordinate, zCoordinate);
				aboveBlockColor = pBlockComp->getBlock(xReverseCoordinate, yReverseCoordinate, zCoordinate + 1);
				if (direction == 1)
				{
					frontBlockColor = pBlockComp->getBlock(xReverseCoordinate, yReverseCoordinate - adjacentBlockDirection, zCoordinate);
					sideBlockColor = pBlockComp->getBlock(xReverseCoordinate + adjacentBlockDirection, yReverseCoordinate, zCoordinate);
				}
				else
				{
					sideBlockColor = pBlockComp->getBlock(xReverseCoordinate, yReverseCoordinate + adjacentBlockDirection, zCoordinate);
					frontBlockColor = pBlockComp->getBlock(xReverseCoordinate + adjacentBlockDirection, yReverseCoordinate, zCoordinate);
				}
				if (blockColor.green != pConstants->NONE.green)
				{
					int inside = xCoordinates[x][y + yBlocksRadius][z + 1];
					int outside = xCoordinates[x + 1][y + yBlocksRadius][z + 1];
					int front = yCoordinates[x][y + yBlocksRadius][z + 1];
					int back = yCoordinates[x][y + yBlocksRadius + 1][z + 1];
					int bottomInside = xCoordinates[x][y + yBlocksRadius][z];
					int bottomOutside = xCoordinates[x + 1][y + yBlocksRadius][z];
					int bottomFront = yCoordinates[x][y + yBlocksRadius][z];
					int bottomBack = yCoordinates[x][y + yBlocksRadius + 1][z];

					if (aboveBlockColor.green == pConstants->NONE.green)
					{
						drawRect(xOffset - inside,
							yOffset + back,
							xOffset - outside,
							yOffset + front,
							blockColor);
					}
					if (frontBlockColor.green == pConstants->NONE.green)
					{
						drawFront(xOffset - outside,
							xOffset - inside,
							yOffset + front,
							xOffset - bottomOutside,
							xOffset - bottomInside,
							yOffset + bottomFront,
							blockColor, 10);
					}
					if (sideBlockColor.green == pConstants->NONE.green)
					{
						drawSide(xOffset - inside,
							yOffset + back,
							yOffset + front,
							xOffset - bottomInside,
							yOffset + bottomBack,
							yOffset + bottomFront,
							blockColor, 20);
					}
				}
			}
		}
	}

	// swap buffers (has to be done at the end)
	glutSwapBuffers();
}

void calculateCoordinates()
{
	int xBlocksRadius = (width >> blockSize >> 1);
	int yBlocksRadius = (height >> blockSize >> 1);
	int xOffset = (width >> 1);
	int yOffset = (height >> 1);
	
	float slant = 1.8;

	for (int y = yBlocksRadius+1; y >= -yBlocksRadius; y--)
	{
		for (int x = xBlocksRadius + 1; x >= 0; x--)
		{
			for (int z = 0; z < 51; z++)
			{
				int altitude = z;
				int altitudeShift = (blockSlant + blockSlant - blockSize - blockSize + 7);
				int xHeightAdjustment = (altitude * x) << 7 >> altitudeShift;
				int xHeightAdjustment1 = (altitude * (x + 1)) << 7 >> altitudeShift;
				int yHeightAdjustment = (altitude * y) << 7 >> altitudeShift;
				int yHeightAdjustment1 = (altitude * (y + 1)) << 7 >> altitudeShift;
				int inside = (x << blockSize) + xHeightAdjustment;
				int outside = ((x + 1) << blockSize) + xHeightAdjustment1;
				int front = (y << blockSize) + ((altitude << blockSize) * slant) + yHeightAdjustment;
				int back = ((y + 1) << blockSize) + ((altitude << blockSize) * slant) + yHeightAdjustment1;
				altitude = z - 1;
				int xHeightAdjustment2 = (altitude * x) << 7 >> altitudeShift;
				int xHeightAdjustment3 = (altitude * (x + 1)) << 7 >> altitudeShift;
				int yHeightAdjustment2 = (altitude * y) << 7 >> altitudeShift;
				int yHeightAdjustment3 = (altitude * (y + 1)) << 7 >> altitudeShift;
				int bottomInside = (x << blockSize) + xHeightAdjustment2;
				int bottomOutside = ((x + 1) << blockSize) + xHeightAdjustment3;
				int bottomFront = (y << blockSize) + ((altitude << blockSize) * slant) + yHeightAdjustment2;
				int bottomBack = ((y + 1) << blockSize) + ((altitude << blockSize) * slant) + yHeightAdjustment3;
				xCoordinates[x][y + yBlocksRadius][z + 1] = inside;
				yCoordinates[x][y + yBlocksRadius][z + 1] = front;
			}
		}
	}
}

void keyboard() {
	if (GetAsyncKeyState(VK_UP))
	{
		yLocation = yLocation + 4;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		yLocation = yLocation - 4;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		xLocation = xLocation + 4;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		xLocation = xLocation - 4;
	}
	if (GetAsyncKeyState(VK_RSHIFT))
	{
		blockSize = blockSize + 1;
		calculateCoordinates();
		while (GetAsyncKeyState(VK_RSHIFT))
		{
		}
	}
	if (GetAsyncKeyState(VK_LSHIFT))
	{
		blockSize = blockSize - 1;
		calculateCoordinates();
		while (GetAsyncKeyState(VK_LSHIFT))
		{
		}
	}
	if (GetAsyncKeyState(0x44))
	{
		//zLocation--;
		adjacentBlockDirection = -adjacentBlockDirection;
		while (GetAsyncKeyState(0x44))
		{
		}
	}
	if (GetAsyncKeyState(0x41))
	{
		//zLocation++;
		direction = -direction;
		while (GetAsyncKeyState(0x41))
		{
		}
	}
}

void enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawText(float x, float y, std::string text, Constants::RGBcolor squareColor) {
	glColor3b(squareColor.red, squareColor.green, squareColor.blue);
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

void drawRect(int x1, int y1, int x2, int y2, Constants::RGBcolor squareColor) {
	glBegin(GL_QUADS);
	glColor3b(squareColor.red, squareColor.green, squareColor.blue);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();
}

void drawFront(int x1o, int x1i, int y1, int x2o, int x2i, int y2, Constants::RGBcolor squareColor, int colorOffset) {
		glBegin(GL_QUADS);
		glColor3b(squareColor.red - colorOffset, squareColor.green - colorOffset, squareColor.blue - colorOffset);
		glVertex2f(x1o, y1);
		glVertex2f(x1i, y1);
		glVertex2f(x2i, y2);
		glVertex2f(x2o, y2);
		glEnd();
}

void drawSide(int x1, int y1t, int y1b, int x2, int y2t, int y2b, Constants::RGBcolor squareColor, int colorOffset) {
		glBegin(GL_QUADS);
		glColor3b(squareColor.red - colorOffset, squareColor.green - colorOffset, squareColor.blue - colorOffset);
		glVertex2f(x1, y1t);
		glVertex2f(x1, y1b);
		glVertex2f(x2, y2b);
		glVertex2f(x2, y2t);
		glEnd();
}

std::string int2str(int x) {
	// converts int to string
	std::stringstream ss;
	ss << x;
	return ss.str();
}