import os
import re
import socket
import subprocess
import time

from .qemu_driver import QemuDriver

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
    with open('screen.bin', 'rb') as screen:
        screen_bytes = screen.read()
    screen_bytes_text = bytes([screen_bytes[i] for i in range(0, len(screen_bytes), 2)])
    screen_bytes_color = bytes([screen_bytes[i] for i in range(1, len(screen_bytes), 2)])

    screen_text = screen_bytes_text.decode()
    screen_array = [
        screen_text[i*80:i*80+80] for i in range(24)
    ]
    assert screen_array[4].strip() == 'pkos> ls'
    assert screen_array[5].strip() == 'Filesystem not yet implemented.'
