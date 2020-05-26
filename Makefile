BOOTLOADER=src/boot.asm
KERNEL=src/kernel.c
BINFILE=build/pkos.bin
ISOFILE=build/pkos.iso
ISO_VOLUME_NAME=PKOS

all: build
build:
	mkdir -p build
	nasm -fbin ${BOOTLOADER} -o build/boot.bin
	gcc -ffreestanding -c ${KERNEL} -o build/kernel.o
	ld -o build/kernel.bin -Ttext 0x1000 build/kernel.o --oformat binary
	cat build/boot.bin build/kernel.bin > ${BINFILE}
run: build 
	qemu-system-i386 ${BINFILE}
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
