/*
 * @Author: Elendeer
 * @Date: 2020-06-05 08:21:21
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-05 20:35:05
 * @Description: file content
 */
#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <string>

namespace ESI {
using std::string;

enum TokenType {  // define enum type to record the type of a token.
    NONE,
    INTEGER,
    MUL,
    DIV,
    PLUS,
    MINUS,
    LPAREN,
    RPAREN,
    eEOF
};
const std::string TokenTypeString[] = {
    "NONE",
    "INTEGER",
    "MUL",
    "DIV", "PLUS",
    "MINUS", "LPAREN",
    "RPAREN", "EOF"
};
const char NOCHAR = '#';
const int NOVAL = -1;

string repr(int num);

class Token {
   private:
    TokenType m_type;
    int m_value;

   public:
    Token(TokenType type = NONE, int value = 0);
    Token(const Token& obj) = default;

    string str_repr();

    TokenType getType() const;
    int getVal() const;
};

}  // namespace ESI

#endif
