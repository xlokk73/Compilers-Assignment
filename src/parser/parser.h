#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include "../lexer/transitions.h"
#include "../lexer/lexer.h"
#include "ast.h"

extern FILE* input_stream;

class Parser {

public:
    explicit Parser(FILE* input_stream);
    void advance();

    FILE* input_stream;
    Token current_token;
    Token next_token();
    
    // Statement nodes
    ASTStatementNode*       parse_statement();
    ASTDeclarationNode*     parse_declaration_statement();
    ASTAssignmentNode*      parse_assignment_statement();
    ASTPrintNode*           parse_print_statement();
    ASTReturnNode*          parse_return_statement();
    ASTBlockNode*           parse_block();
    ASTWhileNode*           parse_while_statement();

    // Expression Nodes
    ASTExpressionNode*      parse_expression();
    ASTExpressionNode*      parse_simp_expression();
    ASTExpressionNode*      parse_term();
    ASTExpressionNode*      parse_factor();

    // Parse Types
    TYPE parse_type(std::string&);

}
