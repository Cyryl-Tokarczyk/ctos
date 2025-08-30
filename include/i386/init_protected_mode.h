#include "i386/gdt.h"

int initProtectedMode();

int checkLineA20();
void enableProtectedModeAndLoadCodeSegmentRegister();