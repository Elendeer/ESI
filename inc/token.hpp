/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 08:21:21
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-11-14 09:33:52
* @Description  :
*********************************************/

#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <string>

namespace ESI {
using std::string;

/*********************************************
* enum types, reflections & constants
*********************************************/

// Enum type to record the type of a token.
enum class TokenType {
    NONE,
    INTEGER,
    MUL,
    DIV,
    PLUS,
    MINUS,
    LPAREN,
    RPAREN,
    eEOF,

    BEGIN,
    END,
    DOT,
    ASSIGN,
    SEMI,
    ID
};

// String representation of TokenTypes.
const std::string TokenTypeString[] = {
    "NONE",
    "INTEGER",
    "MUL",
    "DIV", "PLUS",
    "MINUS", "LPAREN",
    "RPAREN", "EOF",

    "BEGIN",
    "END",
    "DOT",
    "ASSIGN",
    "SEMI",
    "ID"
};

const char NOCHAR = '#';
const int NOVAL = -1;

/*********************************************
* classes & functions
*********************************************/

/**
 * @description: convert a interger to a string representation
 */
string repr(int num);

class Token {
private:
    TokenType m_type;
    int m_value;
    string m_strVal;

public:
    Token();
    Token(TokenType type, int value);
    Token(TokenType type, string value);
    Token(const Token &obj) = default;

    // String representation of the class instance.
    // Examples:
    // Token(INTEGER, 3)
    // Token(MUL, '+')
    string str_repr();

    TokenType getType() const;
    int getVal() const;
    string getStrVal() const;
};

} // namespace ESI

#endif
