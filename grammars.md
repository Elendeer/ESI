<!--
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-11-14 09:06:48
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-04-21 14:49:44
 * @Description  :
-->

# Grammars

```note

program : PROGRAM variable SEMI block DOT

block : declarations compound_statement

declarations : (VAR (variable_declaration SEMI)+)? procedure_declaration*

variable_declaration : ID (COMMA ID)* COLON type_spec

formal_parameter_list : formal_parameters
        | formal_parameters SEMI formal_parameter_list

formal_parameters : ID (COMMA ID)* COLON type_spec

procedure_declaration :
    PROCEDURE ID (LPAREN formal_parameter_list RPAREN)? SEMI block SEMI

type_spec : INTEGER | REAL

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
         | LPAREN expr RPAREN
         | variable

term : factor((MUL | INTEGER_DIV | FLOAT_DIV) factor)*

expr : term ((PLUS | MINUS) term)*

procedure_call_statement :
    ID LPAREN (expr(COMMA expr)*)? RPAREN

```
