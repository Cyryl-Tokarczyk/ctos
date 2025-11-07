#pragma once

#include <stdint.h>

// Ref. Intel Developer Manual Vol. 3A, Chapter 2.4, Fig. 2-6
struct GDTRegister
{
	uint16_t limit; // Number of bytes in the GDT - 1
	uint32_t baseAddress;
} __attribute__((packed));

void createAndLoadGDT();

// Assembly:

void loadGDT(struct GDTRegister gdtReg);
void loadDataSegmentRegisters();
void loadCodeSegmentRegister();