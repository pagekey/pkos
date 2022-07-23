import time

from .qemu_driver import QemuDriver, parse_screen_memory


def test_help():
    driver = QemuDriver()
    driver.start()
    driver.type("sendkey h\n")
    driver.type("sendkey e\n")
    driver.type("sendkey l\n")
    driver.type("sendkey p\n")
    driver.type("sendkey kp_enter\n")
    time.sleep(1) # allow vid memory to catch up
    driver.dump_screen('screen.bin')
    driver.quit()
    time.sleep(1) # wait for it to make screen.bin
    screen_text, _ = parse_screen_memory('screen.bin')
    assert screen_text[4].strip() == 'pkos> help'
    assert screen_text[5].strip() == 'ls: List files'
    assert screen_text[6].strip() == 'clear: Clear screen'
    assert screen_text[7].strip() == 'vga: Run VGA test'
    assert screen_text[8].strip() == 'pkos>'

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
    assert screen_text[6].strip() == 'pkos>'

def test_clear():
    driver = QemuDriver()
    driver.start()
    driver.type("sendkey c\n")
    driver.type("sendkey l\n")
    driver.type("sendkey e\n")
    driver.type("sendkey a\n")
    driver.type("sendkey r\n")
    driver.type("sendkey kp_enter\n")
    time.sleep(1) # allow vid memory to catch up
    driver.dump_screen('screen.bin')
    driver.quit()
    time.sleep(1) # wait for it to make screen.bin
    screen_text, _ = parse_screen_memory('screen.bin')
    assert screen_text[0].strip() == 'pkos>'
    for line in screen_text[1:]:
        assert line.strip() == ''

def test_vga():
    driver = QemuDriver()
    driver.start()
    driver.type("sendkey v\n")
    driver.type("sendkey g\n")
    driver.type("sendkey a\n")
    driver.type("sendkey kp_enter\n")
    time.sleep(1) # allow vid memory to catch up
    driver.dump_screen('screen.bin')
    driver.quit()
    time.sleep(1) # wait for it to make screen.bin
    screen_text, _ = parse_screen_memory('screen.bin')
    # TODO actually make some assertions. See #1 on GitLab
