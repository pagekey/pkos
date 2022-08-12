#!/usr/bin/env python3

from curses import COLOR_CYAN
import glob
import os
import subprocess
import sys

COLOR_RED_BOLD = '\033[31;1m'
COLOR_YELLOW_BOLD = '\033[33;1m'
COLOR_GREEN_BOLD = '\033[32;1m'
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

def pretty_print(message, color=COLOR_RESET):
    print(color + message + COLOR_RESET)

def pretty_call(command, color=COLOR_RESET):
    pretty_print(command)
    subprocess.check_call(command.split())

def build():
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
    pretty_call(rendered_command, COLOR_CYAN_BOLD)
    
    # Generate ISO file
    pretty_call('mkdir -p build/iso/boot/grub', COLOR_CYAN_BOLD)
    pretty_call('cp grub.cfg build/iso/boot/grub', COLOR_CYAN_BOLD)
    pretty_call('cp %s build/iso/boot/grub' % KERNEL_OUT, COLOR_CYAN_BOLD)
    pretty_call('grub-mkrescue -o %s build/iso' % ISO_OUT, COLOR_CYAN_BOLD)
    pretty_call('rm -rf build', COLOR_CYAN_BOLD)
	
    pretty_print('Built %s' % KERNEL_OUT, COLOR_GREEN_BOLD)
    pretty_print('Built %s' % ISO_OUT, COLOR_GREEN_BOLD)
    print("Done!")

def test():
    build()
    pretty_call(os.path.join(REPO_ROOT, 'scripts', 'test_unit'), COLOR_GREEN_BOLD)
    pretty_call('pytest %s' % os.path.join(REPO_ROOT, 'test', 'integration'), COLOR_GREEN_BOLD)

def run():
    build()
    pretty_call('qemu-system-i386 -kernel %s -monitor stdio' % KERNEL_OUT, COLOR_GREEN_BOLD)

def print_usage():
    print("Usage: %s [build,test,run]" % sys.argv[0])
    sys.exit(1)

# TODO add debug build
# TODO add unit test build to this system
# TODO add clean command
# TODO maybe remove docker_run, docker_run_debug, allow any command in docker_shell

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print_usage()
    elif sys.argv[1] == 'build':
        build()
    elif sys.argv[1] == 'test':
        test()
    elif sys.argv[1] == 'run':
        run()
    else:
        print("Command not recognized: %s" % sys.argv[1])
        print_usage()
