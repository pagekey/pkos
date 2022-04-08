BOOT=src/kernel/kernel.asm
KERNEL=src/kernel/kernel.c
ISOFILE=build/pkos.iso
ISO_VOLUME_NAME=PKOS
LINKER=src/linker.ld
KERNEL_OUT=build/pkos.bin
ISO_OUT=build/pkos.iso

# TODO split into separate makefiles per mini-package

all: build
build: clean
	mkdir -p build
	nasm -f elf32 ${BOOT} -o build/boot.o
	nasm -f elf32 src/screen/screen.asm -o build/screen_asm.o
	gcc -m32 -ffreestanding -c ${KERNEL} -o build/kernel.o
	gcc -m32 -ffreestanding -c src/common/stdlib.c -o build/stdlib.o
	gcc -m32 -ffreestanding -c src/screen/screen.c -o build/screen.o
	ld -m elf_i386 -T ${LINKER} -o ${KERNEL_OUT} build/boot.o build/kernel.o build/stdlib.o build/screen.o build/screen_asm.o
build_debug: clean
	mkdir -p build
	nasm -f elf32 ${BOOT} -o build/boot.o
	gcc -m32 -ffreestanding -c ${KERNEL} -o build/kernel.o -ggdb
	gcc -m32 -ffreestanding -c src/stdlib.c -o build/stdlib.o -ggdb
	gcc -m32 -ffreestanding -c src/screen.c -o build/screen.o -ggdb
	ld -m elf_i386 -T ${LINKER} -o ${KERNEL_OUT} build/boot.o build/kernel.o build/stdlib.o build/screen.o
run: build
	qemu-system-i386 -kernel ${KERNEL_OUT} -monitor stdio
run-iso: iso
	qemu-system-i386 -cdrom ${ISO_OUT} -monitor stdio
debug: build_debug
	qemu-system-i386 -kernel ${KERNEL_OUT} -s -S &
	gdb -x .gdbinit
iso: build
	mkdir -p build/iso/boot/grub
	cp grub.cfg build/iso/boot/grub
	cp ${KERNEL_OUT} build/iso/boot/grub
	grub-mkrescue -o ${ISO_OUT} build/iso
	rm -rf build/iso
clean:
	rm -rf build
