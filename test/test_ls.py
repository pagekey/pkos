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
    time.sleep(1) # allow vid memory to catch up
    driver.dump_screen('screen.bin')
    driver.quit()
    time.sleep(1) # wait for it to make screen.bin
    screen_text, _ = parse_screen_memory('screen.bin')
    assert screen_text[4].strip() == 'pkos> ls'
    assert screen_text[5].strip() == 'Filesystem not yet implemented.'
