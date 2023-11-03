#include "mergesort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int int_comparator(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}
int char_comparator(const void* a, const void* b) { 
	return *(char*)a - *(char*)b;
}
int str_comparator(const void* a, const void* b) { 
	return strcmp(*(char**)a, *(char**)b);
}

int main(int argc, char *argv[]) {
	size_t element_size = 0;
	size_t elements = argc - 2;

	if (strcmp(argv[1], "int") == 0) {
		element_size = sizeof(int);
		int* array = malloc(elements * element_size);
		assert(array);
		for (size_t i = 0; i < elements; i++)
			*(array + i) = atoi(argv[i + 2]);
		if (mergesort(array, elements, element_size, int_comparator) == -1) {
			printf("Error: memory allocation failed.");
			return -1;
		}
		for (size_t i = 0; i < elements; i++)
			if (i != elements - 1)
				printf("%d ", *(array + i));
			else
				printf("%d\n", *(array + i));
		free(array);
	}
	else if (strcmp(argv[1], "char") == 0) {
		element_size = sizeof(char);
		char* array = malloc(elements);
		assert(array);
		for (size_t i = 0; i < elements; i++)
			*(array + i) = *(argv[i + 2]);
		if (mergesort(array, elements, element_size, char_comparator) == -1) {
			printf("Error: memory allocation failed.");
			return -1;
		}
		for (size_t i = 0; i < elements; i++)
			if (i != elements - 1)
				printf("%c ", *(array + i));
			else
				printf("%c\n", *(array + i));
		free(array);
	}
	else if (strcmp(argv[1], "str") == 0) {
		element_size = sizeof(char*);
		char** array = malloc(elements * element_size);
		assert(array);
		for (size_t i = 0; i < elements; i++) {
			array[i] = argv[i + 2];
		}
		if (mergesort(array, elements, element_size, str_comparator) == -1) {
			printf("Error: memory allocation failed.");
			return -1;
		}
		for (size_t i = 0; i < elements; i++)
			if (i != elements - 1)
				printf("%s ", *(array + i));
			else
				printf("%s\n", *(array + i));
		free(array);
	}

	return 0;
}