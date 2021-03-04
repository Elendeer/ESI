/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 15:27:18
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-04 01:13:58
 * @Description  :
*********************************************/

#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>
#include <unordered_map>

#include "token.hpp"

namespace ESI {

/*********************************************
* enum types, reflections & constants
*********************************************/

static const std::unordered_map<std::string, Token>reservedKeywords {
    {"PROGRAM", Token(TokenType::PROGRAM, (std::string)"PROGRAM")},
    {"VAR", Token(TokenType::VAR, (std::string)"VAR")},
    {"INTEGER", Token(TokenType::INTEGER, (std::string)"INTEGER")},
    {"REAL", Token(TokenType::REAL, (std::string)"REAL")},
    {"INTEGER_DIV", Token(TokenType::INTEGER_DIV, (std::string)"INTEGER_DIV")},
    {"FLOAT_DIV", Token(TokenType::FLOAT_DIV, (std::string)"FLOAT_DIV")},
    {"BEGIN", Token(TokenType::BEGIN, (std::string)"BEGIN")},
    {"END", Token(TokenType::END, (std::string)"END")}
};


/*********************************************
* classes & functions
*********************************************/

class Lexer {
private:
    std::string m_text;

    // index of m_text
    int m_pos;

    // Token m_current_token;
    char m_current_char;

    void error();

    // Peek a char from input buffer without actually consuming the
    // next char.
    char peek();

    // Advance the 'm_pos' pointer and set the 'm_current_char' variable.
    void advance();

    // Skip space, tab and '\n'.
    void skip_whitespace();

    void skip_comment();

    // Return a (multidigit) integer consumed from the input.
    Token number();

    // Handle identifiers and reserved keywords.
    Token id();

public:
    Lexer(const std::string & text);
    // Lexer(const Lexer &) = default;
    ~Lexer();


    // Lexical analyzer (also know as scanner or tokenizer)
    // This function is responsible for breaking a sentance
    // apart into tokens. One token at a time.
    Token get_next_token();
};

} // namespace ESI

#endif
