#include "stdlib.h"

bool streq(char* string1, int str1len, char* string2, int str2len) {
	if (str1len != str2len) return false;
	for (int i = 0; i < str1len; i++) {
		if (string1[i] != string2[i]) return false;
	}
	return true;
}