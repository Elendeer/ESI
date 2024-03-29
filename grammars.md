<!--
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-11-14 09:06:48
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2023-04-14 18:32:43
 * @Description  :
-->

# Grammars

- __+__ : appear once or more
- __*__ : appear zero or more times
- __?__ : appear zero or one time

```note

program : PROGRAM variable SEMI block DOT

block : declarations compound_statement

declarations : (VAR (variable_declaration SEMI)+)?
    (procedure_declaration | function_declaration)*

variable_declaration : ID (COMMA ID)* COLON type_spec

formal_parameter_list : formal_parameters
        | formal_parameters SEMI formal_parameter_list

formal_parameters : ID (COMMA ID)* COLON type_spec

type_spec : INTEGER | REAL | STRING | BOOLEAN | array_type

array_type :  ARRAY LSQUARE type_spec  RSQUARE
                OF INTEGER_CONST DOT DOT INTEGER_CONST

compound_statement : BEGIN statement_list END

statement_list : statement
               | statement SEMI statement_list

statement : compound_statement
         | assignment_statement
         | procedure_call_statement
         | read_statement
         | write_statement
         | if_statement
         | while_statement
         | empty

assignment_statement : variable ASSIGN logical_expr

variable : ID

factor : PLUS factor
         | MINUS factor
         | NOT factor
         | INTEGER_CONST
         | REAL_CONST
         | STRING
         | TRUE
         | FALSE
         | LPAREN logical_expr RPAREN
         | variable
         | function_call

term : factor((MUL | INTEGER_DIV | FLOAT_DIV) factor)*

expr : term ((PLUS | MINUS) term)*

procedure_declaration :
    PROCEDURE ID (LPAREN formal_parameter_list RPAREN)? SEMI block SEMI

procedure_call_statement :
    ID LPAREN (logical_expr(COMMA logical_expr)*)? RPAREN

function_declaration :
    FUNCTION ID (LPAREN formal_parameter_list RPAREN)?
    COLON type_spec SEMI block SEMI

function_call :
    ID LPAREN (logical_expr(COMMA logical_expr)*)? RPAREN

read_statement :
    READ LPAREN ID (COMMA ID)* RPAREN

write_statement :
    (WRITE | WRITELN) LPAREN logical_expr RPAREN

relational_expr : expr ((EQUAL | NOT_EQUAL
                    | LESS_THAN | LESS_THAN_OR_EQUAL_TO
                    | GREATER_THAN | GREATER_THAN_OR_EQUAL_TO) expr)?

logical_expr :
    relational_expr ((AND | OR | XOR) relational_expr)*

if_statement :
    IF LPAREN logical_expr RPAREN THEN
    (statement | compound_statement)
    (ELSE ((statement | block) | if_statement))?

while_statement :
    WHILE LPAREN logical_xepr RPAREN DO
    (statement | compound_statement)
```
