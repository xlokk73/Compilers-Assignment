#include <map>
#include <vecotr>
#include <stack>
#include "../parser/ast.h"
#include "../parser/parser.h"

class Scope {
public:
    bool declare(std::string, TYPE);
    void declare(std::string, TYPE, std::vector<TYPE>);

private:
    std::map<std::string, std::pair<parser::TYPE, unsigned int>> variable_symbol_table;
    
