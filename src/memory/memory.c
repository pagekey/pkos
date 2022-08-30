
extern void _memcpy_asm(unsigned int dest, unsigned int src, unsigned int size); // see stdlib.asm
void memcpy(unsigned int dest, unsigned int src, unsigned int size) {
	_memcpy_asm(dest, src, size);
}

extern void _memset_asm(unsigned int addr, unsigned char fill, unsigned int size); // see stdlib.asm
void memset(unsigned int addr, unsigned char fill, unsigned int size) {
	_memset_asm(addr, fill, size);
}