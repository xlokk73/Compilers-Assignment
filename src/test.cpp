#include "test.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "lexer/transitions.h"
#include "lexer/lexer.h"
#include "parser/ast.h"
#include "test.h"



bool int_is_equal(int n1, int n2) {
    if(n1 - n2 == 0)
        return true;
    else
        return false;
}

bool str_is_equal(std::string s1, std::string s2) {
    if(s1.compare(s2) == 0)
        return true;
    else
        return false;
}

int test_number = 0;
int tests_failed = 0;
token current_token;
FILE* stream = nullptr;
char file_name[] = "test_file.sl";


void fill_file(const char* file_name, const std::string input) {
    std::ofstream ofs;
    ofs.open(file_name, std::ofstream::out | std::ofstream::trunc);
    ofs << input; 
    ofs.close();
}

void report(int n) {
    test_number++;
    switch(n) {
    case 0:
        std::cout << "\033[;32m" << "TEST " << test_number << ": SUCCESS!" << "\033[0m" << std::endl; 
        return;
    case 1:
        std::cout << "\033[;31m" << "TEST " << test_number << ": FAILURE." << "\033[0m" << std::endl; 
        tests_failed++;
        return;
    default:
        std::cout << "\033[;36m" << "ERROR" << "\033[0m" << std::endl; 
        tests_failed++;
        return;
    }
}

