#pragma once

#include <stdint.h>
#include <stddef.h>

#include "io.h"

enum PrintColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	Pink = 13,
	Yellow = 14,
	White = 15,
};

void printClear();
void printCharacter(char character);
void printString(char* string);
void printSetColor(enum PrintColor foreground, enum PrintColor background);
void moveCursor(uint16_t position);
void scrollScreen();