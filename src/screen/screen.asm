global print_char_with_asm

print_char_with_asm:
	; OFFSET = (ROW * 80) + COL
	mov eax, [esp + 8] 		; eax = row
	mov edx, 80						; 80 (number of cols per row)
	mul edx								; now eax = row * 80
	add eax, [esp + 12] 	; now eax = row * 80 + col
	mov edx, 2						; * 2 because 2 bytes per char on screen
	mul edx
	mov edx, 0xb8000			; vid mem start in edx
	add edx, eax					; Add our calculated offset
	mov eax, [esp + 4] 		; char c
	mov [edx], al
	ret