/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 08:21:21
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-14 20:51:21
* @Description  :
*********************************************/

#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <string>
#include <unordered_map>

#include "../inc/any.hpp"

namespace ESI {

/*********************************************
* enum types, reflections & constants
*********************************************/

// Enum type to record the type of a token.
enum class TokenType {
    NONE,

    // Reserved keywords
    PROGRAM,
    // Types, which are also reserved keywords.
    INTEGER,
    REAL,

    INTEGER_DIV, // the DIV reserved keyword

    BEGIN,
    PROCEDURE,
    VAR,

    // End of reserved keywords
    END,


    INTEGER_CONST,
    REAL_CONST,

    MUL,
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

/*********************************************
 * Token class
*********************************************/

class Token {
private:
    TokenType m_type;
    Any m_value;

    // Represent the position of the token.
    int m_line_no, m_column;

public:
    // Appointment: None type token by default.
    Token(int line_no = -1, int column = -1);
    Token(TokenType type, Any value, int line_no = -1, int column = -1);
    Token(const Token &obj) = default;

    // For reset the line no and column when copy a token.
    // Used when scanning a reserved word.
    Token(const Token &obj, int line_no, int column);

    ~Token();

    // Return string representation of the class instance.
    // Examples:
    // Token(INTEGER, 3)
    // Token(MUL, '+')
    std::string getStringRepr();

    // Return the type of the token.
    // The type of token will be a TokenType type
    // variable (enum type).
    TokenType getType() const;

    // Return the value inside token which is Any type.
    Any getVal() const;

    // String representation of TokenTypes.
    static const std::unordered_map<TokenType, std::string> map_token_type_string ;
};

} // namespace ESI

#endif
