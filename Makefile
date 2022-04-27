BUILD_EXT = .o .bin .iso
CC = gcc
CCFLAGS = -m32 -ffreestanding

LINKER_SCRIPT=src/linker.ld
KERNEL_OUT=pkos.bin
ISO_OUT=pkos.iso

OBJ_FILES := 
BIN_FILES := 

include src/common/main.mk
include src/kernel/main.mk
include src/screen/main.mk
include src/vga/main.mk

%.o: %.c
	${CC} ${CCFLAGS} -c $< -o $@
%.bin: %.asm
	nasm -f elf32 $< -o $@
${KERNEL_OUT}: ${OBJ_FILES} ${BIN_FILES}
	ld -m elf_i386 -T ${LINKER_SCRIPT} -o $@ ${OBJ_FILES} ${BIN_FILES}
${ISO_OUT}: ${KERNEL_OUT}
	mkdir -p build/iso/boot/grub
	cp grub.cfg build/iso/boot/grub
	cp $< build/iso/boot/grub
	grub-mkrescue -o $@ build/iso
	rm -rf build

.PHONY: all
all: ${ISO_OUT}

.PHONY: clean
clean:
	for i in ${BUILD_EXT}; do find . -name "*$$i" -delete; done

.PHONY: debug
debug: CCFLAGS += -ggdb
debug: ${KERNEL_OUT}

.PHONY: run
run: ${KERNEL_OUT}
	qemu-system-i386 -kernel $< -monitor stdio

.PHONY: run-debug
run-debug: clean debug
	qemu-system-i386 -kernel ${KERNEL_OUT} -s -S &
	gdb -x .gdbinit

.PHONY: run-iso
run-iso: ${ISO_OUT}
	qemu-system-i386 -cdrom $< -monitor stdio

