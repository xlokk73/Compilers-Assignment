#include "lexer.h"
#include "transitions.h"
#include <stack>
#include <string>
#include <iostream>

template <typename T>
void clear(std::stack<T> stack) {
    while(!stack.empty())
        stack.pop();
}


token get_next_word(FILE* stream) {
    int ch;

    state current_state = S0;

    std::string lexeme = "";

    std::stack<state> stack;
    clear(stack);
    stack.push(BAD);

    classifier cat = other;

    //std::cout << "************************" << std::endl;
    while (current_state != SE) {
        //std::cout << "LOOPING" << std::endl;
        ch = getc(stream);
        //std::cout << "CHAR CODE: " << ch << std::endl;

        if( current_state != S0 || (char_cat(ch) != space && char_cat(ch) != newline) )
         
            lexeme = lexeme + (char)ch;

        //std::cout << "CH: " << (char)ch << std::endl;
        //std::cout << "LEXEME: " << lexeme << std::endl;

        if (is_accepting(current_state))
            clear(stack);
        
        stack.push(current_state);
        cat = char_cat(ch);
        //std::cout << "CAT : " << cat << std::endl;
        current_state = (state)transitions[current_state][cat];

        //std::cout << "CURRENT STATE: " << current_state << std::endl;
    }


    while (!is_accepting(current_state) && current_state != BAD) {
        current_state = stack.top();
        stack.pop();
        lexeme.pop_back();
        ungetc(ch, stream);
        //std::cout << "STATE: " << current_state << std::endl;
    }

    //std::cout << "FINAL STATE: " << current_state << std::endl;
    //std::cout << "FINAL LEXEME: " << lexeme << std::endl;

    token new_token;
    if (is_accepting(current_state)) {
        // std::cout << "(state before): " << current_state << std::endl;
        new_token.type = type(&current_state, lexeme);
        // std::cout << "(state after): " << current_state << std::endl;
        new_token.value = lexeme;
        return new_token;
    }    
        
    else {
        new_token.type = invalid;
        return new_token;
    }
}        

