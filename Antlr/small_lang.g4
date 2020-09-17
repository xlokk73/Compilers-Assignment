grammar small_lang;

Program 
    : (Statement)* 
    ;

Block
    : '{' Statement* '}' ;

Statement
    : VariableDecl ';'
    | Assignment ';'
    | PrintStatement ';'
    | IfStatement 
    | ForStatement 
    | WhileStatement
    | RtrnStatement ';'
    | FuncDecl
    | Block
    ;

FuncDecl
    : 'ff' Identifier '(' ?FormalParams ')' ':' ( Type | Auto ) Block ;

FormalParams
    : FormalParam
    ( ',' FormalParam )* 
    ;

FormalParam
    : Identifier ':' Type ; 

WhileStatement
    : 'while' '(' Expression ')' Block ; 

ForStatement
    : 'for' '(' ?VariableDecl ';' Expression ';' ?Assignment ';' Block ;

IfStatement 
    : 'if' '(' Expression ')' Block ?( 'else' Block ) ;

RtrnStatement 
    : 'return' Expression ;

PrintStatement
    : 'print' Expression ;

VariableDecl 
    : 'let' Identifier ':' ( Type | Auto ) '=' Expression ;

Assignment 
    : Identifier '=' Expression ;

Expression
    : SimpleExpression ( RelationalOp SimpleExpression )* ;

SimpleExpression
    : Term ( AdditiveOp Term )* ;

Term
    : Factor ( MultiplicativeOp Factor )* ;

Factor 
    : Literal
    | Identifier
    | FunctionCall
    | SubExpression
    | Unary
    ;

Unary 
    : ( '-' | 'not' ) Expression ;

SubExpression
    : '(' Expression ')' ;

FunctionCall 
    : Identifier '(' ?ActualParams ')' ;

ActualParams
    : Expression ( ',' Expression )* ;

RelationalOp 
    : '<' | '>' | '==' | '<=' | '>=' ;

AdditiveOp 
    : '+' | '-' | 'or' ;

MultiplicativeOp 
    : '*' | '/' | 'and' ;

Identifier 
    : ( '_' | Letter ) ( '_' | Letter | Digit )* ;

Literal
    : BooleanLiteral
    | IntegerLiteral
    | FloatLiteral
    ;

FloatLiteral 
    : Digit Digit* '.' Digit Digit* ;

IntegerLiteral
    : Digit Digit* ;

BooleanLiteral
    : 'true' | 'false' ;

Auto 
    : 'auto' ;

Type 
    : 'float' | 'int' | 'bool' ;

Digit
    : 0..9 ; 

Letter 
    : 'A'..;Z' | 'a'..'z' ;
