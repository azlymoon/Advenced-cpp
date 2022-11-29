#pragma once
void test_my_strcpy(const char* test_name, const unsigned dst_sz, const char* src_str);
void test_my_strlen(const char* test_name, const char* src_str);
void test_my_strcat(const char* test_name, char* res, const char* src_str, const char* ans);
void test_my_strcmp(const char* test_name, char* res, const char* src_str);
void strcpy_suit();
void strlen_suit();
void strcat_suit();
void strcmp_suit();
extern int all_tests_passed;