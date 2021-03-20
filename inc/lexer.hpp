/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 15:27:18
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-20 21:07:32
 * @Description  :
*********************************************/

#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>
#include <unordered_map>

#include "token.hpp"

namespace ESI {

// Lexer, AKA token analyzer
class Lexer {
private:
    std::string m_text;

    // index of m_text
    int m_pos;

    // Token m_current_token;
    char m_current_char;

    // Represent a 'no char' char.
    const static char NOCHAR;

    const static std::unordered_map<std::string, Token>reservedKeywords ;

    // ===== functions =====

    void error();

    // Peek a char from input buffer without actually consuming the
    // next char.
    char peek();

    // Advance the 'm_pos' pointer and set the 'm_current_char' variable.
    void advance();

    // Skip space, tab and '\n'.
    void skipWhitespace();

    void skipComment();

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
    // May throw exception.
    Token getNextToken();
};

} // namespace ESI

#endif
