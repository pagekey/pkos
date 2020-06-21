BOOT=src/boot.asm
KERNEL=src/kernel.c
ISOFILE=build/pkos.iso
ISO_VOLUME_NAME=PKOS
LINKER=src/linker.ld
KERNEL_OUT=build/pkos_kernel

all: build
build: clean
	mkdir -p build
	nasm -f elf32 ${BOOT} -o build/boot.o
	gcc -m32 -ffreestanding -c ${KERNEL} -o build/kernel.o
	ld -m elf_i386 -T ${LINKER} -o ${KERNEL_OUT} build/boot.o build/kernel.o
run: build 
	qemu-system-i386 -kernel ${KERNEL_OUT}
iso: build 
	mkdir -p build/iso
	dd if=/dev/zero of=build/iso/pkos.img bs=1024 count=1440
	dd if=${BINFILE} of=build/iso/pkos.img seek=0 count=1 conv=notrunc
	genisoimage -quiet -V '${ISO_VOLUME_NAME}' -input-charset iso8859-1 -o ${ISOFILE} -b pkos.img -hide build/iso/pkos.img build/iso
	rm -rf build/iso
run-iso: iso
	qemu-system-i386 -cdrom ${ISOFILE} 
clean:
	rm -rf build
