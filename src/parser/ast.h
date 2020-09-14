#ifndef AST_H
#define AST_H

#include "../lexer/transitions.h"
#include <string>
#include <vector>

enum TYPE {INT, REAL, BOOL, STRING};

// Abstract Nodes
class ASTNode {
};

class ASTStatementNode : public ASTNode {
};

class ASTExpressionNode : public ASTNode {
};

// Nodes
class ASTProgramNode :  public ASTNode {
public:
    explicit ASTProgramNode(std::vector<ASTStatementNode*>);
    std::vector<ASTStatementNode*> statements;
};

class ASTDeclarationNode : public ASTStatementNode {
public: 
    ASTDeclarationNode(TYPE, std::string, ASTExpressionNode*);
    TYPE type;
    std::string identifier;
    ASTExpressionNode *expr;
};

class ASTAssignmentNode : public ASTStatementNode {
public:
    ASTAssignmentNode(std::string, ASTExpressionNode*);
    std::string identifier;
    ASTExpressionNode *expr;
};

class ASTPrintNode : public ASTStatementNode {
public:
    explicit ASTPrintNode(ASTExpressionNode*);
    ASTExpressionNode *expr;
};

class ASTReturnNode : public ASTStatementNode {
public:
    explicit ASTReturnNode(ASTExpressionNode*);
    ASTExpressionNode *expr;
};

class ASTBlockNode : public ASTStatementNode {
public:
    ASTBlockNode(std::vector<ASTStatementNode*>);
    std::vector<ASTStatementNode*> statements;
};

class ASTIfNode : public ASTStatementNode {
public:
    ASTIfNode(ASTExpressionNode*, ASTBlockNode*, ASTBlockNode* = nullptr);
    ASTExpressionNode *condition;
    ASTBlockNode *if_block;
    ASTBlockNode *else_block;
};

class ASTWhileNode : public ASTStatementNode {
public:
    ASTWhileNode(ASTExpressionNode*, ASTBlockNode*);
    ASTExpressionNode *condition;
    ASTBlockNode *block;
};

// Expression Nodes
template <typename T>
class ASTLiteralNode : public ASTExpressionNode {
public:
    ASTLiteralNode(T val) : val(val){};
    T val;
};

class ASTBinaryExpressionNode : public ASTExpressionNode {
public:
    ASTBinaryExpressionNode(std::string, ASTExpressionNode*, ASTExpressionNode*);
    std::string op;
    ASTExpressionNode* left;
    ASTExpressionNode* right;
};

class ASTIdentifierNode : public ASTExpressionNode {
public:
    explicit ASTIdentifierNode(std::string);
    std::string identifier;
};

class ASTUnaryExpressionNode : public ASTExpressionNode {
public:
    ASTUnaryExpressionNode(std::string, ASTExpressionNode*);
    std::string unary_op;
    ASTExpressionNode *expr;
};

#endif
