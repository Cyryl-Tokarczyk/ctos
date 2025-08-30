#include "i386/gdt.h"

// Refer to "Intel 64 and IA-32 Architectures Software Developer's Manual Vol. 3A" Chapter 3
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
typedef struct GDTEntryTest GDTEntryTest;

GDTEntryTest* createGDTEntry(GDTEntryTest* gdtEntry, uint8_t type)
{
	// Size of the segment (we want it to occupy the whole memory)
	// It's multiplied by 1-byte when granularity = 0
	// and by 4KB when granularity = 1

	gdtEntry->SegmentLimit0_15 = 0xFFFF;
	gdtEntry->SegmentLimit16_19 = 0xF;

	// Start address of the segment

	gdtEntry->BaseAddress0_15 = 0;
	gdtEntry->BaseAddress16_23 = 0;
	gdtEntry->BaseAddress24_31 = 0;

	gdtEntry->Type = type; // See table 3.1 in Intel Developer Manual (see above)

	gdtEntry->DescriptorType = 1; // 0 = system, 1 = code or data
	gdtEntry->DescriptorPrivilegeLevel = 0; // Highest privilege
	gdtEntry->SegmentPresent = 1; // Is the segment present in memory (generally yes)

	gdtEntry->AVL = 0; // Doesn't matter

	gdtEntry->L = 0; // In 32-bit mode should be set to 0

	gdtEntry->OperationSize = 1; // This flag should always be set to 1 for 32 - bit code and data segments

	gdtEntry->Granularity = 1; // To multiply size by 4KB

	return gdtEntry;
}

#define NumberOfGDTEntries 3

GDTEntryTest gdt[NumberOfGDTEntries];

void createAndLoadGDT()
{
	// Set up GDT

	// GDT entries:
	// 0 -> null entry (required)
	// 1 -> code segment, type 0b1010 = Execute/Read
	// 2 -> data segment, type 0b0010 = Read/Write

	gdt[0] = (GDTEntryTest){0};
	createGDTEntry(&gdt[1], 0xA);
	createGDTEntry(&gdt[2], 0x2);

	// Set up GDT descriptor (address and size)

	struct GDTDescriptor gdtDesc;
	gdtDesc.limit = sizeof(GDTEntryTest) * NumberOfGDTEntries - 1;
	gdtDesc.baseAddress = (uint32_t) gdt;

	// Load GDT with asm lgdt

	loadGDT(gdtDesc);
}