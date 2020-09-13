#include "transitions.h"
#include <iostream>

std::string get_type(token_type e) {
    switch(e) {
        case invalid: return "invalid";
        case number: return "number";
        case float_num: return "float_num";
        case identifier: return "identifier";
        case keyword: return "keyword";
        case mult_op: return "mult_op";
        case add_op: return "add_op";
        case rel_op: return "rel_op";
        case var_type: return "var_type";
        case boolean: return "boolean";
        case automatic: return "automatic";
        case srb: return "srb";
        case erb: return "erb";
        case scb: return "scb";
        case ecb: return "ecb";
        case comma: return "comma";
        case colon: return "colon";
        case s_colon: return "s_colon";
        case comment: return "comment";
        case ssb: return "ssb";
        case esb: return "esb";

        case statement: return "statement";
        case rtrn_statement: return "rtrn_statement";
        case print_statement: return "print_statement";
        case while_statement: return "while_statement";
        case for_statement: return "for_statement";
        case expression: return "expression";
        case simp_expression: return "simp_expression";
        case var_decl: return "var_decl";
        case block: return "block";
        case if_head: return "if_head";
        case if_block: return "if_block";
        case for_head: return "for_head";
        case for_block: return "for_block";
        case for_extra: return "for_extra";
        case func_head: return "func_head";
        case func_block: return "func_block";
        case func_extra: return "func_extra";
        case formal_params: return "formal_params";
        case formal_param: return "formal_param";
        case func_call: return "func_call"; 
        case actual_params: return "actual_params";
        case sub_exp: return "sub_exp";
        case unary: return "unary"; 
        case array: return "array";
    }
}

/* Classifier table */
classifier char_cat(int ch) {
    if(ch > 47 && ch < 58) {
        // std::cout << "CASE: digit" << std::endl;
        return digit;
    }

    else if((ch > 64 && ch < 91) || (ch > 96 && ch < 123)) {
        // std::cout << "CASE: letter" << std::endl;
        return letter;
    }

    else if(ch == ' ') {
        // std::cout << "CASE: space" << std::endl;
        return space;
    }

    else if(ch == '\n') {
        // std::cout << "CASE: newline" << std::endl;
        return newline;
    }

    else if(ch == '.') {
        // std::cout << "CASE: dot" << std::endl;
        return dot;
    }

    else if(ch == '_') {
        // std::cout << "CASE: underscore" << std::endl;
        return underscore;
    }

    else if(ch == '*') {
        // std::cout << "CASE: mult_char" << std::endl;
        return mult_char;
    }

    else if(ch == '/') {
        // std::cout << "CASE: divide_char" << std::endl;
        return div_char;
    }

    else if(ch == '+' || ch == '-') {
        // std::cout << "CASE: add_char" << std::endl;
        return add_char;
    }

    else if(ch == '=') {
        // std::cout << "CASE: equals" << std::endl;
        return equals;
    }

    else if(ch == '>') {
        // std::cout << "CASE: greater_than" << std::endl;
        return greater_than;
    }

    else if(ch == '<') {
        // std::cout << "CASE: less_than" << std::endl;
        return less_than;
    }

    else if(ch == '(') {
        // std::cout << "CASE: srb_char" << std::endl;
        return srb_char;
    }

    else if(ch == ')') {
        // std::cout << "CASE: erb_char" << std::endl;
        return erb_char;
    }

    else if(ch == '{') {
        // std::cout << "CASE: scb_char" << std::endl;
        return scb_char;
    }

    else if(ch == '}') {
        // std::cout << "CASE: ecb_char" << std::endl;
        return ecb_char;
    }

    else if(ch == ',') {
        // std::cout << "CASE: comma_char" << std::endl;
        return comma_char;
    }

    else if(ch == ':') {
        // std::cout << "CASE: colon_char" << std::endl;
        return colon_char;
    }

    else if(ch == ';') {
        // std::cout << "CASE: s_colon_char" << std::endl;
        return s_colon_char;
    }
    else if(ch == '[') {
        // std::cout << "CASE: ssb_char" << std::endl;
        return ssb_char;
    }
    else if(ch == ']') {
        // std::cout << "CASE> esb_char" << std::endl;
        return esb_char;
    }

    else {
        return other;
    }
}

token_type keyword_type(std::string lexeme) {
    if(lexeme.compare("float") == 0 || lexeme.compare("int") == 0 || lexeme.compare("bool") == 0 || lexeme.compare("char") == 0)
        return var_type;

    else if(lexeme.compare("and") == 0)
        return mult_op;

    else if(lexeme.compare("or") == 0)
        return add_op;

    else if(lexeme.compare("true") == 0 || lexeme.compare("false") == 0)
        return boolean;

    else if(lexeme.compare("auto") == 0)
        return automatic;

    else if(lexeme.compare("var") == 0)
        return keyword;
    else if(lexeme.compare("return") == 0)
        return keyword;
    else if(lexeme.compare("if") == 0)
        return keyword;
    else if(lexeme.compare("print") == 0)
        return keyword;
    else if(lexeme.compare("let") == 0)
        return keyword;
    else if(lexeme.compare("else") == 0)
        return keyword;

    else
        return identifier;
    
}

/* Token type table */
token_type type(state* fin, std::string lexeme) {
    switch(*fin) {
    case S1:
        return number;
    case S3:
        return float_num;
    case S4:
        return keyword_type(lexeme);
    case S5:
        return mult_op;
    case S6:
        return add_op;
    case S7:
        return rel_op;
    case S8:
        return rel_op;
    case S9:
        return rel_op;
    case S10:
        return rel_op;
    case S10b:
        return rel_op;
    case S11:
        return srb;
    case S12:
        return erb;
    case S13: 
        return scb;
    case S14:
        return ecb;
    case S15:
        return comma;
    case S16:
        return colon;
    case S17:
        return s_colon;
    case S18:
        return mult_op;
    case S20:
        return comment;
    case S23:
        return comment;
    case S24:
        return ssb;
    case S25:
        return esb;
    default:
        return invalid;
    }
}

bool is_accepting(const state n) {
    for(int i = 0; i < total_accepting_states; ++i)
        if(n == SA[i])
            return true;

    return false;
}

