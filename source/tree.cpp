#include "tree.h"
#include <iostream>

struct node* make_node(token data, struct node* left, struct node* right) { 
  // Allocate memory for new node  
  struct node* node = (struct node*)malloc(sizeof(struct node)); 
  
  // Assign data to this node 
  node->data = data; 
  
  // Initialize left and right children as NULL 
  node->left = left; 
  node->right = right; 
  return(node); 
} 

void print_tree(struct node* tree) {
    std::cout << "type: " <<  get_type(tree->data.type) << std::endl;
    std::cout << "value: " << tree->data.value << std::endl;
    
    if ( tree->left != nullptr ) {
        std::cout << "printing " << get_type(tree->data.type) << "'s left child:\n";
        print_tree(tree->left);
    }

    if ( tree->right != nullptr ) {
        std::cout << "printing " << get_type(tree->data.type) << "'s right child:\n";
        print_tree(tree->right);
    }
}

void destroy_tree(struct node *tree) {
  if ( tree != nullptr ) {
      destroy_tree(tree->left);
      destroy_tree(tree->right);
      free(tree);
  }
}

void add_to_rightmost(AST* root, AST* left, AST* right) {
    if ( root == nullptr ) {
       root = right;
    }

    else if ( root->right != nullptr ) {
       add_to_rightmost(root->right, left, right); 
    }

    else {
        root->right = right;
        root->left = left;
    }
}
