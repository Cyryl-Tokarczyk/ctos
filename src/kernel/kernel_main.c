#include "i386/init_protected_mode.h"
#include "i386/print_vga.h"
#include "i386/serial_port.h"
#include "common/conversion.h"

void kernel_main()
{
	if (initProtectedMode() != 0) return;
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


	char buffer[10];

	// struct GDTEntryTest gdtTest;

	// printString("Struct size: ");
	// printString(intToString(sizeof(gdtTest), buffer));

	printString("Serial port COM1 status: ");
	printString(intToString(initSerialPort(COM1, 3), buffer));
	printToSerialPort(COM1, "Test wypisywania na serial port");
}