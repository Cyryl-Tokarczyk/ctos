#pragma once

#include <stdint.h>

// Ref. Intel Developer Manual Vol. 3A, Section 3.4.2
struct SegmentSelector
{
    uint16_t RequestedPrivilegeLevel : 2;
    uint16_t TableIndicator : 1; // Table Indicator 0 = GDT, 1 = LDT
    uint16_t Index : 13; // Index of the GDT/LDT entry (not the offset in GDT!, i.e. second entry = 1, not 8)
} __attribute__((packed));
typedef struct SegmentSelector SegmentSelector;