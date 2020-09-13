#include "parser.h"
#include <iostream>

FILE* input_stream = NULL;
token current_tok;

void set_stream(FILE* new_stream) { input_stream = new_stream; }
void advance() { current_tok = get_next_word(input_stream); }

void tell(std::string type) {
    std::cout << "PARSED: " << type << std::endl;
}
