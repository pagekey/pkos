#define ROWS 25
#define COLS 80

extern void print_char_with_asm(char c, int row, int col);
extern void load_gdt();

void print_message() {
	// Fill the screen with 'x'
	int i, j;
	for (i = 0; i < COLS; i++) {
		for (j = 0; j < ROWS; j++) {
			print_char_with_asm('*',j,i);
		}
	}
	print_char_with_asm('-',0,0);
	print_char_with_asm('P',0,1);
	print_char_with_asm('K',0,2);
	print_char_with_asm('O',0,3);
	print_char_with_asm('S',0,4);
	print_char_with_asm('-',0,5);
}

void main() {
	load_gdt();
	print_message();
}
