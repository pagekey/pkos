LINKER_SCRIPT=src/linker.ld
KERNEL_OUT=build/pkos.bin
ISO_OUT=build/pkos.iso

OBJ_FILES := 
BIN_FILES := 

include src/common/main.mk
include src/kernel/main.mk
include src/screen/main.mk

%.o: %.c
	gcc -m32 -ffreestanding -c $< -o $@
%.bin: %.asm
	nasm -f elf32 $< -o $@
${KERNEL_OUT}: ${OBJ_FILES} ${BIN_FILES}
	ld -m elf_i386 -T ${LINKER_SCRIPT} -o $@ ${OBJ_FILES} ${BIN_FILES}
${ISO_OUT}: build/pkos.bin
	mkdir -p build/iso/boot/grub
	cp grub.cfg build/iso/boot/grub
	cp $^ build/iso/boot/grub
	grub-mkrescue -o $@ build/iso
	rm -rf build/iso

BUILD_EXT = .o .bin
clean:
	rm -rf build
	for i in ${BUILD_EXT}; do find . -name "*$$i" -delete; done

all: ${ISO_OUT}

# build_debug: clean
# 	mkdir -p build
# 	nasm -f elf32 ${BOOT} -o build/boot.o
# 	gcc -m32 -ffreestanding -c ${KERNEL} -o build/kernel.o -ggdb
# 	gcc -m32 -ffreestanding -c src/stdlib.c -o build/stdlib.o -ggdb
# 	gcc -m32 -ffreestanding -c src/screen.c -o build/screen.o -ggdb
# 	ld -m elf_i386 -T ${LINKER} -o ${KERNEL_OUT} build/boot.o build/kernel.o build/stdlib.o build/screen.o
# run: build
# 	qemu-system-i386 -kernel ${KERNEL_OUT} -monitor stdio
# run-iso: iso
# 	qemu-system-i386 -cdrom ${ISO_OUT} -monitor stdio
# debug: build_debug
# 	qemu-system-i386 -kernel ${KERNEL_OUT} -s -S &
# 	gdb -x .gdbinit
