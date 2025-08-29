#pragma once

#include <stdint.h>

struct GDTEntryTest
{
	uint16_t SegmentLimit0_15;
	uint16_t BaseAddress0_15;
	uint8_t BaseAddress16_23;
	uint8_t Type : 4;
	uint8_t DescriptorType : 1; // 0 = system, 1 = code or data
	uint8_t DescriptorPrivilegeLevel : 2;
	uint8_t SegmentPresent : 1;
	uint8_t SegmentLimit16_19 : 4;
	uint8_t AVL : 1; // Available for use by system software
	uint8_t L : 1; // 64-bit code segment (IA-32e mode only)
	uint8_t OperationSize : 1; // Default operation size(0 = 16 - bit segment; 1 = 32 - bit segment)
	uint8_t Granularity : 1;
	uint8_t BaseAddress24_31;
} __attribute__((packed));

void initGDT();