import os
import re
import socket
import subprocess
import time

def test_ls():
    if os.path.exists('screen.bin'): os.remove('screen.bin')
    process = subprocess.Popen('qemu-system-i386 -nographic -monitor unix:qemu-monitor-socket,server,nowait -kernel pkos.bin'.split(), stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    time.sleep(1) # boot up
    monitor = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    monitor.connect("qemu-monitor-socket")
    monitor.send("sendkey l\n".encode())
    monitor.send("sendkey s\n".encode())
    monitor.send("sendkey kp_enter\n".encode())
    time.sleep(1) # allow vid memory to catch up
    screensize = 2 * 80 * 24
    monitor.send(f"memsave 0xb8000 {screensize} screen.bin\n".encode())
    monitor.send("q\n".encode())

    # Parse the dumped screen memory
    time.sleep(1) # wait for it to make screen.bin
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
