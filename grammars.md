<!--
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-11-14 09:06:48
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-24 16:54:08
 * @Description  :
-->

# Grammars

```note

program : PROGRAM variable SEMI block DOT

block : declarations compound_statement

declarations : (VAR (variable_declaration SEMI)+)*
            | (PROCEDURE ID (LPAREN formal_parameter_list RPAREN)? SEMI block SEMI)*
            | empty

formal_parameter_list : formal_parameters
        | formal_parameters SEMI formal_parameter_list

formal_parameters : ID (COMMA ID)* COLON type_spec

variable_declaration : ID (COMMA ID)* COLON type_spec

type_spec : INTEGER | REAL

compound_statement : BEGIN statement_list END

statement_list : statement
               | statement SEMI statement_list

statement : compound_statement
         | assignment_statement
         | empty

assignment_statement : variable ASSIGN expr

variable : ID

factor : PLUS factor
         | MINUS factor
         | INTEGER_CONST
         | REAL_CONST
         | LPAREN expr RPAREN
         | variable

term : factor((MUL | INTEGER_DIV | FLOAT_DIV) factor)*

expr : term ((PLUS | MINUS) term)*

```
