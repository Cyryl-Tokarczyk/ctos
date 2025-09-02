#include "i386/cpu_init/idt.h"

struct IDTEntry
{
    uint16_t Offset0_15;
    uint16_t SegmentSelector;
    uint8_t Reserved;
    uint8_t GateType : 5; // 0b11110 for Trap Gate 32-bit
    uint8_t DescriptorPrivilegeLevel : 2;
    uint8_t SegmentPresent : 1; // Is the interrupt handler present in memory
    uint16_t Offset16_31;
} __attribute__((packed));
typedef struct IDTEntry IDTEntry;

#define NumberOfIDTEntries 32 // No more entries are currently defined in idt.asm

static IDTEntry idt[NumberOfIDTEntries] __attribute__((aligned(8)));

void initIDT()
{

}

struct GeneralPurposeRegisters
{
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
} __attribute__((packed));
typedef struct GeneralPurposeRegisters GeneralPurposeRegisters;

// There's also additional info further on the stack:
// EIP
// CS
// EFLAGS

void commonInterruptHandler(
    GeneralPurposeRegisters cpuRegisters,
    uint16_t interruptNumber,
    uint16_t errorCode
)
{
    char buffer[10];
    printStringToSerialPort(COM1, "Interrupt no. ");
    printStringToSerialPort(COM1, intToString(interruptNumber, buffer));
    printStringToSerialPort(COM1, "\n");

    printStringToSerialPort(COM1, "Error code: ");
    printStringToSerialPort(COM1, intToString(errorCode, buffer));
    printStringToSerialPort(COM1, "\n");
}