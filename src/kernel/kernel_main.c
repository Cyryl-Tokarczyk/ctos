#include "print_vga.h"

void kernel_main() {
	printClear();


	uint32_t test = 0x12345678;
	uint8_t* bytes = (uint8_t*)&test;

	if (bytes[0] == 0x78) {
		// Little-endian
		printCharacter('L');
	}
	else if (bytes[0] == 0x12) {
		// Big-endian
		printCharacter('B');
	}


	printCharacter('C');
	printString("jazda");
	printString(" z \n testami");
	printCharacter('\n');
	printString("testtest");
	for (size_t i = 0; i < 30; i++)
	{
		printString("testtest \n");
	}
}