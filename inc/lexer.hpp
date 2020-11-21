/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 15:27:18
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-11-21 10:01:45
 * @Description  :
*********************************************/

#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>
#include <vector>
#include <unordered_map>

#include "token.hpp"

namespace ESI {
using std::string;
using std::vector;

/*********************************************
* enum types, reflections & constants
*********************************************/

const std::unordered_map<string, Token>reservedKeywords {
    {"PROGRAM", Token(TokenType::PROGRAM, "END")},
    {"VAR", Token(TokenType::VAR, "VAR")},
    {"INTEGER", Token(TokenType::INTEGER, "INTEGER")},
    {"REAL", Token(TokenType::REAL, "REAL")},
    {"INTEGER_DIV", Token(TokenType::INTEGER_DIV, "DIV")},
    {"BEGIN", Token(TokenType::BEGIN, "BEGIN")},
    {"END", Token(TokenType::END, "END")}
};


/*********************************************
* classes & functions
*********************************************/

class Lexer {
private:
    string m_text;

    // index of m_text
    int m_pos;

    // Token m_current_token;
    char m_current_char;

    // Handle identifiers and reserved keywords.
    Token id();

public:
    Lexer(const string & text);
    Lexer(const Lexer &) = default;

    void error();

    // Peek a char from input buffer without actually consuming the
    // next char.
    char peek();

    // Advance the 'm_pos' pointer and set the 'm_current_char' variable.
    void advance();

    void skip_whitespace();

    void skip_comment();

    // Return a (multidigit) integer consumed from the input.
    Token number();

    // Lexical analyzer (also know as scanner or tokenizer)
    // This function is responsible for breaking a sentance
    // apart into tokens. One token at a time.
    Token get_next_token();
};

} // namespace ESI

#endif
