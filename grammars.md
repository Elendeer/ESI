<!--
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-11-14 09:06:48
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-11-14 09:12:28
 * @Description  :
-->

# Grammars

```note

program : compound_statement DOT

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
         | INTEGER
         | LPAREN expr RPAREN
         | variable

term : factor((MUL | DIV) factor)*

expr : term ((PLUS | MINUS) term)*

```
