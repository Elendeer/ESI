/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 08:21:21
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-11-21 12:39:57
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
const std::string TokenTypeString[] = {
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

const char NOCHAR = '#';
const int NOVAL = -1;

/*********************************************
* classes & functions
*********************************************/

// The type of value of each token may be different,
// And each token have noly one value.
// So we put pointers of different types into this union.
// It's not really necessery in fact, because it can be
// replace by a simple viod*.
union TokenValue {
    // This pointer for return in getVal().
    void * p_void;

    // Pointers below for make the code inside
    // Token class more clear. Like having a
    // automatically type cast exactly.

    int * p_int;
    string * p_str;
    double * p_double;
};


/*********************************************
 * Token class
*********************************************/

class Token {
private:
    TokenType m_type;

    // Union type, pointers inside.
    TokenValue m_value;


public:
    Token();
    Token(TokenType type, int value);
    Token(TokenType type, double value);
    Token(TokenType type, const string & value);
    Token(const Token &obj) = default;

    // String representation of the class instance.
    // Examples:
    // Token(INTEGER, 3)
    // Token(MUL, '+')
    void print_str_repr();

    TokenType getType() const;

    // Return a void pointer pionting to the value of
    // the token.
    void * getVal() const;

    ~Token();
};

} // namespace ESI

#endif
