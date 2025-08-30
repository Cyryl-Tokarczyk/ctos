global checkLineA20

; Check A20 line
; Returns to caller if A20 gate is cleared.
; Continues to A20_on if A20 line is set.
; Written by Elad Ashkcenazi 

checkLineA20:   
    pushad
    mov edi,0x112345  ;odd megabyte address.
    mov esi,0x012345  ;even megabyte address.
    mov [esi],esi     ;making sure that both addresses contain diffrent values.
    mov [edi],edi     ;(if A20 line is cleared the two pointers would point to the address 0x012345 that would contain 0x112345 (edi)) 
    cmpsd             ;compare addresses to see if the're equivalent.
    popad
    jne A20_on        ;if not equivalent , A20 line is set.
    mov eax, 1
    ret               ;if equivalent , the A20 line is cleared.

A20_on:
    mov eax, 0
    ret

global enableProtectedModeAndLoadCodeSegmentRegister

enableProtectedModeAndLoadCodeSegmentRegister:
    mov eax, cr0
    or eax, 1 ; set bit 0 (PE) for PM
    mov cr0, eax
    jmp 0x08:.clearCS
.clearCS:
    ret