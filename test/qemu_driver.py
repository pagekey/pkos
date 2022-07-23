import os
import socket
import subprocess
import time

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
    def quit(self):
        self.type("q\n")
