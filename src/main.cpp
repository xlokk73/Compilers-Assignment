#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "lexer/transitions.h"
#include "lexer/lexer.h"
#include "test.h"
#include "parser/parser.h"

#define CMD_SIZE 100

int main(const int argc, const char* argv[]) {
    std::cout << "Hello, World!" << std::endl;
  
    if(argc != 2) {
        std::cout << "Error: invalid number of arguments" << std::endl;
        return -1;
    }

    if (strcmp(argv[1], "test_lexer") == 0) {
        test_lexer();
        return 0;
    }

    if (strcmp(argv[1], "test_tree") == 0) {
        return 0;
    }

    FILE* stream = fopen (argv[1], "r");
    if(stream == nullptr) {
        std::cout << "Error: file does not exist" << std::endl;
        return 0;
    }

    set_stream(stream);
    parse_program();

    return 0;
}
