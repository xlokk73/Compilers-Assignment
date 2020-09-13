#ifndef TEST_H
#define TEST_H

#include <string>
#include <fstream>



bool int_is_equal(int n1, int n2);

bool str_is_equal(std::string s1, std::string s2);

void fill_file(const char* file_name, const std::string input);

void report(int n);

void test_lexer();


#endif
