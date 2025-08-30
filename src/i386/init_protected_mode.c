#include "i386/init_protected_mode.h"

int initProtectedMode()
{
    asm("cli"); // Disable interrupts
    createAndLoadGDT();
    enableProtectedModeAndLoadCodeSegmentRegister(); // Enable PM and load the code segment register (with far jump) 
	loadDataSegmentRegisters(); // Load the data segment registers
    if (checkLineA20() != 0) return 1;

    return 0;
}