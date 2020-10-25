/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 15:27:18
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-09-28 21:51:57
* @Description  :
*********************************************/

#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>
#include <vector>

#include "token.hpp"

namespace ESI {
using std::string;
using std::vector;

/*********************************************
* enum types, reflections & constants
*********************************************/

enum class ReservedKeywords {
    BEGIN,
    END
};
const vector<string> reservedKeywordsString{
    "BEGIN",
    "END"};
const vector<Token> reservedKeywordsToken{
    Token(TokenType::BEGIN, "BEGIN"),
    Token(TokenType::END, "END")};

/*********************************************
* classes & functions
*********************************************/

class Lexer {
private:
    string m_text;
    int m_pos; // index of m_text
    // Token m_current_token;
    char m_current_char;

    Token id();

public:
    Lexer(string text);
    Lexer(const Lexer &) = default;

    void error();

    char peek();
    void advance();
    void skip_whitespace();
    int interger();

    Token get_next_token();
    // void eat(TokenType token_type);
    // int term();
    // int expr();
};

} // namespace ESI

#endif
