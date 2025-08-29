global loadGDT

loadGDT:
    cli ; turn off interrupts
    lgdt [esp + 4] ; load the GDT descriptor
    ret

global loadDataSegmentRegisters
global loadCodeSegmentRegister

; data segment register layout:
; 0 - 1 -> Requested Privilege Level
; 2     -> Table Indicator 0 = GDT, 1 = LDT
; 3 - 15 -> index of the GDT/LDT entry

loadDataSegmentRegisters:
    mov ax, 0x10    ; we load the data registers with 0x10
    mov ss, ax      ; because we want RPL = 0,
    mov ds, ax      ; Table Indicator = GDT
    mov es, ax      ; index = 2 (our data segment)
    mov fs, ax
    mov gs, ax
    ret

loadCodeSegmentRegister:
    jmp 0x08:.loadCS ; 0x08 points means index of the code segment in GDT = 1
.loadCS:
    ret