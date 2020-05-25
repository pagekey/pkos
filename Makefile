all: build
build:
	mkdir -p build
	nasm -fbin first.asm -o build/pkos.bin
run: build 
	qemu-system-i386 build/pkos.bin
iso: build 
	mkdir -p build/iso
	dd if=/dev/zero of=build/iso/pkos.img bs=1024 count=1440
	dd if=build/pkos.bin of=build/iso/pkos.img seek=0 count=1 conv=notrunc
	genisoimage -quiet -V 'PKOS' -input-charset iso8859-1 -o build/pkos.iso -b pkos.img -hide build/iso/pkos.img build/iso
	rm -rf build/iso
run-iso: iso 
	qemu-system-i386 -cdrom build/pkos.iso
clean:
	rm -rf build
