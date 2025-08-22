global out

; out - send a byte to one of the I/O ports
; stack: 
;		[esp + 8] - data byte
;		[esp + 4] - port address
;		[esp] - return address

out:
	mov al, [esp + 8]
	mov dx, [esp + 4]
	out dx, al
	ret

global in

; in - read a byte from one of the I/O ports
; stack:
;		[esp + 4] - port address

in:
	mov dx, [esp + 4]
	mov eax, 0
	in al, dx
	ret