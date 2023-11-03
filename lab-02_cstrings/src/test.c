#include "test_str.h"
#include <stdio.h>

int main() {
	printf("======== TESTS ========\n");

	strcpy_suit();
	strlen_suit();
	strcat_suit();
	strcmp_suit();

	if (all_tests_passed) {
		printf("======== All tests passed ========\n");
	}
	else {
		printf("======== Some tests failed ========\n");
	}

	return all_tests_passed ? 0 : 1;
}