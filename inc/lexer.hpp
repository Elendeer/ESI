/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 15:27:18
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-02-22 17:21:14
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
// If use unordered_map <string , Token> will cause a bug.
static std::unordered_map<std::string, Token>reservedKeywords {
    {"PROGRAM", Token(TokenType::PROGRAM, "PROGRAM")},
    {"VAR", Token(TokenType::VAR, "VAR")},
    {"INTEGER", Token(TokenType::INTEGER, "INTEGER")},
    {"REAL", Token(TokenType::REAL, "REAL")},
    {"INTEGER_DIV", Token(TokenType::INTEGER_DIV, "INTEGER_DIV")},
    {"FLOAT_DIV", Token(TokenType::FLOAT_DIV, "FLOAT_DIV")},
    {"BEGIN", Token(TokenType::BEGIN, "BEGIN")},
    {"END", Token(TokenType::END, "END")}
};

// const static std::unordered_map<std::string, Token&>reservedKeywords {
//     {"PROGRAM", *(new Token(TokenType::PROGRAM, "PROGRAM"))},
//     {"VAR", *(new Token(TokenType::VAR, "VAR"))},
//     {"INTEGER", *(new Token(TokenType::INTEGER, "INTEGER"))},
//     {"REAL", *(new Token(TokenType::REAL, "REAL"))},
//     {"INTEGER_DIV", *(new Token(TokenType::INTEGER_DIV, "INTEGER_DIV"))},
//     {"FLOAT_DIV", *(new Token(TokenType::FLOAT_DIV, "FLOAT_DIV"))},
//     {"BEGIN", *(new Token(TokenType::BEGIN, "BEGIN"))},
//     {"END", *(new Token(TokenType::END, "END"))}
// };


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
