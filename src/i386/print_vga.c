#include "print_vga.h"

uint16_t* vgaBuffer = (uint16_t*) 0xB8000;

static size_t vgaIndex = 0;

static const size_t columnsNumber = 80;
static const size_t rowsNumber = 25;

enum PrintColor foregroundColor = White;
enum PrintColor backgroundColor = Black;

void printClear()
{
	uint16_t blank = foregroundColor << 8 | backgroundColor << 12;
	for (size_t row = 0; row < rowsNumber; row++)
	{
		for (size_t col = 0; col < columnsNumber; col++)
		{
			vgaBuffer[row * columnsNumber + col] = blank; // We need to set the foreground in order for the cursor to be visible
		}
	}
}

// Bit structure VGA expects (in low endian), one cell being 2 bytes:
// 0 - 7 -> ASCII character
// 8 - 11 -> foreground color
// 12 - 15 -> background color
void printCharacter(char character)
{
	if (character == '\n')
	{
		int currentRow = vgaIndex / columnsNumber;
		vgaIndex = (currentRow + 1) * columnsNumber;
	}
	else
	{
		vgaBuffer[vgaIndex] = (character) | (foregroundColor << 8) | (backgroundColor << 12);
		vgaIndex++;
	}

	if (vgaIndex >= rowsNumber * columnsNumber)
	{
		scrollScreen();
		vgaIndex -= columnsNumber; // Push index one row up
	}

	moveCursor(vgaIndex);
}

void printString(char* string)
{
	for (size_t i = 0; string[i]; i++)
	{
		printCharacter(string[i]);
	}
}

void printSetColor(enum PrintColor foreground, enum PrintColor background)
{
	foregroundColor = foreground;
	backgroundColor = background;
}

void scrollScreen()
{
	// Push all values up one row
	for (size_t row = 1; row < rowsNumber - 1; row++)
	{
		for (size_t col = 0; col < columnsNumber; col++)
		{
			vgaBuffer[(row - 1) * columnsNumber + col] = vgaBuffer[row * columnsNumber + col];
		}
	}

	// Clear last row
	uint16_t blank = foregroundColor << 8 | backgroundColor << 12;
	for (size_t col = 0; col < columnsNumber; col++)
	{
		vgaBuffer[(rowsNumber - 1) * columnsNumber + col] = blank;
	}
}

// VGA CRTC I/O ports

static const uint16_t commandPort = 0x3D4;
static const uint16_t dataPort = 0x3D5;

// CRTC registers indices

static const uint16_t cursorLocationHighByteRegister = 0x0E;
static const uint16_t cursorLocationLowByteRegister = 0x0F;

void moveCursor(uint16_t position)
{
	out(commandPort, cursorLocationHighByteRegister);
	out(dataPort,  position >> 8 & 0x00FF);

	out(commandPort, cursorLocationLowByteRegister);
	out(dataPort, position & 0x00FF);
}