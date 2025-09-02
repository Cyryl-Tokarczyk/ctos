#include "i386/cpu_init/gdt.h"

int initProtectedMode();

int checkLineA20();
void enableProtectedModeAndLoadCodeSegmentRegister();