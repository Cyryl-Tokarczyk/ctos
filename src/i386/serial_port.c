#include "serial_port.h"

// I/O ports macros
// 
// All serial ports have the same offsets for I/O ports
// 
// Divisor ports are shared with data port and Interrupt Enable Register port
// They can be accessed after setting the DLAB to 1 (via setting bit 7 of Line Control Register)

#define DataPort(base)				(base)
#define DivisorLowBytePort(base)	(base)		
#define DivisorHighBytePort(base)	(base + 1)	
#define FIFOControlPort(base)		(base + 2)
#define LineControlPort(base)		(base + 3)
#define ModemControlPort(base)		(base + 4)
#define LineStatusPort(base)		(base + 5)

// For now it doesn't take any arguments, because i want to use default values
// but I don't want to go through the hassle of setting it up as C++ just yet

int initSerialPort(/*uint16_t port = COM1, uint16_t baudRateDivisor = 3*/)
{
	uint16_t port = COM1;
	uint16_t baudRateDivisor = 3;

	// Enable DLAB
	out(LineControlPort(port), 0x80);

	// Set the divisor of the baud rate
	out(DivisorLowBytePort(port), baudRateDivisor & 0x00FF);
	out(DivisorHighBytePort(port), (baudRateDivisor >> 8) & 0x00FF);

	// Configure the connection parameters (1 stop bit, 8 bit data packet length)
	out(LineControlPort(port), 0x03);

	// Configure the FIFO buffers (enable, clear and 14-byte buffer)
	out(FIFOControlPort(port), 0b11000111);


	// Check if the serial port is functional

	// Set in loopback mode and send a test byte
	out(ModemControlPort(port), 0x1E);
	out(DataPort(port), 0xAE);

	if (in(DataPort(port)) != 0xAE)
	{
		return 1;
	}

	// If not faulty

	// Configure the modem (no receiving data so no interrupts handling)
	out(ModemControlPort(port), 0x03);

	return 0;
}