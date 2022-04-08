#ifndef __SCREEN_H
#define __SCREEN_H

void println(char* string, int len);
void print(char* string, int len);
void printchar(char c, int row, int col);
extern void print_char_with_asm(char c, int row, int col);
void clear_screen();
void print_prompt();
void print_message();

#endif