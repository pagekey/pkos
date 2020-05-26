bits 16
[org 0x7c00]

	mov si, STR1
	call print_string
	
	mov al, 0x2	; number of sectors: 2
	mov bx, 0x0 	; read memory es:bx
	mov es, bx	; 0x0:0x9000 = 0x9000
	mov bx, 0x9000
	call disk_read

	; Print out the character at location read from disk
	mov ah, 0xe
	mov al, [0x9200]
	int 0x10
	jmp $

	STR1: db "Reading from 0x9200: ",0

	%include "src/inc/print_string.asm"
	%include "src/inc/disk_read.asm"

	times 510-($-$$) db 0
	dw 0xaa55

times 512 db 'f'
times 512 db 'x'
