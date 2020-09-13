#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include "../lexer/transitions.h"
#include "../lexer/lexer.h"
#include "ast.h"

:x
extern FILE* input_stream;

void set_stream(FILE* new_stream);

void advance();
