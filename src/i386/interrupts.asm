; global interrupt

; ; interrupt - call the int operation
; ; stack: 
; ;		[esp + 4] - interrupt handler index
; ;		[esp] - return address

; interrupt:
;     mov ax, [esp + 4]
;     int ax
;     ret

global testInterrupts

; testInterrupts - calls all of the interrupts
; stack: 
;		[esp] - return address

testInterrupts:
    int 0
    ret

; testInterrupts:
; %assign i 0
; %rep 32
;     int %+i 
; %assign i i+1
; %endrep
;     ret