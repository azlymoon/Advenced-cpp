#include "str.h"

#include <stdio.h>

char* my_strcpy(char* destination, const char* source) {
	char* temp = destination;
	while ((*destination++ = *source++));
	return temp;
}

long unsigned int my_strlen(const char* string) {
	long unsigned int size_str = 0;
	while ((*string++))
		size_str++;
	return size_str;
}

char* my_strcat(char* destination, const char* source) {
	char* temp = destination + my_strlen(destination);
	while ((*temp++ = *source++));
	return destination;
}

int my_strcmp(const char* string1, const char* string2) {
	while (*string1) {
		if (*string1 != *string2)
			break;
		string1++, string2++;
	}
	return *(const unsigned char*)string1 - *(const unsigned char*)string2;
}