void test_lexer() {
    std::cout << "TESTING LEXER" << std::endl;
    /* Test 1 */
    fill_file(file_name, "123");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);


    if(str_is_equal(current_token.value, "123") &&
       int_is_equal(current_token.type, number)) {
        report(0);
    }
    else {
        report(1);
    }


    /* Test 2 */
    fill_file(file_name, "123hello4567");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(str_is_equal(current_token.value, "123") &&
       int_is_equal(current_token.type, number)) {
       report(0);
    }
    else {
        report(1);
    }
    
    /* Test 3 */
    fill_file(file_name, "hello123");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, identifier) &&
       str_is_equal(current_token.value, "hello123")) {
       report(0);
    }
    else {
        report(1);
    }

    /* Test 4 */
    fill_file(file_name, " 123");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, number) &&
       str_is_equal(current_token.value, "123")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 5 */
    fill_file(file_name, " 123 hello");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, number) &&
       str_is_equal(current_token.value, "123")) {
        report(0);
    }
    else {
        report(1);
    }


    /* Test 6 */
    fill_file(file_name, "     123hello    haha4567");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, number) &&
       str_is_equal(current_token.value, "123")) {
        report(0);
    }
    else {
        report(1);
    }


    /* Test 7 */
    fill_file(file_name, " hello 123");
    stream = fopen(file_name, "r"); 

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, identifier) &&
       str_is_equal(current_token.value, "hello")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 8 */
    fill_file(file_name, "123.456;");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, float_num) &&
       str_is_equal(current_token.value, "123.456")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 9 */
    fill_file(file_name, "   123.456");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, float_num) &&
       str_is_equal(current_token.value, "123.456")) {
        report(0);
    }
    else {
        report(1);
    }




    /* Test 10 */
    fill_file(file_name, "  123.456hello ");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, float_num) &&
       str_is_equal(current_token.value, "123.456")) {
        report(0);
    }
    else {
        report(1);
    }


    /* Test 11 */
    fill_file(file_name, "123.");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, number) &&
       str_is_equal(current_token.value, "123")) {
        report(0);
    }
    else {
        report(1);
    }



    /* Test 12 */
    fill_file(file_name, "h123.4");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, identifier) &&
       str_is_equal(current_token.value, "h123")) {
        report(0);
    }
    else {
        report(1);
    }


    /* Test 13 */
    fill_file(file_name, "hello");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, identifier) &&
       str_is_equal(current_token.value, "hello")) {
        report(0);
    }
    else {
        report(1);
    }


    /* Test 14 */
    fill_file(file_name, "hello this is a test 123");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, identifier) &&
       str_is_equal(current_token.value, "hello")) {
        report(0);
    }
    else {
        report(1);
    }


    /* Test 15 */
    fill_file(file_name, "  hello 123 123.4567hello  ");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, identifier) &&
       str_is_equal(current_token.value, "hello")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 16 */ 
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, number) && 
       str_is_equal(current_token.value, "123")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 17 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, float_num) &&
       str_is_equal(current_token.value, "123.4567")) {
        report(0);
    }
    else {
        report(1);
    }


    /* Test 18 */
    fill_file(file_name, "float");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, var_type) &&
       str_is_equal(current_token.value, "float")) {
        report(0);
    }
    else {
        report(1);
    }


    /* Test 19 */
    fill_file(file_name, "/");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, mult_op) &&
       str_is_equal(current_token.value, "/")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 20 */
    fill_file(file_name, "*");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, mult_op) &&
       str_is_equal(current_token.value, "*")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 21 */
    fill_file(file_name, "and \n \n   float");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, mult_op) &&
       str_is_equal(current_token.value, "and")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 22 */ 
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, var_type) &&
       str_is_equal(current_token.value, "float")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 23 */
    fill_file(file_name, "+");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, add_op) &&
       str_is_equal(current_token.value, "+")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 24 */
    fill_file(file_name, "-");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, add_op) &&
       str_is_equal(current_token.value, "-")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 25 */
    fill_file(file_name, "or");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, add_op) &&
       str_is_equal(current_token.value, "or")) {
        report(0);
    }
    else {
        report(1);
    }


    /* Test 26 */
    fill_file(file_name, "  or \n \n  123.45 - 2");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, add_op) &&
       str_is_equal(current_token.value, "or")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 27 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, float_num) &&
       str_is_equal(current_token.value, "123.45")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 28 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, add_op) &&
       str_is_equal(current_token.value, "-")) {
        report(0);
    }
    else {
        report(1);
    }


    /* Test 29 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, number) &&
       str_is_equal(current_token.value, "2")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 30 */
    fill_file(file_name, "=");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, rel_op) &&
       str_is_equal(current_token.value, "=")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 31 */
    fill_file(file_name, ">");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, rel_op) &&
       str_is_equal(current_token.value, ">")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 32 */
    fill_file(file_name, "<");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, rel_op) &&
       str_is_equal(current_token.value, "<")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 33 */
    fill_file(file_name, "<=");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, rel_op) &&
       str_is_equal(current_token.value, "<=")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 34 */
    fill_file(file_name, ">=");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, rel_op) &&
       str_is_equal(current_token.value, ">=")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 35 */
    fill_file(file_name, "<=");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, rel_op) &&
       str_is_equal(current_token.value, "<=")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 36 */
    fill_file(file_name, " \n 32 >= \n 23.21a");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, number) &&
       str_is_equal(current_token.value, "32")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 37 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, rel_op) &&
       str_is_equal(current_token.value, ">=")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 38 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, float_num) &&
       str_is_equal(current_token.value, "23.21")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 39 */
    fill_file(file_name, " (\n hello )  \n {\n } ");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, srb) &&
       str_is_equal(current_token.value, "(")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 40 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, identifier) &&
       str_is_equal(current_token.value, "hello")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 41 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, erb) &&
       str_is_equal(current_token.value, ")")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 42 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, scb) &&
       str_is_equal(current_token.value, "{")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 43 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, ecb) &&
       str_is_equal(current_token.value, "}")) {
        report(0);
    }
    else {
        report(1);
    }
    
    /* Test 44 */
    fill_file(file_name, "(hello)");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, srb) &&
       str_is_equal(current_token.value, "(")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 45 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, identifier) &&
       str_is_equal(current_token.value, "hello")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 46 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, erb) &&
       str_is_equal(current_token.value, ")")) {
        report(0);
    }
    else {
        report(1);
    }

   /* Test 47 */
    fill_file(file_name, ",:;");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, comma) &&
       str_is_equal(current_token.value, ",")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 48 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, colon) &&
       str_is_equal(current_token.value, ":")) {
        report(0);
    }
    else {
        report(1);
    }
 
    /* Test 49 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, s_colon) &&
       str_is_equal(current_token.value, ";")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 50 */
    fill_file(file_name, "//hello this is a single line comment\n int 10");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, comment) &&
       str_is_equal(current_token.value, "//hello this is a single line comment\n")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 51 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, var_type) &&
       str_is_equal(current_token.value, "int")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 52 */
    fill_file(file_name, "/*hello this is a\n multi line comment\n haha*/  int 10");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, comment) &&
       str_is_equal(current_token.value, "/*hello this is a\n multi line comment\n haha*/")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 53 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, var_type) &&
       str_is_equal(current_token.value, "int")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 54 */
    fill_file(file_name, "let blablabla");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, keyword) &&
       str_is_equal(current_token.value, "let")) {
        report(0);
    }
    else {
        report(1);
    }

    

    /* Test 55 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, identifier) &&
       str_is_equal(current_token.value, "blablabla")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 56 */
    fill_file(file_name, "[]a");
    stream = fopen(file_name, "r");

    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, ssb) &&
       str_is_equal(current_token.value, "[")) {
        report(0);
    }
    else {
        report(1);
    }

    /* Test 57 */
    current_token = get_next_word(stream);

    if(int_is_equal(current_token.type, esb) &&
       str_is_equal(current_token.value, "]")) {
        report(0);
    }
    else {
        report(1);
    }



    if(tests_failed == 0)
        std::cout <<  "\033[;32m" << "ALL TESTS PASSED" << "\033[0m" << std::endl;
    else
        std::cout << "\033[;31m" << tests_failed << " TEST(S) FAILED" << "\033[0m" << std::endl;



}
