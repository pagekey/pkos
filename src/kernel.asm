bits 32
section .multiboot
	dd 0x1BADB002	; Magic number
	dd 0x0			; Flags
	dd - (0x1BADB002 + 0x0)	; Checksum

section .text

global start
global print_char_with_asm

extern main			; Defined in kernel.c

print_char_with_asm:
	mov eax, [esp + 4] ; char c
	mov [0xb8000], al
	ret

start:
	cli				; Disable interrupts
	mov esp, stack_space
	call main
	hlt

section .bss
resb 8192			; 8KB for stack
stack_space:
