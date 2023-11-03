#include "test_str.h"
#include "str.h"
#include <string.h>
#include <stdio.h>

int all_tests_passed = 1;

void test_my_strcpy(const char* test_name, const unsigned dst_sz, const char* src_str)
{
	char res[dst_sz];
	int retval_ok = my_strcpy(res, src_str) == res;
	int cmp_ok = strcmp(res, src_str) == 0;
	if (retval_ok && cmp_ok) {
		printf("%s - %s\n", test_name, "OK");
	} else {
		printf("%s - %s\n", test_name, "Failed");
		all_tests_passed = 0;
	}
	if (!retval_ok) {
		printf("   invalid return value\n");
	}
	if (!cmp_ok) {
		printf("   '%s' vs '%s'\n", res, src_str);
	}
}

void test_my_strlen(const char* test_name, const char* src_str)
{
	int len_ok = my_strlen(src_str) == strlen(src_str);
	if (len_ok) {
		printf("%s - %s\n", test_name, "OK");
	}
	else {
		printf("%s - %s\n", test_name, "Failed");
		all_tests_passed = 0;
	}
	if (!len_ok) {
		printf("   invalid return value\n");
	}
}

void test_my_strcat(const char* test_name, char* dest, const char* src_str, const char* ans)
{
	char res[40] = {};
	strcpy(res, dest);
	int retval_ok = my_strcat(res, src_str) == res;
	int cat_ok = strcmp(res, ans) == 0;
	if (retval_ok && cat_ok) {
		printf("%s - %s\n", test_name, "OK");
	}
	else {
		printf("%s - %s\n", test_name, "Failed");
		all_tests_passed = 0;
	}
	if (!retval_ok) {
		printf("   invalid return value\n");
	}
	if (!cat_ok) {
		printf("   '%s' vs '%s'\n", res, ans);
	}
}

void test_my_strcmp(const char* test_name, char* res, const char* src_str)
{
	int cmp_ok = my_strcmp(res, src_str) == strcmp(res, src_str);
	if (cmp_ok) {
		printf("%s - %s\n", test_name, "OK");
	}
	else {
		printf("%s - %s\n", test_name, "Failed");
		all_tests_passed = 0;
	}
	if (!cmp_ok) {
		printf("   '%d' vs '%d'\n", my_strcmp(res, src_str), strcmp(res, src_str));
	}
}

void strcpy_suit() {
	printf("====== strcpy ======\n");
	test_my_strcpy("Empty", 1, "");
	test_my_strcpy("Single", 5, "a");
	test_my_strcpy("Double", 5, "ab");
	test_my_strcpy("Multi", 4, "abc");
}

void strlen_suit() {
	printf("====== strlen ======\n");
	test_my_strlen("Empty", "");
	test_my_strlen("Single", "a");
	test_my_strlen("Double", "ab");
	test_my_strlen("Multi", "abc");
}

void strcat_suit() {
	printf("====== strcat ======\n");
	test_my_strcat("Empty", "", "", "");
	test_my_strcat("Single", "", "a", "a");
	test_my_strcat("Double", "a", "ab", "aab");
	test_my_strcat("Multi", "aab", "abc", "aababc");
}

void strcmp_suit() {
	printf("====== strcmp ======\n");
	test_my_strcmp("Empty", "", "");
	test_my_strcmp("Equal", "a", "a");
	test_my_strcmp("Left larger", "ab", "a");
	test_my_strcmp("Right large", "ab", "abc");
	test_my_strcmp("Empty - No Empty", "", "abc");
	test_my_strcmp("Part of another", "bc", "abcd");
}