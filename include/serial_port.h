#pragma once

#include <stddef.h>
#include <stdint.h>

#include "io.h"

enum SerialPorts
{
	COM1 = 0x3F8,
};

int initSerialPort(uint16_t port, uint16_t baudRateDivisor);

void printToSerialPort(uint16_t port, char* string);