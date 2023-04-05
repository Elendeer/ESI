#include <iostream>
#include <string>

#include "../../inc/lexer.hpp"

int main() {
    using namespace std;
    using namespace ESI;

    string input;
    cout << "input a string, this test will try to break it down to tokens." << endl;

    getline(cin, input);

    Lexer lexer(input);

    Token token = lexer.getNextToken();
    while (token.getType() != TokenType::eEOF) {
        cout << token.getStringRepr() << endl;
        token = lexer.getNextToken();
    }

    return 0;
}