#define ROWS 25
#define COLS 80

extern void print_char_with_asm(char c, int row, int col);
extern void load_gdt();

void main()
{
	load_gdt();
	char* mem = (char*) 0xb8000;
	// Fill the screen with 'x'
	int i, j;
	for (i = 0; i < COLS; i++) {
		for (j = 0; j < ROWS; j++) {
			print_char_with_asm('Q',j,i);
		}
	}
	// mem[0] = '-';
	// mem[2] = 'O';
	// mem[4] = 'S';
	// mem[6] = '9';
	// mem[8] = '-';
	print_char_with_asm('-',0,0);
	print_char_with_asm('O',0,1);
	print_char_with_asm('S',0,2);
	print_char_with_asm('1',0,3);
	print_char_with_asm('1',0,4);
	print_char_with_asm('-',0,5);
}
