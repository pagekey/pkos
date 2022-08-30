#ifndef __KEYBOARD_MAP_H
#define __KEYBOARD_MAP_H

unsigned char keyboard_map[128] = {
  // -------- 0 to 9 --------
  ' ',
  ' ', // 1: escape key
  '1','2','3','4','5','6','7','8',
  // -------- 10 to 19 --------
  '9','0','-','=',
  ' ', // Backspace
  ' ', // Tab
  'q','w','e','r',
  // -------- 20 to 29 --------
  't','y','u','i','o','p','[',']',
  ' ', // Enter
  ' ', // left Ctrl
  // -------- 30 to 39 --------
  'a','s','d','f','g','h','j','k','l',';',
  // -------- 40 to 49 --------
  ' ','`',
  ' ', // left Shift
  ' ','z','x','c','v','b','n',
  // -------- 50 to 59 --------
  'm',',','.',
  '/', // slash, or numpad slash if preceded by keycode 224
  ' ', // right Shift
  '*', // numpad asterisk
  ' ', // left Alt
  ' ', // Spacebar
  ' ',
  ' ', // F1
  // -------- 60 to 69 --------
  ' ', // F2
  ' ', // F3
  ' ', // F4
  ' ', // F5
  ' ', // F6
  ' ', // F7
  ' ', // F8
  ' ', // F9
  ' ', // F10
  ' ',
  // -------- 70 to 79 --------
  ' ', // scroll lock
  '7', // numpad 7, HOME key if preceded by keycode 224
  '8', // numpad 8, up arrow if preceded by keycode 224
  '9', // numpad 9, PAGE UP key if preceded by keycode 224
  '-', // numpad hyphen
  '4', // numpad 4, left arrow if preceded by keycode 224
  '5', // numpad 5
  '6', // numpad 6, right arrow if preceded by keycode 224
  ' ',
  '1', // numpad 1, END key if preceded by keycode 224
  // -------- 80 to 89 --------
  '2', // numpad 2, down arrow if preceded by keycode 224
  '3', // numpad 3, PAGE DOWN key if preceded by keycode 224
  '0', // numpad 0, INSERT key if preceded by keycode 224
  '.', // numpad dot, DELETE key if preceded by keycode 224
  ' ',' ',' ',' ',' ',' ',
  // -------- 90 to 99 --------
  ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
  // -------- 100 to 109 --------
  ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
  // -------- 110 to 119 --------
  ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
  // -------- 120-127 --------
  ' ',' ',' ',' ',' ',' ',' ',' ',
};
// Right control, right alt seem to send
// keycode 224, then the left control/alt keycode
// Arrow keys also send two interrupts, one 224 and then their actual code
// Same for numpad enter
// 197: Num Lock
// 157: Pause|Break (followed by 197?)
// Clicking on screen appears to send keycodes 70, 198
  // Is this the MARK command or something like that?

#endif