#ifndef AST_H
#define AST_H

#include "../lexer/transitions.h"

enum TYPE {INT, REAL, BOOL, STRING};

// Abstract Nodes
class ASTNode {
}

class ASTStatementNode : public ASTNode {
}

class ASTExpressionNode : public ASTNode {
}

// Nodes
class ASTProgramNode :  public ASTNode {
public:
    explicit ASTProgrameNode(std::vector<ASTStatementNode*>;
}

class ASTDeclerationNode : public ASTStatementNode {
public: 
    ASTDeclerationNode(TYPE, std::string, ASTExpressionNode*);
    TYPE type:
    std::string identifier;
    ASTExprNode *expr;
}

class ASTAssignmentNode : public ASTStatementNode {
public:
    ASTAssignmentNode(std::string, ASTExpressionNode);
    std::string identifier;
    ASTExpressionNode *expr;
}

class ASTPrintNode : public AstStatementNode {
public:
    explicit ASTPrintNode(ASTExprNode*);
    ASTExprNode *expr;
}

class ASTReturnNode : public ASTStatementNode {
public:
    explicit ASTReturnNode(ASTExpressionNode*);
    ASTExpressionNode *expr;
}

class ASTBlockNode : public ASTStatementNode {
public:
    explicit ASTBlock(std::vector<ASTStatementNode*>);
    std::vector<ASTStatementNode*> statement;
};

class ASTIfNode : public ASTStatementNode {
public:
    ASTIfNode(AASTExprNode*, ASTBlockNode*, ASTBlockNode* = nullptr);
    ASTExpressionNode *condition;
    ASTBlockNode *if_block;
    ASTBlockNode *else_block;
}

class ASTWhileNode(ASTExpressionNode*, ASTBlockNode*);
public:
    ASTWhileNode(ASTExpressionNode*, ASTBlockNode*);
    ASTExpressionNode *condition;
    ASTBlockNode *block;
}

// Expression Nodes
template <typename T>
class ASTLiteralNode : public ASTExpressionNode {
public:
    ASTLiteralNode(T val) : val(val){};
    T val;
}

class ASTBinaryExpressionNode : public ASTExpressionNode {
public:
    ASTBinaryExpressionNode(std::string, ASTExpressionNode*, ASTExpressionNode);
    std::string op;
    ASTExpressionNode *left;
    ASTExpressionNode *right;
}

class ASTIdentifierNode : public ASTExpresionNode {
public:
    explicit ASTIdentifierNode(std::string);
    std::string identifier;
};

class ASTUnaryExpressionNode : public ASTExpressionNode {
public:
    ASTUnaryExpressionNode(std::string, ASTExprNode*);
    std::string unary_op;
    ASTExprNode *expr;
};

#endif
