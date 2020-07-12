// ----- Pre-processor constants -----
#define ROWS 25
#define COLS 80
// IDT_SIZE: Specific to x86 architecture
#define IDT_SIZE 256
// KERNEL_CODE_SEGMENT_OFFSET: the first segment after the null segment in gdt.asm
#define KERNEL_CODE_SEGMENT_OFFSET 0x8
// 32-bit Interrupt gate: 0x8E
// ( P=1, DPL=00b, S=0, type=1110b => type_attr=1000_1110b=0x8E) (thanks osdev.org)
#define IDT_INTERRUPT_GATE_32BIT 0x8e


// ----- External functions -----
extern void print_char_with_asm(char c, int row, int col);
extern void load_gdt();
extern void keyboard_handler();

// ----- Structs -----
struct IDT_entry {
	unsigned short offset_lowerbits; // 16 bits
	unsigned short selector; // 16 bits
	unsigned char zero; // 8 bits
	unsigned char type_attr; // 8 bits
	unsigned short offset_upperbits; // 16 bits
};

// ----- Global variables -----
struct IDT_entry IDT[IDT_SIZE]; // This is our entire IDT. Room for 256 interrupts

void load_idt() {
	// Get the address of the keyboard_handler code in kernel.asm as a number
	int offset = (int)keyboard_handler;
	// Populate the first entry of the IDT
	IDT[0].offset_lowerbits = offset & 0x0000FFFF; // lower 16 bits
	IDT[0].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0].zero = 0;
	IDT[0].type_attr = IDT_INTERRUPT_GATE_32BIT;
	IDT[0].offset_upperbits = (offset & 0xFFFF0000) >> 16;
}

void handle_keyboard_interrupt() {
	print_char_with_asm('K',0,0);
}

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

// ----- Entry point -----
void main() {
	load_gdt();
	load_idt();
	print_message();
}
