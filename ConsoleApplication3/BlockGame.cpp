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
void drawSide(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, Constants::RGBcolor squareColor, int colorOffset);
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

int step = 1;//4;

const int xCoordinatesSize = 500;
const int yCoordinatesSize = 500;
const int zCoordinatesSize = 51;

int xCoordinates[xCoordinatesSize][yCoordinatesSize][zCoordinatesSize + 1];
int yCoordinates[xCoordinatesSize][yCoordinatesSize][zCoordinatesSize + 1];

double cameraAngle;

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
	cameraAngle = .0015;
	calculateCoordinates();
	pBlockComp->generateFlowerField(0, 1023, 0, 1023, 11, 9, 13);
	pBlockComp->generateRect(0, 1023, 0, 1023, 0, 4, pConstants->GRAY);
	pBlockComp->generateRect(0, 1023, 0, 1023, 5, 9, pConstants->BROWN);
	pBlockComp->generateRect(0, 1023, 0, 1023, 10, 10, pConstants->GREEN);
	pBlockComp->generateBlock(xBlocks / 2, yBlocks / 2, 5, pConstants->RED);
	pBlockComp->generateBlock(xBlocks / 2, yBlocks / 2, 1, pConstants->RED);
	pBlockComp->generateBlock(xBlocks / 2, yBlocks / 2, 2, pConstants->GREEN);
	pBlockComp->generateBlock(xBlocks / 2, yBlocks / 2, 3, pConstants->BLUE);
	pBlockComp->generateBlock(xBlocks / 2, yBlocks / 2, 6, pConstants->BLUE);
	pBlockComp->generateRect(xBlocks / 2 - 20, xBlocks / 2 + 20, yBlocks / 2 - 19, yBlocks / 2 + 20, 11, 25, pConstants->NONE);
	
	pBlockComp->generatePerson(xBlocks, yBlocks, 14);

	pBlockComp->generateRect(xBlocks / 2 - 20, xBlocks / 2 + 19, yBlocks / 2 - 20, yBlocks / 2 + 20, 10, 10, pConstants->RED);
	pBlockComp->generateRect(xBlocks / 2 - 16, xBlocks / 2 - 13, yBlocks / 2 - 20, yBlocks / 2 + 20, 10, 10, pConstants->BLACK);
	pBlockComp->generateRect(xBlocks / 2 - 8, xBlocks / 2 - 5, yBlocks / 2 - 20, yBlocks / 2 + 20, 10, 10, pConstants->BLACK);
	pBlockComp->generateRect(xBlocks / 2, xBlocks / 2 + 3, yBlocks / 2 - 20, yBlocks / 2 + 20, 10, 10, pConstants->BLACK);
	pBlockComp->generateRect(xBlocks / 2 + 8, xBlocks / 2 + 11, yBlocks / 2 - 20, yBlocks / 2 + 20, 10, 10, pConstants->BLACK);
	pBlockComp->generateRect(xBlocks / 2 + 16, xBlocks / 2 + 19, yBlocks / 2 - 20, yBlocks / 2 + 20, 10, 10, pConstants->BLACK);
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
	int yBlocksRadiusFront = (height >> blockSize >> 1) * .75;
	int yBlocksRadiusBack = (height >> blockSize >> 1) * 1.5;
	int xOffset = (width >> 1);
	int yOffset = (height >> 1);
	int yCoordinate;
	int yReverseCoordinate;
	int xCoordinate;
	int xReverseCoordinate;
	for (int y = yBlocksRadiusBack; y >= -yBlocksRadiusFront; y--)
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
					int insideFrontX = xCoordinates[x][y + yBlocksRadius][z + 1];
					int insideFrontY = yCoordinates[x][y + yBlocksRadius][z + 1];

					int insideBackX = xCoordinates[x][y + yBlocksRadius + 1][z + 1];
					int insideBackY = yCoordinates[x][y + yBlocksRadius + 1][z + 1];

					int outsideBackX = xCoordinates[x + 1][y + yBlocksRadius + 1][z + 1];
					int outsideBackY = yCoordinates[x + 1][y + yBlocksRadius + 1][z + 1];

					int outsideFrontX = xCoordinates[x + 1][y + yBlocksRadius][z + 1];
					int outsideFrontY = yCoordinates[x + 1][y + yBlocksRadius][z + 1];

					int bottomX = xCoordinates[x][y + yBlocksRadius][z];
					int bottomY = yCoordinates[x][y + yBlocksRadius][z];

					int bottomOutsideX = xCoordinates[x + 1][y + yBlocksRadius][z];
					int bottomOutsideY = yCoordinates[x + 1][y + yBlocksRadius][z];

					int bottomBackX = xCoordinates[x][y + yBlocksRadius + 1][z];
					int bottomBackY = yCoordinates[x][y + yBlocksRadius + 1][z];

					if (aboveBlockColor.green == pConstants->NONE.green)
					{
						drawSide(xOffset + insideFrontX,
							yOffset + insideFrontY,
							xOffset + insideBackX,
							yOffset + insideBackY,
							xOffset + outsideBackX,
							yOffset + outsideBackY,
							xOffset + outsideFrontX,
							yOffset + outsideFrontY,
							blockColor, 0);
					}
					if (frontBlockColor.green == pConstants->NONE.green)
					{
						drawSide(xOffset + outsideFrontX,
							yOffset + outsideFrontY,
							xOffset + insideFrontX,
							yOffset + insideFrontY,
							xOffset + bottomX,
							yOffset + bottomY,
							xOffset + bottomOutsideX,
							yOffset + bottomOutsideY,
							blockColor, 10);
					}
					if (sideBlockColor.green == pConstants->NONE.green)
					{
						drawSide(xOffset + insideBackX,
							yOffset + insideBackY,
							xOffset + insideFrontX,
							yOffset + insideFrontY,
							xOffset + bottomX,
							yOffset + bottomY,
							xOffset + bottomBackX,
							yOffset + bottomBackY,
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
					int insideFrontX = xCoordinates[x][y + yBlocksRadius][z + 1];
					int insideFrontY = yCoordinates[x][y + yBlocksRadius][z + 1];

					int insideBackX = xCoordinates[x][y + yBlocksRadius + 1][z + 1];
					int insideBackY = yCoordinates[x][y + yBlocksRadius + 1][z + 1];

					int outsideBackX = xCoordinates[x + 1][y + yBlocksRadius + 1][z + 1];
					int outsideBackY = yCoordinates[x + 1][y + yBlocksRadius + 1][z + 1];

					int outsideFrontX = xCoordinates[x + 1][y + yBlocksRadius][z + 1];
					int outsideFrontY = yCoordinates[x + 1][y + yBlocksRadius][z + 1];

					int bottomX = xCoordinates[x][y + yBlocksRadius][z];
					int bottomY = yCoordinates[x][y + yBlocksRadius][z];

					int bottomOutsideX = xCoordinates[x + 1][y + yBlocksRadius][z];
					int bottomOutsideY = yCoordinates[x + 1][y + yBlocksRadius][z];

					int bottomBackX = xCoordinates[x][y + yBlocksRadius + 1][z];
					int bottomBackY = yCoordinates[x][y + yBlocksRadius + 1][z];
					/**/
					if (aboveBlockColor.green == pConstants->NONE.green)
					{
						drawSide(xOffset - insideFrontX,
							yOffset + insideFrontY,
							xOffset - insideBackX,
							yOffset + insideBackY,
							xOffset - outsideBackX,
							yOffset + outsideBackY,
							xOffset - outsideFrontX,
							yOffset + outsideFrontY,
							blockColor, 0);
					}
					if (frontBlockColor.green == pConstants->NONE.green)
					{
						drawSide(xOffset - outsideFrontX,
							yOffset + outsideFrontY,
							xOffset - insideFrontX,
							yOffset + insideFrontY,
							xOffset - bottomX,
							yOffset + bottomY,
							xOffset - bottomOutsideX,
							yOffset + bottomOutsideY,
							blockColor, 10);
					}
					if (sideBlockColor.green == pConstants->NONE.green)
					{
						drawSide(xOffset - insideBackX,
							yOffset + insideBackY,
							xOffset - insideFrontX,
							yOffset + insideFrontY,
							xOffset - bottomX,
							yOffset + bottomY,
							xOffset - bottomBackX,
							yOffset + bottomBackY,
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
	double cameraX = 0;
	double cameraY = 10.0;
	double cameraZ = -70.0;

	int xBlocksRadius = (width >> blockSize >> 1);
	int yBlocksRadius = (height >> blockSize >> 1);
	int yBlocksRadiusFront = (height >> blockSize >> 1) * .75;
	int yBlocksRadiusBack = (height >> blockSize >> 1) * 1.5;
	int xOffset = (width >> 1);
	int yOffset = (height >> 1);
	
	float slant = 1.8;

	for (int y = yBlocksRadiusBack +1; y >= -yBlocksRadius; y--)
	{
		for (int x = xBlocksRadius + 1; x >= 0; x--)
		{
			for (int z = 0; z < 51; z++)
			{
				//complex view
				double a = y + cameraY + yBlocksRadius;
				xCoordinates[x][y + yBlocksRadius][z + 1] = atan((x + cameraX) / (a * 1024)) * 256 * 1024;
				yCoordinates[x][y + yBlocksRadius][z + 1] = atan(((z + cameraZ) / (a * 1024)) + cameraAngle) * 256 * 1024;

				//standard view
				/*int altitudeShift = (blockSlant + blockSlant - blockSize - blockSize + 7);
				int xHeightAdjustment = (z * x) << 7 >> altitudeShift;
				int yHeightAdjustment = (z * y) << 7 >> altitudeShift;
				int inside = (x << blockSize) + xHeightAdjustment;
				int front = (y << blockSize) + ((z << blockSize) * slant) + yHeightAdjustment;
				xCoordinates[x][y + yBlocksRadius][z + 1] = inside;
				yCoordinates[x][y + yBlocksRadius][z + 1] = front;*/
			}
		}
	}
}

void keyboard() {
	if (GetAsyncKeyState(VK_UP))
	{
		yLocation = yLocation + step;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		yLocation = yLocation - step;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		xLocation = xLocation + step;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		xLocation = xLocation - step;
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
		adjacentBlockDirection = -adjacentBlockDirection;
		while (GetAsyncKeyState(0x44))
		{
		}
	}
	if (GetAsyncKeyState(0x41))
	{
		direction = -direction;
		while (GetAsyncKeyState(0x41))
		{
		}
	}
	if (GetAsyncKeyState(0x53))
	{
		cameraAngle = cameraAngle + .0005;
		calculateCoordinates();
		while (GetAsyncKeyState(0x53))
		{
		}
	}
	if (GetAsyncKeyState(0x57))
	{
		cameraAngle = cameraAngle - .0005;
		calculateCoordinates();
		while (GetAsyncKeyState(0x57))
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

void drawSide(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, Constants::RGBcolor squareColor, int colorOffset) {
		glBegin(GL_QUADS);
		glColor3b(squareColor.red - colorOffset, squareColor.green - colorOffset, squareColor.blue - colorOffset);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
		glVertex2f(x4, y4);
		glEnd();
}

std::string int2str(int x) {
	// converts int to string
	std::stringstream ss;
	ss << x;
	return ss.str();
}