import os
import re
import subprocess
import time

def strip_ansi_escape(text):
    ansi_escape = re.compile(r'\x1B\[[0-?]*[ -/]*[@-~]')
    subbed = ansi_escape.sub('', text)
    return subbed

def test_ls():
    if os.path.exists('screen.bin'): os.remove('screen.bin')
    process = subprocess.Popen('qemu-system-i386 -monitor stdio -kernel pkos.bin'.split(), stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    time.sleep(1) # boot up
    process.stdin.write("sendkey l\n".encode())
    process.stdin.write("sendkey s\n".encode())
    process.stdin.write("sendkey kp_enter\n".encode())
    process.stdin.flush()
    time.sleep(1) # allow vid memory to catch up
    screensize = 2 * 80 * 24
    process.stdin.write(f"memsave 0xb8000 {screensize} screen.bin\n".encode())
    process.stdin.write("q\n".encode())
    process.stdin.flush()

    # One approach: Try to parse through the terminal output (and have to deal with ANSI escape chars, etc.)
    # output_bytes, _ = process.communicate()
    # output = output_bytes.decode()
    # lines = [strip_ansi_escape(l) for l in output.split('\r\n')]
    # lines = [l for l in lines if not l.startswith('(qemu)') and not l.startswith('QEMU 4.2.1 monitor')]

    # Another approach: simply parse the dumped screen memory!
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
