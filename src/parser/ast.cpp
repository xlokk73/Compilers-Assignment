#include "ast.h"
#include <iostream>
#include <utility>

// Program Node

ASTProgramNode::ASTProgramNode(std::vector<ASTStatementNode* statements) :
    statements(std::move(statements))
{}

// Statement Nodes

ASTDeclarationNode::ASTDeclarationNode(TYPE type, std::string identifier, ASTExpressionNode* expr) :
    type(type),
    identifier(std::move(identifier)),
    expr(expr)
{}

ASTAssignmentNode::ASTAssignmentNode(std::string identifier, ASTExpressionNode* expr) :
        identifier(std::move(identifier)),
        expr(expr)
{}

ASTPrintNode::ASTPrintNode(ASTExpressionNode* expr) :
        expr(expr)
{}

ASTReturnNode::ASTReturnNode(ASTExpressionNode* expr) :
        expr(expr)
{}

ASTBlockNode::ASTBlockNode(std::vector<ASTStatementNode*> statements) :
        statements(std::move(statements))
{}

ASTIfNode::ASTIfNode(ASTExpressionNode* condition, ASTBlockNode* if_block, ASTBlockNode* else_block) :
        condition(condition),
        if_block(if_block),
        else_block(else_block)
{}

ASTWhileNode::ASTWhileNode(ASTExpressionNode* condition, ASTBlockNode* block) :
        condition(condition),
        block(block)
{}

//Expression Nodes
ASTBinaryExpressionNode::ASTBinaryExpressionNode(std::string op, ASTExpressionNode* left, ASTExpressionNode* right) :
    op(std::move(op)),
    left(left),
    right(right)
{}

ASTIdentifierNode::ASTIdentifierNode(std::string identifier) :
    identifier(identifier)
{}

ASTUnaryExpressionNode::ASTUnaryExpressionNode(std::string unary_op, ASTExpressionNode* expr) :
    unary_op(std::move(unary_op)),
    expr(expr)
{}

