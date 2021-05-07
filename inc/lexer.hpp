/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 15:27:18
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-05-07 20:49:41
 * @Description  :
*********************************************/

#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>
#include <unordered_map>
#include <exception>

#include "token.hpp"
#include "exception.hpp"

namespace ESI {

// Lexer, AKA token analyzer
class Lexer {
private:
    std::string m_text;

    // index of m_text
    int m_pos;

    // Token m_current_token;
    char m_current_char;

    // Current analizing line number of source code.
    int m_line_no;
    // Current analizing column of source code.
    int m_column;

    // Map of reserved key words.
    // Will be build according to enum class TokenType.
    std::unordered_map<std::string, Token>m_reserved_keyword_map ;


    // ===== static members =====

    // Represent a 'no char' char.
    const static char NOCHAR;

    // ===== functions =====

    // Build reserved keywords according to enum class TokenType.
    void buildReservedKeywordMap();

    void error(std::string message, ErrorCode error_code);

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

    // Recognize a string, retrun a string token.
    Token readString();

public:
    Lexer(const std::string & text);
    // Lexer(const Lexer &) = default;
    ~Lexer();


    // Lexical analyzer (also know as scanner or tokenizer)
    // This function is responsible for breaking a sentance
    // apart into tokens. One token at a time.
    // May throw exception.
    Token getNextToken();

    char getCurrentChar() const;
};

// Error thrown by Lexer.
class LexerError : public Exception {
private:

public :
    LexerError(
        const std::string & message,
        ErrorCode error_code = ErrorCode::NONE,
        Token token = Token());

    ~LexerError();

    virtual const std::string what() const;
};

} // namespace ESI

#endif
