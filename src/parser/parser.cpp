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
    current_token   = next_token;
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
                return parse_declaration_statement(); 
                    
            else if (current_token.value.compare("print") == 0)
                return parse_print_statement();

            else if (current_token.value.compare("if") == 0)
                return nullptr;//parse_if_statement();

            else if (current_token.value.compare("while") == 0)
                return nullptr;//parse_while_statement();

            else if (current_token.value.compare("return") == 0)
                return parse_return_statement();


        case scb:
            return nullptr;//parse_block();

        default:
            std::cout << "Error: invalid statement starting: " << current_token.value << std::endl;
            return nullptr;
    }
}

ASTDeclarationNode* Parser::parse_declaration_statement() {
    // Node attributes
    TYPE type;
    std::string id;
    ASTExpressionNode* expr;
    
    // Consume identifier
    advance();
    if (current_token.type != identifier) {
        std::cout << "Error: expecting identifier after 'let'" << std::endl;
        return nullptr;
    }

    id = current_token.value;

    advance();
    if (current_token.type != colon) {
        std::cout << "Error: expecting colon after identifier" << std::endl;
        return nullptr;
    }

    advance();
    type = parse_type(id); 

    advance();
    if (current_token.value.compare("=") != 0) {
        std::cout << "Error: expecting equals" << std::endl;
        return nullptr;
    }

    // Parse the right hand side
    expr = parse_expression();

    advance();
    if (current_token.type != s_colon) {
        std::cout << "Error: Expecting ';' after assignment" << std::endl;
        return nullptr;
    }

    return new ASTDeclarationNode(type, id, expr);
}

ASTPrintNode* Parser::parse_print_statement() {
    
    // Get expression to print
    ASTExpressionNode* expr = parse_expression();

    // consume ';' token
    advance();

    // Make sure ut's a ';'
    if (current_token.type != s_colon) { 
        std::cout << "Error: expected ';' after print statement" << std::endl;
        return nullptr;
    }

    return new ASTPrintNode(expr);
}

ASTExpressionNode* Parser::parse_expression() {
    ASTExpressionNode* simple_expr = parse_simple_expression();

    if (next_token.type == rel_op) {
        advance();
        return new ASTBinaryExpressionNode(current_token.value, simple_expr, parse_expression());
    }

    return simple_expr;
}

ASTExpressionNode* Parser::parse_simple_expression() {
    
    ASTExpressionNode* term = parse_term();

    if (next_token.type == add_op) {
        advance();
        return new ASTBinaryExpressionNode(current_token.value, term, parse_simple_expression());
    }

    return term;
}

ASTExpressionNode* Parser::parse_term() {
    
    ASTExpressionNode* factor = parse_factor();

    if (next_token.type == mult_op) {
        advance();
        return new ASTBinaryExpressionNode(current_token.value, factor, parse_term());
    }

    return factor;
}

ASTExpressionNode* Parser::parse_factor() {
    advance();

    switch(current_token.type) {
        
        // Literal Cases
        case number:
            return new ASTLiteralNode<int>(std::stoi(current_token.value));

        case float_num:
            return new ASTLiteralNode<float>(std::stof(current_token.value));

        case boolean:
            return new ASTLiteralNode<bool>(current_token.value == "true");

        case identifier:
            if (next_token.type == scb) {
                //return parse_array();
            }
            return new ASTIdentifierNode(current_token.value);

        // Subexpression case
        case srb: {
            ASTExpressionNode *sub_expr = parse_expression();
            advance();
            if (current_token.type != erb) {
                std::cout << "Error: expected ')' after expression" << std::endl;
                return nullptr;
            }

            return sub_expr;
        }

        case add_op:
            return new ASTUnaryExpressionNode(current_token.value, parse_expression());

        default:
            std::cout << "Error: expected expression" << std::endl;
            return nullptr;
    }
}

ASTReturnNode* Parser::parse_return_statement() {
    
    // Get expression to return
    ASTExpressionNode* expr = parse_expression();

    // Consume ';' token
    advance();

    // Make sure it's a ';'
    if (current_token.type != s_colon) {
        std::cout << "Error: Expected ';' after return statement" << std::endl;
        return nullptr;
    }
    
    return new ASTReturnNode(expr);
}

TYPE Parser::parse_type(std::string& identifier) {

    if (current_token.value.compare("int") == 0)
        return INT;

    else if (current_token.value.compare("float") == 0)
        return FLOAT;

    else if (current_token.value.compare("bool") == 0) 
        return BOOL;

    else if (current_token.value.compare("char") == 0)
        return CHAR;

    std::cout << "Error: Expexted type for " << identifier << std::endl;
}

