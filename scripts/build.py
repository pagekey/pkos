#!/usr/bin/env python3

import glob
import os
import subprocess

COLOR_RED_BOLD = '\033[31;1m'
COLOR_YELLOW_BOLD = '\033[33;1m'
COLOR_CYAN_BOLD = '\033[36;1m'
COLOR_RESET = '\033[0m'

ASSEMBLE_COMMAND = "nasm -f elf32 %s -o %s"
COMPILE_COMMAND = "gcc -m32 -ffreestanding -c %s -o %s"
LINK_COMMAND = "ld -m elf_i386 -T %s -o %s %s %s"

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC_DIR = os.path.join(REPO_ROOT, 'src')
LINKER_SCRIPT = os.path.join(REPO_ROOT, 'src', 'linker.ld')

ASM_FILES = glob.glob(os.path.join(SRC_DIR, '*', '*.asm'), recursive=True)
SOURCE_FILES = glob.glob(os.path.join(SRC_DIR, '*', '*.c'), recursive=True)

BIN_FILES = [f.replace('.asm', '.bin') for f in ASM_FILES]
O_FILES = [f.replace('.c', '.o') for f in SOURCE_FILES]

KERNEL_OUT = os.path.join(REPO_ROOT, 'pkos.bin')
ISO_OUT = os.path.join(REPO_ROOT, 'pkos.iso')

def pretty_call(command, color=COLOR_RESET):
    print(color + command + COLOR_RESET)
    subprocess.check_call(command.split())

if __name__ == "__main__":
    # Assemble assembly code
    for file_in, file_out in zip(ASM_FILES, BIN_FILES):
        rendered_command = ASSEMBLE_COMMAND % (file_in, file_out)
        pretty_call(rendered_command, COLOR_RED_BOLD)
    
    # Compile C code
    for file_in, file_out in zip(SOURCE_FILES, O_FILES):
        rendered_command = COMPILE_COMMAND % (file_in, file_out)
        pretty_call(rendered_command, COLOR_YELLOW_BOLD)
    
    # Link the assembly and C code together, create .bin file
    rendered_command = LINK_COMMAND % (
        LINKER_SCRIPT,
        KERNEL_OUT,
        ' '.join(BIN_FILES),
        ' '.join(O_FILES),
    )
    print(COLOR_CYAN_BOLD + rendered_command + COLOR_RESET)
    subprocess.check_call(rendered_command.split())
    
    # Generate ISO file
    pretty_call('mkdir -p build/iso/boot/grub', COLOR_CYAN_BOLD)
    pretty_call('cp grub.cfg build/iso/boot/grub', COLOR_CYAN_BOLD)
    pretty_call('cp %s build/iso/boot/grub' % KERNEL_OUT, COLOR_CYAN_BOLD)
    pretty_call('grub-mkrescue -o %s build/iso' % ISO_OUT, COLOR_CYAN_BOLD)
    pretty_call('rm -rf build', COLOR_CYAN_BOLD)
	
    print("Done!")