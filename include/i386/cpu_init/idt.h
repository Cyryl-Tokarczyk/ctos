#pragma once

#include <stdint.h>

#include "i386/cpu_structs.h"
#include "i386/serial_port.h"
#include "common/conversion.h"

// Ref. Intel Developer Manual Vol. 3A, Chapter 2.4, Fig. 2-6
struct IDTRegister
{
	uint16_t limit; // Number of bytes in the IDT, in 32bit mode = no. entries * 8 bytes
	uint32_t baseAddress;
} __attribute__((packed));

void initIDT();

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

void commonInterruptHandler(
    [[maybe_unused]] GeneralPurposeRegisters cpuRegisters,
    uint32_t interruptNumber,
    uint32_t errorCode
);

void isr_stub_1();

// Assembly:

extern void** isr_stub_table;

void loadIDT(struct IDTRegister idtReg);
