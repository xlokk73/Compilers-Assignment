#include "semantic_analysis.h"

void Scope::already_declared(std::string identifier) {
    return variable_symbol_table.find(identifier) != variable_symbol_table.end();
}

void Scope::declare(std::string identifier, TYPE type) {
    variable_symbol_table[identifier] = type;

TYPE Scope::type(std::string identifier) {
    if (already_declared(identifier) 
        return variable_symbol_table[identifier];
    
    std::cout << "Error during semantic analysis" << std::endl;
}
