#!/usr/bin/env python3

from curses import COLOR_CYAN, COLOR_GREEN
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
COMPILE_TEST_COMMAND = "g++ %s %s -lgtest -lgtest_main -pthread -fprofile-arcs -ftest-coverage"
LINK_COMMAND = "ld -m elf_i386 -T %s -o %s %s %s"

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC_DIR = os.path.join(REPO_ROOT, 'src')
TEST_DIR = os.path.join(REPO_ROOT, 'test')
BUILD_DIR = os.path.join(REPO_ROOT, 'build')
DIST_DIR = os.path.join(REPO_ROOT, 'dist')
LINKER_SCRIPT = os.path.join(REPO_ROOT, 'src', 'linker.ld')

ASM_FILES = glob.glob(os.path.join(SRC_DIR, '*', '*.asm'), recursive=True)
SOURCE_FILES = glob.glob(os.path.join(SRC_DIR, '*', '*.c'), recursive=True)
UNIT_TEST_FILES = glob.glob(os.path.join(TEST_DIR, 'unit', '*.cpp'), recursive=True)

BIN_FILES = [f.replace('.asm', '.bin') for f in ASM_FILES]
O_FILES = [f.replace('.c', '.o') for f in SOURCE_FILES]

KERNEL_OUT = os.path.join(DIST_DIR, 'pkos.bin')
ISO_OUT = os.path.join(DIST_DIR, 'pkos.iso')

def pretty_print(message, color=COLOR_GREEN_BOLD):
    print(color + message + COLOR_RESET)

def pretty_call(command, color=COLOR_GREEN_BOLD, shell=False):
    pretty_print(command, color)
    subprocess.check_call(command.split(), shell=shell)

def build():
    os.makedirs('build', exist_ok=True)
    os.makedirs('dist', exist_ok=True)
    os.makedirs('public', exist_ok=True)
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
	
    pretty_print('Built %s' % KERNEL_OUT)
    pretty_print('Built %s' % ISO_OUT)
    print("Done!")

def test():
    build()
    test_unit()
    test_integration()

def test_unit():
    pretty_call('rm -rf build')
    pretty_call('mkdir build')
    os.chdir(BUILD_DIR)
    pretty_call(
        COMPILE_TEST_COMMAND % (
            ' '.join(UNIT_TEST_FILES), 
            ' '.join(glob.glob(os.path.join(SRC_DIR, 'common', '*.c'))), # temporary workaround
            # ' '.join(SOURCE_FILES), # TODO get unit tests working with all source files
        )
    )
    pretty_call('./a.out')
    pretty_call('gcov ../test/unit/*.cpp src/common/*.cpp')
    pretty_call('lcov -b . -d . -c --output-file coverage.info')
    # not sure why this lcov cmd doesn't work with subprocess:
    pretty_print("lcov -r coverage.info '/usr/include/*' '*/test/unit/*.cpp' --output-file coverage.info")
    os.system("lcov -r coverage.info '/usr/include/*' '*/test/unit/*.cpp' --output-file coverage.info")
    pretty_call('genhtml coverage.info --output-directory ../public/')
    os.chdir(REPO_ROOT)

def test_integration():
    pretty_call('pytest %s' % os.path.join(REPO_ROOT, 'test', 'integration'))

def run():
    build()
    pretty_call('qemu-system-i386 -kernel %s -monitor stdio' % KERNEL_OUT)

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
