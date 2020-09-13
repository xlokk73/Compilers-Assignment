#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include "transitions.h"
#include "tree.h"

extern token tok;
extern FILE* input_stream;

void set_stream(FILE* new_stream);

void advance();

bool parse_program();

AST* parse_statement();

AST* parse_block();

AST* parse_l_curly();

AST* parse_r_curly();

AST* parse_semicolon();

AST* parse_assignment();

AST* parse_rtrn_statement();

AST* parse_print_statement();

AST* parse_return();

AST* parse_print();

AST* parse_var_decl();

AST* parse_colon();

AST* parse_let();

AST* parse_identifier();

AST* parse_type();

AST* parse_colon();

AST* parse_let();

AST* parse_identifier();

AST* parse_auto();

AST* parse_equals();

AST* parse_expression(); 

AST* parse_rel_op();

AST* parse_simp_expression();

AST* parse_add_op();

AST* parse_mult_op();

AST* parse_term();

AST* parse_factor();

AST* parse_literal();

AST* parse_float_literal();

AST* parse_while_statement();

AST* parse_while();

AST* parse_l_par();

AST* parse_r_par();

AST* parse_if_statement();

AST* parse_if();

AST* parse_else();

AST* parse_for_statement();

AST* parse_for();

AST* parse_func_decl();
    
AST* parse_ff();

AST* parse_formal_params();
      
AST* parse_formal_param();

AST* parse_func_call();

AST* parse_actual_params();

AST* parse_sub_exp(); 

AST* parse_unary();

AST* parse_minus();

AST* parse_not();

AST* parse_comma();

AST* parse_boolean_literal();

AST* parse_integer_literal();

AST* parse_l_square();

AST* parse_r_square();

#endif
