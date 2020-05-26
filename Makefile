all: build
build:
	mkdir -p build
	nasm -fbin first.asm -o build/pkos.bin
	nasm -fbin challenges/challenge1-1.asm -o build/challenge1-1.bin
	nasm -fbin challenges/challenge1-2.asm -o build/challenge1-2.bin
	nasm -fbin challenges/challenge2-1.asm -o build/challenge2-1.bin
	nasm -fbin challenges/challenge2-2.asm -o build/challenge2-2.bin
	nasm -fbin challenges/challenge3-1.asm -o build/challenge3-1.bin
	nasm -fbin challenges/challenge3-2.asm -o build/challenge3-2.bin
run: build 
	@python3 runscript.py
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
