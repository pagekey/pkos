#include "stdlib.h"

char* itoa(int integer, char* result) {
	int num_digits = 0;
    // Push each digit
	while (integer > 0) {
        // Mod 10 gets just the last digit
        // Adding '0' turns it into an ASCII character
		result[num_digits] = (integer % 10) + '0';
		num_digits++;
        // Divide by 10 to get the next character in line
		integer /= 10;
	}
    // Reverse it and return it
    char tmp = 0;
    for (int i = 0; i < num_digits/2; i++) {
        // Swap at each end of the array
        tmp = result[i];
        result[i] = result[num_digits-i-1];
        result[num_digits-i-1] = tmp;
    }
    // Null terminate the string
    result[num_digits] = '\0';
	return result;
}

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
