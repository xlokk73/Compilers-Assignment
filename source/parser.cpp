#include "parser.h"
#include "transitions.h"
#include "lexer.h"
#include <iostream>

FILE* input_stream = NULL;
token current_tok;

void set_stream(FILE* new_stream) { input_stream = new_stream; }
void advance() { current_tok = get_next_word(input_stream); }

void tell(std::string type) {
    std::cout << "PARSED: " << type << std::endl;
}

bool parse_program() {
    advance();
    AST* statement_node = nullptr;
    while (1) {
    tell("");
        statement_node = parse_statement();

        if ( statement_node != nullptr ) {
            std::cout << "Printing tree\n";
            print_tree(statement_node);
        }
        else {
            std::cout << "invalid input\n";
        }
        
        if ( statement_node == nullptr ) { return false; }
    }
    return true;
}

AST* parse_statement() {
    tell("statement");
    AST* rtrn_statement_node = parse_rtrn_statement();
    if ( rtrn_statement_node != nullptr ) {
        AST* semicolon_node = parse_semicolon();
        if ( semicolon_node != nullptr ) { 
            token new_tok;
            new_tok.type = statement;
            return make_node(new_tok, rtrn_statement_node, semicolon_node); 
        } 
        else { return nullptr; }
    }

    AST* print_statement_node = parse_print_statement();
    if ( print_statement_node != nullptr ) {
        AST* semicolon_node = parse_semicolon();
        if ( semicolon_node != nullptr ) {
            token new_tok;
            new_tok.type = statement;
            return make_node(new_tok, print_statement_node, semicolon_node);
        }
        else { return nullptr; }
    }

    AST* var_decl_node = parse_var_decl(); 
    if ( var_decl_node != nullptr ) {
        AST* semicolon_node = parse_semicolon();
        if ( semicolon_node != nullptr ) {
            token new_tok;
            new_tok.type = statement;
            return make_node(new_tok, var_decl_node, semicolon_node);
        }
        else { return nullptr; }
    }

    AST* assignment_node = parse_assignment();
    if ( assignment_node != nullptr ) {
        AST* semicolon_node = parse_semicolon();
        if ( semicolon_node != nullptr ) {
            token new_tok;
            new_tok.type = statement;
            return make_node(new_tok, assignment_node, semicolon_node);
        }
        else { return nullptr; }
    }

    AST* block_node = parse_block();
    if ( block_node != nullptr ) {
        token new_tok;
        new_tok.type = statement;
        return make_node(new_tok, block_node, nullptr);
    }

    AST* while_statement_node = parse_while_statement();
    if ( while_statement_node != nullptr ) {
        token new_tok;
        new_tok.type = statement;
        return make_node(new_tok, while_statement_node, nullptr);
    }

    AST* if_statement_node = parse_if_statement();
    if ( if_statement_node != nullptr ) {
        token new_tok;
        new_tok.type = statement;
        return make_node(new_tok, if_statement_node, nullptr);
    }

    AST* for_statement_node = parse_for_statement();
    if ( for_statement_node != nullptr ) {
        token new_tok;
        new_tok.type = statement;
        return make_node(new_tok, if_statement_node, nullptr);
    }


    AST* func_decl_node = parse_func_decl();
    if ( func_decl_node != nullptr ) { 
        AST* semicolon_node = parse_semicolon();
        if ( semicolon_node != nullptr ) {
            token new_tok;
            new_tok.type = statement;
            return make_node(new_tok, func_decl_node, semicolon_node);
        }
        else { return nullptr; }
    }


    else { return nullptr; }
}

AST* parse_func_decl() {
    tell("func_decl");
    AST* ff_node = parse_ff();
    if ( ff_node == nullptr )                   { return nullptr; }

    AST* identifier_node = parse_identifier();
    if ( identifier_node == nullptr )           { return nullptr; }

    AST* l_par_node = parse_l_par();
    if ( l_par_node == nullptr )                { return nullptr; }

    AST* formal_params_node = parse_formal_params();
    
    AST* r_par_node = parse_r_par();
    if ( r_par_node == nullptr )                { return nullptr; }

    AST* colon_node = parse_colon();
    if ( colon_node == nullptr )                { return nullptr; }

    AST* type_node = parse_type();
    if ( type_node == nullptr ) {
        type_node = parse_auto();
    }
    if ( type_node == nullptr )                 { return nullptr; }
    
    AST* block_node = parse_block();
    if ( block_node == nullptr )                { return nullptr; }

    token new_tok_0;
    new_tok_0.type = func_extra;
    AST* func_extra_node = make_node(new_tok_0, formal_params_node, type_node);
    
    token new_tok_1;
    new_tok_1.type = func_block;
    AST* func_block_node = make_node(new_tok_1, func_extra_node, block_node); 

    token new_tok_2;
    new_tok_2.type = func_head;
    return make_node(new_tok_2, identifier_node, func_block_node);
}

