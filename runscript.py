#!/usr/bin/env python3

import os
import glob

choice = -1

#options = glob.glob(os.path.join('build','challenge*.bin'))
options = [
	('challenge1-1', 'Read character, then print it, infinitely.'),
	('challenge1-2', 'If you read an enter character, reboot.'),
	('challenge2-1', 'Clear the screen.'),
	('challenge2-2', 'Write something in the middle of the empty screen.'),
	('challenge3-1', 'Switch to VGA mode and fill the screen with a color.'),
	('challenge3-2', 'Use the wait function to animate the fill.'),
]

while choice < 0 or choice >= len(options):
	print('------------------------------------------------------')
	print('Please choose a challenge to run by entering a number.')
	print('------------------------------------------------------')
	for i,opt in enumerate(options):
		print('(%d) %s: %s' % (i+1, opt[0], opt[1]))
	userin = input('> ')
	try:
		choice = int(userin) - 1
	except ValueError:
		pass

print('Running %s.' % options[choice][0])

path = os.path.join('build', options[choice][0] + '.bin')
command = 'qemu-system-i386 %s' % path
print(command)
os.system(command)
