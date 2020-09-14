#include "ast.h"
#include <iostream>

ASTDeclerationNode::ASTDeclerationNode(TYPE type, std::string identifier, ASTExpressionNode* expr) :
    type(type),
    identifier(std::move(identifier)),
    expr(expr)
{}

ASTAssignmentNode::ASTAssignmentNode(std::string identifier, ASTExprNode *expr) :
        identifier(std::move(identifier)),
        expr(expr)
{}

ASTPrintNode::ASTPrintNode(ASTExprNode *expr) :
        expr(expr)
{}

ASTReturnNode::ASTReturnNode(ASTExprNode *expr) :
        expr(expr)
{}

ASTBlockNode::ASTBlockNode(std::vector<ASTStatementNode*> statements) :
        statements(std::move(statements))
{}

ASTIfNode::ASTIfNode(ASTExprNode* condition, ASTBlockNode *if_block, ASTBlockNode *else_block) :
        condition(condition),
        if_block(if_block),
        else_block(else_block)
{}

ASTWhileNode::ASTWhileNode(ASTExprNode *condition, ASTBlockNode *block) :
        condition(condition),
        block(block)
{}

//Expression Nodes
ASTBinaryExpressionNode::ASTBinaryExpressionNode(std::string op, ASTExpressionNode* left, ASTExpressionNode* right) :
    op(std::move(op),
    left(left),
    right(right)
{}

ASTIdentifierNode::ASTIdentifierNode(std::string identifier) :
    identifier(identifier)
{}

ASTUnaryExpressionNode::ASTUnaryExpressionNode(std::string unary_op, ASTExpressionNode *expr) :
    unary_op(std::move(unary_op)),
    expr(expr)
{}

