#include "gdt.h"

// Refer to "Intel® 64 and IA-32 Architectures Software Developer’s Manual Vol. 3A" Chapter 3
// for further explanation

struct GDTEntry
{
	uint16_t SegmentLimit0_15;
	uint16_t BaseAddress0_15;
	uint8_t BaseAddress16_23;
	
} __attribute__((packed));

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
	uint8_t AVL : 1; // Free bit not used by the CPU
	uint8_t L : 1; // 64-bit code segment (IA-32e mode only)
	uint8_t OperationSize : 1; // Default operation size(0 = 16 - bit segment; 1 = 32 - bit segment)
	uint8_t Granularity : 1;
	uint8_t BaseAddress24_31;
} __attribute__((packed));

void initGDT()
{
	// Set up GDT

	// GDT entries:
	// 0 -> null entry (required)
	// 1 -> code segment
	// 2 -> data segment

	struct GDTEntryTest gdt[3];

	gdt[0] = 0;

	// Size of the segment (we want it to occupy the whole memory)
	// It's multiplied by 1-byte when granularity = 0
	// and by 4KB when granularity = 1

	gdt[1].SegmentLimit0_15 = 0xFFFF;
	gdt[1].SegmentLimit16_19 = 0xF;

	// Start address of the segment

	gdt[1].BaseAddress0_15 = 0;
	gdt[1].BaseAddress16_23 = 0;
	gdt[1].BaseAddress24_31 = 0;

	// Type 0b1010 means Execute/Read

	gdt[1].Type = 0xA;

	gdt[1].DescriptorType = 1;
	gdt[1].DescriptorPrivilegeLevel = 0; // Highest privilege
	gdt[1].SegmentPresent = 1;

	gdt[1].AVL = 0;

	gdt[1].L = 0; // In 32-bit mode should be set to 0

	gdt[1].OperationSize = 1; // This flag should always be set to 1 for 32 - bit code and data segments

	gdt[1].Granularity = 1; // To multiply size by 4KB

	// Set up GDT descriptor (address and size)

	// Load GDT with asm lgdt

	// Load the segment registers

	// Load the code segment register (with far jump)
}