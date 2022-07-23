import os
import re
import socket
import subprocess
import time

from .qemu_driver import QemuDriver, parse_screen_memory

def test_ls():
    driver = QemuDriver()
    driver.start()
    driver.type("sendkey l\n")
    driver.type("sendkey s\n")
    driver.type("sendkey kp_enter\n")

    time.sleep(0.5) # allow vid memory to catch up
    screensize = 2 * 80 * 24
    driver.type(f"memsave 0xb8000 {screensize} screen.bin\n")
    driver.quit()

    # Parse the dumped screen memory
    time.sleep(0.5) # wait for it to make screen.bin
    screen_text, _ = parse_screen_memory('screen.bin')
    assert screen_text[4].strip() == 'pkos> ls'
    assert screen_text[5].strip() == 'Filesystem not yet implemented.'
