#define ROWS 25
#define COLS 80

extern void print_char_with_asm(char c);

void main()
{
	char* mem = (char*) 0xb8000;
	// Fill the screen with 'x'
	int i, j;
	for (i = 0; i < COLS; i++) {
		for (j = 0; j < ROWS; j++) {
			mem[(i + COLS * j)*2] = 'x';
		}
	}
	mem[0] = '-';
	mem[2] = 'O';
	mem[4] = 'S';
	mem[6] = '9';
	mem[8] = '-';
	print_char_with_asm('Q');
}
