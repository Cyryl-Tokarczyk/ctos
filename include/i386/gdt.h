#pragma once

#include <stdint.h>

// Ref. Intel Developer Manual Vol. 3A, Chapter 2.4
struct GDTDescriptor
{
	uint16_t limit; // Number of bytes in the GDT - 1
	uint32_t baseAddress;
} __attribute__((packed));

void createAndLoadGDT();

void loadGDT(struct GDTDescriptor gdtDesc);
void loadDataSegmentRegisters();
void loadCodeSegmentRegister();