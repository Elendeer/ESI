<!--
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-11-14 09:06:48
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-05-08 18:16:17
 * @Description  :
-->

# Grammars

```note

program : PROGRAM variable SEMI block DOT

block : declarations compound_statement

declarations : (VAR (variable_declaration SEMI)+)?
    (procedure_declaration | function_declaration)*

variable_declaration : ID (COMMA ID)* COLON type_spec

formal_parameter_list : formal_parameters
        | formal_parameters SEMI formal_parameter_list

formal_parameters : ID (COMMA ID)* COLON type_spec

type_spec : INTEGER | REAL | STRING | BOOLEAN

compound_statement : BEGIN statement_list END

statement_list : statement
               | statement SEMI statement_list

statement : compound_statement
         | assignment_statement
         | procedure_call_statement
         | empty

assignment_statement : variable ASSIGN expr

variable : ID

factor : PLUS factor
         | MINUS factor
         | INTEGER_CONST
         | REAL_CONST
         | STRING
         | TRUE
         | FALSE
         | LPAREN expr RPAREN
         | variable
         | function_call

term : factor((MUL | INTEGER_DIV | FLOAT_DIV) factor)*

expr : term ((PLUS | MINUS) term)*

procedure_declaration :
    PROCEDURE ID (LPAREN formal_parameter_list RPAREN)? SEMI block SEMI

procedure_call_statement :
    ID LPAREN (expr(COMMA expr)*)? RPAREN

function_declaration :
    FUNCTION ID (LPAREN formal_parameter_list RPAREN)?
    COLON type_spec SEMI block SEMI

function_call :
    ID LPAREN (expr(COMMA expr)*)? RPAREN

```
