#include "stdlib.h"

bool streq(char* string1, char* string2) {
	int i = 0;
	while (true) {
		// Char mismatch? false
		if (string1[i] != string2[i]) {
			return false;
		}
		// They're equal, AND it's null char? We're done
		if (string1[i] == '\0') {
			break;
		}
		i++;
	}
	return true;
}

bool safe_streq(char* string1, int str1len, char* string2, int str2len) {
	if (str1len != str2len) return false;
	for (int i = 0; i < str1len; i++) {
		if (string1[i] != string2[i]) return false;
	}
	return true;
}
