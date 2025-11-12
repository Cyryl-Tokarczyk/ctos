#include "i386/cpu_init/idt.h"

struct IDTEntry
{
    uint16_t Offset0_15;
    SegmentSelector SegmentSelector;
    uint8_t Reserved;
    uint8_t GateType : 5; // 0b01111 for Trap Gate 32-bit
    uint8_t DescriptorPrivilegeLevel : 2;
    uint8_t SegmentPresent : 1; // Is the interrupt handler present in memory
    uint16_t Offset16_31;
} __attribute__((packed));
typedef struct IDTEntry IDTEntry;

IDTEntry* createIDTEntry(IDTEntry* idtEntry, size_t idtIndex)
{
    idtEntry->Offset0_15 = (uint32_t) isr_stub_table[idtIndex] & 0xFFFF;
    idtEntry->Offset16_31 = (uint32_t) isr_stub_table[idtIndex] >> 16;

    if (idtIndex == 0)
    {
        idtEntry->Offset0_15 = 0x1030;
        idtEntry->Offset16_31 = 0x0010;
    }    

    char buffer[24];
    printStringToSerialPort(COM1, "Address of the isr stub:");
    printStringToSerialPort(COM1, intToString((uint32_t) isr_stub_table[idtIndex] & 0xFFFF, buffer));
    printStringToSerialPort(COM1, intToString((uint32_t) isr_stub_table[idtIndex] >> 16, buffer));
    printStringToSerialPort(COM1, "\n");
    printStringToSerialPort(COM1, "Actual address of the isr stub:");
    printStringToSerialPort(COM1, intToString((uint32_t) isr_stub_table[idtIndex], buffer));
    printStringToSerialPort(COM1, "\n");

    SegmentSelector segSel;
    segSel.RequestedPrivilegeLevel = 0;
    segSel.TableIndicator = 0;
    segSel.Index = 1; // Code segment is at index 1

    idtEntry->SegmentSelector = segSel;

    idtEntry->Reserved = 0;

    idtEntry->GateType = 0b01111; // Trap Gate 32-bit
    idtEntry->DescriptorPrivilegeLevel = 0;
    idtEntry->SegmentPresent = 1; // Yes, it is present

    return idtEntry;
}

#define NumberOfIDTEntries 32 // No more entries are currently defined in idt.asm

static IDTEntry idt[NumberOfIDTEntries] __attribute__((aligned(8)));

void initIDT()
{
    // Set up IDT

    char buffer[24];
    printStringToSerialPort(COM1, "IDT table address:");
    printStringToSerialPort(COM1, intToString((uint32_t) isr_stub_table, buffer));
    printStringToSerialPort(COM1, "\n");

    for (size_t i = 0; i < NumberOfIDTEntries; i++)
    {
        createIDTEntry(&idt[i], i);
    }

    // Set up IDT register

    struct IDTRegister idtReg;
    idtReg.limit = sizeof(IDTEntry) * NumberOfIDTEntries - 1;
    idtReg.baseAddress = (uint32_t) idt;

    // Load IDT

    loadIDT(idtReg);

    // Turn on interrupts

    __asm__ volatile ("sti");
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
    [[maybe_unused]] GeneralPurposeRegisters cpuRegisters,
    uint32_t interruptNumber,
    uint32_t errorCode
)
{
    char buffer[10];
    printStringToSerialPort(COM1, "Interrupt no. ");
    printStringToSerialPort(COM1, intToString(interruptNumber, buffer));
    printStringToSerialPort(COM1, "\n");

    printStringToSerialPort(COM1, "Error code: ");
    printStringToSerialPort(COM1, intToString(errorCode, buffer));
    printStringToSerialPort(COM1, "\n");

    return;
}