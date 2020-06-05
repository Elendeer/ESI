/*
 * @Author: Elendeer
 * @Date: 2020-06-05 15:27:18
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-05 18:55:18
 * @Description: file content
 */

#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>

#include "token.hpp"

namespace ESI {
using std::string;

class Lexer {
   private:
    string m_text;
    int m_pos;  // index of m_text
    // Token m_current_token;
    char m_current_char;

   public:
    Lexer(string text);
    Lexer(const Lexer&) = default;

    void error();

    void advance();
    void skip_whitespace();
    int interger();

    Token get_next_token();
    // void eat(TokenType token_type);
    // int term();
    // int expr();
};

}  // namespace ESI

#endif