AST* parse_ff() {
    tell("ff_tok");
    token new_tok = current_tok;
    if ( current_tok.value.compare("ff") == 0 ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_formal_params() {
    tell("formal_parse");
    AST* formal_param_node = parse_formal_param();
    if ( formal_param_node == nullptr ) { return nullptr; }

    AST* comma_node = parse_comma();
    AST* temp_formal_param_node = parse_formal_param();
    while ( temp_formal_param_node != nullptr && comma_node != nullptr ) {
        add_to_rightmost(formal_param_node, nullptr, temp_formal_param_node);

        comma_node = parse_comma();
        if ( comma_node == nullptr ) {
            break;
        }
        temp_formal_param_node = parse_formal_param();
    }

    token new_token;
    new_token.type = formal_params;
    return make_node(new_token, formal_param_node, nullptr);
}
   
AST* parse_formal_param() {
    tell("formal_param");
    AST* identifier_node = parse_identifier();
    if ( identifier_node == nullptr )   { return nullptr; }
    
    AST* colon_node = parse_colon();
    if ( colon_node == nullptr )        { return nullptr; }

    AST* type_node = parse_type();
    if ( type_node == nullptr )         { return nullptr; }

    token new_token;
    new_token.type = formal_param;
    return make_node(new_token, identifier_node, type_node);
}

AST* parse_for_statement() {
    tell("for_statement");
    AST* for_node = parse_for();
    if ( for_node == nullptr )                  { return nullptr; }

    AST* l_par_node = parse_l_par();
    if ( l_par_node == nullptr )                { return nullptr; }

    AST* var_decl_node = parse_var_decl();

    AST* semicolon_0_node = parse_semicolon();
    if ( semicolon_0_node == nullptr )          { return nullptr; }

    AST* expression_node = parse_expression();
    if ( expression_node == nullptr )           { return nullptr; }

    AST* semicolon_1_node = parse_semicolon();
    if ( semicolon_1_node == nullptr )          { return nullptr; }

    AST* assignment_node = parse_assignment();

    AST* r_par_node = parse_r_par();
    if ( r_par_node == nullptr )                { return nullptr; }

    AST* block_node = parse_block();
    if ( block_node == nullptr )                { return nullptr; }

    token new_tok_0;
    new_tok_0.type = for_extra;
    AST* for_extra_node = make_node(new_tok_0, var_decl_node, assignment_node);

    token new_tok_1;
    new_tok_1.type = for_block;
    AST* block = make_node(new_tok_1, for_extra_node, block_node);

    token new_tok_2;
    new_tok_2.type = for_head;
    return make_node(new_tok_2, expression_node, block); 
}

AST* parse_for() {
    tell("for_tok");
    token new_tok = current_tok;
    if ( current_tok.value.compare("for") == 0 ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_if_statement() {
    tell("if_statement"); 
    AST* if_node = parse_if();
    if ( if_node == nullptr)                                            { return nullptr; }

    AST* l_par_node = parse_l_par();
    if ( l_par_node == nullptr)                                         { return nullptr; }

    AST* expression_node = parse_expression() ;
    if ( expression_node == nullptr )                                   { return nullptr; }

    AST* r_par_node = parse_r_par();
    if ( r_par_node == nullptr )                                        { return nullptr; }

    AST* block_node = parse_block();
    if ( block_node == nullptr )                                        { return nullptr; }

    AST* else_node = parse_else();
    AST* else_block_node = parse_block();

    if ( (else_node == nullptr && else_block_node != nullptr)
      || (else_node != nullptr && else_block_node == nullptr) )         { return nullptr; }


    AST* block = nullptr;
    token new_tok_0;
    new_tok_0.type = if_block;
    block = make_node(new_tok_0, block_node, else_block_node);

    token new_tok_1;
    new_tok_1.type = if_head;
    return make_node(new_tok_1, expression_node, block); 
}

AST* parse_if() {
    tell("if_tok");
    token new_tok = current_tok;
    if ( current_tok.value.compare("if") == 0 ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_else() {
    tell("else_tok");
    token new_tok = current_tok;
    if ( current_tok.value.compare("else") == 0 ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_while_statement() {
    tell("while statement");
    AST* while_node = parse_while(); 
    if ( while_node == nullptr )        { return nullptr; }

    AST* l_par_node = parse_l_par();
    if ( l_par_node == nullptr )        { return nullptr; }

    AST* expression_node = parse_expression();
    if ( expression_node == nullptr )   { return nullptr; }

    AST* r_par_node = parse_r_par();
    if ( r_par_node == nullptr )        { return nullptr; }

    AST* block_node = parse_block();
    if ( block_node == nullptr )        { return nullptr; }

    token new_tok;
    new_tok.type = while_statement;
    return make_node(new_tok, expression_node, block_node);
}

AST* parse_while() {
    tell("while");
    token new_tok = current_tok;
    if ( current_tok.value.compare("while") == 0 ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_l_par() {
    tell("l_par");
    token new_tok = current_tok;
    if ( current_tok.type == srb ) { advance(); return make_node(current_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_r_par() {
    tell("r_par");
    token new_tok = current_tok;
    if ( current_tok.type == erb ) { advance(); return make_node(current_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_block() {
    tell("block");
    AST* l_curly_node = parse_l_curly();
    if ( l_curly_node == nullptr )      { return nullptr; }
    AST* statement_node = parse_statement();
    if ( statement_node == nullptr)     { return nullptr; }
    AST* r_curly_node = parse_r_curly();
    if ( r_curly_node == nullptr)       { return nullptr; }

    token new_tok;
    new_tok.type = block;
    return make_node(new_tok, statement_node, nullptr);
}

AST* parse_l_curly() {
    tell("l_curly");
    token new_tok = current_tok;
    if ( current_tok.type == scb ) { advance(); return make_node(current_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_r_curly() {
    tell("r_curly");
    token new_tok = current_tok;
    if ( current_tok.type == ecb ) { advance(); return make_node(current_tok, nullptr, nullptr); }
    else { return nullptr; }
}


AST* parse_semicolon() {
    tell("semicolon");
    token new_tok = current_tok;
    if ( current_tok.type == s_colon ) { advance(); return make_node(current_tok, nullptr, nullptr); }
    else { return nullptr; }
}
    
AST* parse_assignment() {
    AST* identifier_node = parse_identifier();
    if ( identifier_node == nullptr )   { return nullptr; }
    AST* equals_node = parse_equals();
    if ( equals_node == nullptr )       { return nullptr; }
    AST* expression_node = parse_expression();
    if ( expression_node == nullptr )   { return nullptr; }

    return make_node(equals_node->data, identifier_node, expression_node);
}
    
AST* parse_rtrn_statement() {
    tell("rtrn_stmnt");
    AST* rtrn_node = parse_return(); 
    if ( rtrn_node == nullptr ) { 
        return nullptr;
    }

    AST* expression_node = parse_expression();
    if ( expression_node == nullptr ) { 
        return nullptr; 
    } 

    token new_tok;
    new_tok.type = rtrn_statement;
    return make_node(new_tok, rtrn_node, expression_node);
}

AST* parse_print_statement() {
    tell("print_statement");
    AST* print_node = parse_print();
    if ( print_node == nullptr ) {
        return nullptr;
    }

    AST* expression_node = parse_expression();
    if ( expression_node == nullptr ) {
        return nullptr;
    }

    token new_tok;
    new_tok.type = print_statement;
    return make_node(new_tok, print_node, expression_node);
}

AST* parse_var_decl() {
    AST* let_node = parse_let();
    if ( let_node == nullptr )          { return nullptr; } 
    AST* identifier_node = parse_identifier();
    if ( identifier_node == nullptr )   { return nullptr; } 
    AST* colon_node = parse_colon();
    if ( colon_node == nullptr )        { return nullptr; }

    AST* type_node = parse_type();

    if ( type_node == nullptr ) {
        type_node = parse_auto();
    }

    if ( type_node == nullptr )         { return nullptr; }
    
    AST* equals_node = parse_equals();
    if ( equals_node == nullptr )       { return nullptr; }
    AST* expression_node = parse_expression();
    if ( expression_node == nullptr )   { return nullptr; }

    token new_tok;
    new_tok.type = var_decl;
    return make_node(type_node->data, identifier_node, expression_node);
}


AST* parse_colon() {
    tell("colon");
    token new_tok = current_tok;
    if ( current_tok.type == colon ) { advance(); return make_node(current_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_let() {
    tell("let_tok");
    token new_tok = current_tok;
    if ( current_tok.value.compare("let") == 0 ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_identifier() {
    tell("identifier");
    token new_tok = current_tok;
    if ( current_tok.type == identifier) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_array() {
    tell("array");
    AST* identifier_node = parse_identifier();
    if ( identifier_node == nullptr )   { return nullptr; }

    AST* l_square_node = parse_l_square();
    if ( l_square_node == nullptr )     { return nullptr; }

    AST* int_node = parse_integer_literal();

    AST* r_square_node = parse_r_square();
    if ( r_square_node == nullptr )     { return nullptr; }

    token new_token;
    new_token.type = array;
    return make_node(new_token, identifier_node, int_node);
}

AST* parse_l_square() {
    tell("l_square");
    token new_tok = current_tok;
    if ( current_tok.type == ssb ) { advance(); return make_node(current_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_r_square() {
    tell("r_square");
    token new_tok = current_tok;
    if ( current_tok.type == esb ) { advance(); return make_node(current_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_type() {
    tell("type");
    token new_tok = current_tok;
    if ( current_tok.value.compare("float") == 0 
      || current_tok.value.compare("bool") == 0
      || current_tok.value.compare("int") == 0
      || current_tok.value.compare("char") == 0) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_auto() {
    tell("auto");
    token new_tok = current_tok;
    if ( current_tok.value.compare("auto") == 0 ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_equals() {
    tell("equals");
    token new_tok = current_tok;
    if ( current_tok.value.compare("=") == 0 ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_return() {
    tell("rtrn_tok");
    token new_tok = current_tok;
    if ( current_tok.value.compare("return") == 0 ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_print() {
    tell("print_tok");
    token new_tok = current_tok;
    if ( current_tok.value.compare("print") == 0 ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_expression() {
    tell("exp");
    AST* simp_expression_node_l = parse_simp_expression();
    if ( simp_expression_node_l == nullptr ) { return nullptr; }

    AST* rel_op_node                    = nullptr;
    AST* simp_expression_node_r         = nullptr;
    AST* temp_rel_op_node               = nullptr;
    AST* temp_simp_expression_node_r    = nullptr;
 
    for(int i=0;; ++i) {
        temp_rel_op_node = parse_rel_op();
        if ( temp_rel_op_node == nullptr )               { break; }

        temp_simp_expression_node_r = parse_simp_expression();
        if ( temp_simp_expression_node_r == nullptr )    { return nullptr; }

        if ( i==0 ) {
            rel_op_node = temp_rel_op_node;
        }

        add_to_rightmost(simp_expression_node_r, temp_rel_op_node, temp_simp_expression_node_r);  
    }

    if ( rel_op_node == nullptr ) {
        return simp_expression_node_l;
    }

    return make_node(rel_op_node->data, simp_expression_node_l, simp_expression_node_r);
}

AST* parse_rel_op() {
    tell("rel");
    token new_tok = current_tok;
    if ( current_tok.type == rel_op ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_simp_expression() {
    tell("simp");
    AST* term_node_l = parse_term();
    if ( term_node_l == nullptr )                { return nullptr; }

    AST* add_op_node        = nullptr;
    AST* term_node_r        = nullptr;
    AST* temp_add_op_node   = nullptr;
    AST* temp_term_node_r   = nullptr;

    for(int i=0;; ++i) {
        temp_add_op_node = parse_add_op();
        if ( temp_add_op_node == nullptr )            { break; }

        temp_term_node_r = parse_term(); 
        if ( temp_term_node_r == nullptr )            { return nullptr; }

        if ( i==0 ) {
            add_op_node = temp_add_op_node;
        }
        add_to_rightmost(term_node_r, temp_add_op_node, temp_term_node_r);
    }

    if ( add_op_node == nullptr ) {
        return term_node_l; 
    }

    return make_node(add_op_node->data, term_node_l, term_node_r);
}

AST* parse_add_op() {
    tell("add");
    token new_tok = current_tok;
    if ( current_tok.type == add_op ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_term() {
    tell("term");
    AST* factor_node_l = parse_factor();
    if ( factor_node_l == nullptr ) { return nullptr; }

    AST* mult_op_node           = nullptr;
    AST* factor_node_r          = nullptr;
    AST* temp_mult_op_node      = nullptr;
    AST* temp_factor_node_r     = nullptr;

    for(int i=0;; ++i) {
        temp_mult_op_node = parse_mult_op();
        if ( temp_mult_op_node == nullptr )   { break; }

        temp_factor_node_r = parse_factor();
        if ( temp_factor_node_r == nullptr ) { return nullptr; }

        if ( i==0 ) {
            mult_op_node = temp_mult_op_node;
        }
        add_to_rightmost(factor_node_r, temp_mult_op_node, temp_factor_node_r);
    }
    if ( mult_op_node == nullptr ) {
        return factor_node_l;
    }

    return make_node(mult_op_node->data, factor_node_l, factor_node_r);
}

AST* parse_mult_op() {
    tell("mult");
    token new_tok = current_tok;
    if ( current_tok.type == mult_op ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_factor() { 
    tell("factor");
    AST* literal_node = parse_literal();
    if ( literal_node != nullptr )          { return literal_node; }

    AST* identifier_node = parse_identifier();
    if ( identifier_node != nullptr )       { return identifier_node; }

    AST* func_call_node = parse_func_call();
    if ( func_call_node != nullptr )        { return func_call_node; }

    AST* sub_exp_node = parse_sub_exp();
    if ( sub_exp_node != nullptr )          { return sub_exp_node; }

    AST* unary_node = parse_unary(); 
    if (unary_node != nullptr )             { return unary_node; }

    return nullptr;
}

AST* parse_func_call() {
    tell("func_call");
    AST* identifier_node = parse_identifier();
    if ( identifier_node == nullptr )       { return nullptr; }

    AST* l_par_node = parse_l_par();
    if ( l_par_node == nullptr )            { return nullptr; }

    AST* actual_params_node = parse_actual_params();

    AST* r_par_node = parse_r_par();
    if ( r_par_node == nullptr )            { return nullptr; }

    token new_token;
    new_token.type = func_call;
    return make_node(new_token, identifier_node, actual_params_node);
}

AST* parse_actual_params() {
    tell("actual_params");
    AST* expression_node = parse_expression();
    if ( expression_node == nullptr ) { return nullptr; }

    AST* comma_node = parse_comma();
    AST* temp_expression_node = parse_expression();
    while ( temp_expression_node != nullptr  && comma_node != nullptr) {
        add_to_rightmost(expression_node, nullptr, temp_expression_node);
        
        comma_node = parse_comma();
        if ( comma_node == nullptr) {
            break;
        }
        temp_expression_node = parse_expression();
    }

    token new_token;
    new_token.type = actual_params;
    return make_node(new_token, expression_node, nullptr);
}

AST* parse_sub_exp() { 
    tell("sub_exp");
    AST* l_par_node = parse_l_par();
    if ( l_par_node == nullptr )        { return nullptr; }
    
    AST* expression_node = parse_expression();
    if ( expression_node == nullptr )   { return nullptr; }

    AST* r_par_node = parse_r_par();
    if ( r_par_node == nullptr )        { return nullptr; }

    token new_token;
    new_token.type = sub_exp;
    return make_node(new_token, expression_node, nullptr);
}

AST* parse_unary() {
    tell("unary");
    AST* minus_node = parse_minus();
    if ( minus_node == nullptr ) {
        minus_node = parse_not();
    }
    if ( minus_node == nullptr )        { return nullptr; }

    AST* expression_node = parse_expression();
    if ( expression_node == nullptr )   { return nullptr; }

    token new_token;
    new_token.type = unary;
    return make_node(new_token, minus_node, expression_node);
}

AST* parse_minus() {
    tell("minus");
    token new_tok = current_tok;
    if ( current_tok.value.compare("-") == 0 ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_not() {
    tell("not");
    token new_tok = current_tok;
    if ( current_tok.value.compare("not") == 0 ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_comma() {
    tell("comma");
    token new_tok = current_tok;
    if ( current_tok.value.compare(",") == 0 ) { advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_literal() {
    tell("lit");
    AST* float_literal_node = parse_float_literal();
    if ( float_literal_node != nullptr )    { return float_literal_node; }

    AST* integer_literal_node = parse_integer_literal();
    if ( integer_literal_node != nullptr )  { return integer_literal_node; }

    AST* boolean_literal_node = parse_boolean_literal();
    if ( boolean_literal_node != nullptr )  { return boolean_literal_node; }

    AST* array_node = parse_array();
    if ( array_node != nullptr )            { return array_node; }
    
    return nullptr;
}

AST* parse_float_literal() { 
    tell("float");
    token new_tok = current_tok;
    if ( current_tok.type == float_num ) { ; advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_integer_literal() { 
    tell("integer");
    token new_tok = current_tok;
    if ( current_tok.type == number ) { ; advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}

AST* parse_boolean_literal() { 
    tell("boolean");
    token new_tok = current_tok;
    if ( current_tok.type == boolean ) { ; advance(); return make_node(new_tok, nullptr, nullptr); }
    else { return nullptr; }
}


