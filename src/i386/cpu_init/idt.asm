extern commonInterruptHandler

%macro isr_error_stub 1
isr_stub_%1:
    push dword %1 ; interrupt number
    pushad
    call commonInterruptHandler
    popad
    add esp, 4 ; 'pop' the interrupt number
    iret
%endmacro

%macro isr_no_error_stub 1
isr_stub_%1:
    push dword 0 ; push 0 in place of an error code
    push dword %1 ; interrupt number
    pushad
    call commonInterruptHandler
    popad
    add esp, 8 ; 'pop' the interrupt number and added error code
    iret
%endmacro

; generate all the neccessary handlers

isr_no_error_stub 0
isr_no_error_stub 1
isr_no_error_stub 2
isr_no_error_stub 3
isr_no_error_stub 4
isr_no_error_stub 5
isr_no_error_stub 6
isr_no_error_stub 7
isr_error_stub    8
isr_no_error_stub 9
isr_error_stub    10
isr_error_stub    11
isr_error_stub    12
isr_error_stub    13
isr_error_stub    14
isr_no_error_stub 15
isr_no_error_stub 16
isr_error_stub    17
isr_no_error_stub 18
isr_no_error_stub 19
isr_no_error_stub 20
isr_no_error_stub 21
isr_no_error_stub 22
isr_no_error_stub 23
isr_no_error_stub 24
isr_no_error_stub 25
isr_no_error_stub 26
isr_no_error_stub 27
isr_no_error_stub 28
isr_no_error_stub 29
isr_error_stub    30
isr_no_error_stub 31

; generate a table containing pointers to all the handlers
; so that it's not neccessary to generate all of the definitions
; in the C header file

global isr_stub_table

isr_stub_table:
%assign i 0
%rep 32
    dd isr_stub_%+i
%assign i i+1
%endrep