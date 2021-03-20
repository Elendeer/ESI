/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-20 21:47:51
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-20 22:15:34
 * @Description  :
*********************************************/

#include <iostream>

#include "../inc/lexer.hpp"

using namespace std;
using namespace ESI;

int main() {
    string str;
    getline(cin, str);
    Lexer lexer(str);

    Token token = lexer.getNextToken();
    while (token.getType() != TokenType::eEOF) {
        token.print_str_repr();
        cout << endl;
        token = lexer.getNextToken();
    }

    return 0;
}
