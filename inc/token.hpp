/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 08:21:21
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-01 16:24:46
* @Description  :
*********************************************/

#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <string>

#include "../inc/any.hpp"

namespace ESI {

/*********************************************
* enum types, reflections & constants
*********************************************/

// Enum type to record the type of a token.
enum class TokenType {
    NONE,

    // Reserved keywords
    BEGIN,
    END,
    PROGRAM,
    VAR,

    // Types, which are also reserved keywords.
    INTEGER,
    REAL,

    // Values
    INTEGER_CONST,
    REAL_CONST,

    MUL,
    INTEGER_DIV, // the DIV reserved keyword
    FLOAT_DIV,
    PLUS,
    MINUS,
    LPAREN,
    RPAREN,

    eEOF,

    DOT,
    ASSIGN,
    SEMI,
    COMMA,
    ID,

    COLON,
};

// String representation of TokenTypes.
const static std::string TokenTypeString[] = {
    "NONE",

    // Reserved keywords
    "BEGIN",
    "END",
    "PROGRAM",
    "VAR",

    // Types, which are also reserved keywords.
    "INTEGER",
    "REAL",

    // Values
    "INTEGER_CONST",
    "REAL_CONST",

    "MUL",
    "INTEGER_DIV", // the DIV reserved keyword
    "FLOAT_DIV",
    "PLUS",
    "MINUS",
    "LPAREN",
    "RPAREN",

    "eEOF",

    "DOT",
    "ASSIGN",
    "SEMI",
    "COMMA",
    "ID",

    "COLON",
};

const static char NOCHAR = (char)(-1);
const static int NOVAL = -1;


/*********************************************
 * Token class
*********************************************/

class Token {
private:
    TokenType m_type;
    Any m_value;


public:
    // Appointment: None type token by default.
    Token();
    Token(TokenType type, Any value);
    Token(const Token &obj) = default;

    // String representation of the class instance.
    // Examples:
    // Token(INTEGER, 3)
    // Token(MUL, '+')
    void print_str_repr();

    // Return the type of the token.
    // The type of token will be a TokenType type
    // variable (enum type).
    TokenType getType() const;

    // Return the value inside token which is Any type.
    Any getVal() const;

    ~Token();
};

} // namespace ESI

#endif
