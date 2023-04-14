#include <iostream>
#include "../../inc/AST.hpp"

using namespace std;
using namespace ESI;

int main() {
    Token int_type_token(TokenType::INTEGER, (string)"INTEGER");
    cout << int_type_token.getStringRepr() << endl;
    Type int_type_node(int_type_token);
    cout << int_type_node.getVal() << endl << endl;

    Num num_start(Token(TokenType::INTEGER_CONST, 0));
    Num num_end(Token(TokenType::INTEGER_CONST, 10));

    AST * p = & int_type_node;
    AST * pn1 = & num_start;
    AST * pn2 = & num_end;
    Type array_type_node(
        Token(TokenType::ARRAY, (string)"ARRAY"),
        p,
        pn1,
        pn2
    );
    cout << array_type_node.getArrayTypeVal() << endl;
    cout << array_type_node.getArrayStart()->getToken().getStringRepr()
        << endl;
    cout << array_type_node.getArrayEnd()->getToken().getStringRepr()
        << endl;


    return 0;
}