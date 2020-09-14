#include "parser.h"
#include <iostream>

FILE* input_stream = NULL;
token current_tok;


void tell(std::string type) {
    std::cout << "PARSED: " << type << std::endl;
}

Parser::Parser(FILE* input_stream) : input_stream(input_stream) {
    current_token   = get_next_word(input_stream);
    next_token      = get_next_word(input_stream); 
}

void Parser::advance() { 
    current_token   = get_next_word(input_stream);
    next_token      = get_next_word(input_stream); 
}

ASTProgramNode* Parser::parse_program() {
    auto statements = new std::vector<ASTStatementNode*>;

    while(current_token.type != eof) {
        statements->push_back(parse_statement());
        advance();
    }
    
    return new ASTProgramNode(*statements);
}

ASTStatementNode* Parser::parse_statement() {
    
    switch(current_token.type) {

        case keyword:
    
            if (current_token.value.compare("let") == 0)
                return parse_decleration_statement(); 
                    
            else if (current_token.value.compare("print") == 0)
                return parse_print_statement();

            else if (current_token.value.compare("if") == 0)
                return parse_if_statement();

            else if (current_token.value.compare("while") == 0)
                return parse_while_statement();

            else if (current_token.value.compare("return") == 0)
                return parse_return_statement();


        case scb:
            return parse_block();

        default:
            std::cout << "Error: invalid statement starting: " << current_token.value << std::endl;
    }
}

ASTDeclerationNode* Parser::parse
