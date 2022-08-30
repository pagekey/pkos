#ifndef __STDLIB_H
#define __STDLIB_H

#include "types.h"

char* itoa(int integer, char* result);
char* itoah(int integer, char* result);
char* itoab(int integer, char* result);

bool streq(char* string1, char* string2);
bool safe_streq(char* string1, int str1len, char* string2, int str2len);

void terrible_sleep_impl(int ticks);

#endif