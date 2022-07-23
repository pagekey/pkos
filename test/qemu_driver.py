import os
import socket
import subprocess
import time

SCREEN_WIDTH = 80
SCREEN_HEIGHT = 24

class QemuDriver:
    def __init__(self):
        self.monitor = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    def start(self):
        if os.path.exists('screen.bin'): os.remove('screen.bin')
        process = subprocess.Popen('qemu-system-i386 -nographic -monitor unix:qemu-monitor-socket,server,nowait -kernel pkos.bin'.split(), stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        time.sleep(0.5) # boot up
        self.monitor.connect("qemu-monitor-socket")
    def type(self, message):
        self.monitor.send(message.encode())
    def dump_screen(self, filename):
        screensize = 2 * SCREEN_WIDTH * SCREEN_HEIGHT
        self.type(f"memsave 0xb8000 {screensize} {filename}\n")
    def quit(self):
        self.type("q\n")

def parse_screen_memory(filename):
    with open(filename, 'rb') as screen:
        screen_bytes = screen.read()
    screen_bytes_text = bytes([screen_bytes[i] for i in range(0, len(screen_bytes), 2)])
    screen_bytes_color = bytes([screen_bytes[i] for i in range(1, len(screen_bytes), 2)])
    screen_text = screen_bytes_text.decode()
    screen_color = screen_bytes_color.decode()
    screen_text_array = [
        screen_text[i*SCREEN_WIDTH:(i+1)*SCREEN_WIDTH] for i in range(SCREEN_HEIGHT)
    ]
    screen_color_array = [
        screen_color[i*SCREEN_WIDTH:(i+1)*SCREEN_WIDTH] for i in range(SCREEN_HEIGHT)
    ]
    return screen_text_array, screen_color_array
