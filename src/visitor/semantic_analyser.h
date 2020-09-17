#include <map>
#include <vecotr>
#include <stack>
#include <utility>
#include <iostream>
#include "../parser/ast.h"
#include "../parser/parser.h"

class Scope {
public:
    bool already_declared(std::string);
    void declare(std::string, TYPE);
    TYPE type(std::string);

private:
    std::map<std::string, std::pair<parser::TYPE, unsigned int>> variable_symbol_table;
    
}
       
