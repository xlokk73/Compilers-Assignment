#include "parser.h"
#include <iostream>

FILE* input_stream = NULL;
token current_tok;

void Parser::set_stream(FILE* new_stream) { input_stream = new_stream; }
void Parser::advance() { current_tok = get_next_word(input_stream); }

void tell(std::string type) {
    std::cout << "PARSED: " << type << std::endl;
}

Parser(FILE* input_stream) : input_stream(input_stream) {
    current_token   = get_next_word(input_stream);
    next_token      = get_next_word(input_stream); 
}

void Parser::advance() { current_tok = get_next
