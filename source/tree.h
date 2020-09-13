#ifndef TREE_H
#define TREE_H

#include "transitions.h"

typedef struct node { 
    token data; 
    struct node *left; 
    struct node *right; 
} AST; 

struct node* make_node(token data, struct node* left, struct node* right);

void print_tree(struct node* tree);

void destroy_tree(struct node* tree);

void add_to_rightmost(AST* root, AST* left, AST* right);

#endif
