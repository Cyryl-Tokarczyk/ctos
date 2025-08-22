MAGIC_NUMBER equ 0x1BADB002 ; multiboot specification
FLAGS equ 0x0
CHECKSUM equ -MAGIC_NUMBER

KERNEL_STACK_SIZE equ 4096

section .multiboot
align 4						; also multiboot
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

section .text
global loader
extern kernel_main
loader:
	mov esp, kernel_stack_top	; initialize the stack
								; by moving esp to the start
	call kernel_main
	hlt

section .bss
align 4
kernel_stack_bottom:
	resb KERNEL_STACK_SIZE
kernel_stack_top: