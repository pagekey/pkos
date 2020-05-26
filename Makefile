BOOTLOADER=src/boot.asm
BINFILE=build/pkos.bin
ISOFILE=build/pkos.iso
ISO_VOLUME_NAME=PKOS

all: build
build:
	mkdir -p build
	nasm -fbin ${BOOTLOADER} -o ${BINFILE} 
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
