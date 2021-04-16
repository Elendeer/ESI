/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 08:41:25
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-20 22:18:48
* @Description  :
*********************************************/

#include <iostream>

#include "../inc/token.hpp"

using std::string;
using std::unordered_map;

namespace ESI {

const unordered_map<TokenType, string> Token::map_token_type_string {
    {TokenType::NONE, "NONE"},

    // Reserved keywords
    {TokenType::PROGRAM, "PROGRAM"},
    // Types, which are also reserved keywords.
    {TokenType::INTEGER, "INTEGER"},
    {TokenType::REAL, "REAL"},

    {TokenType::INTEGER_DIV, "DIV"}, // the DIV reserved keyword

    {TokenType::BEGIN, "BEGIN"},
    {TokenType::PROCEDURE, "PROCEDURE"},
    {TokenType::VAR, "VAR"},

    // End of reserved keywords
    {TokenType::END, "END"},


    {TokenType::INTEGER_CONST, "INTEGER_CONST"},
    {TokenType::REAL_CONST, "REAL_CONST"},

    {TokenType::MUL, "MUL"},
    {TokenType::FLOAT_DIV, "FLOAT_DIV"},
    {TokenType::PLUS, "PLUS"},
    {TokenType::MINUS, "MINUS"},
    {TokenType::LPAREN, "LPAREN"},
    {TokenType::RPAREN, "RPAREN"},

    {TokenType::eEOF, "eEOF"},

    {TokenType::DOT, "DOT"},
    {TokenType::ASSIGN, "ASSIGN"},
    {TokenType::SEMI, "SEMI"},
    {TokenType::COMMA, "COMMA"},
    {TokenType::ID, "ID"},

    {TokenType::COLON, "COLON"},

};

/*********************************************
* Overload the construction function to fit different
* input value (int / string).
*********************************************/

Token::Token(int line_no, int column) :
    m_type(TokenType::NONE),
    m_line_no(line_no),
    m_column(column) {
        m_value = Any((string)"NONE");
    }

Token::Token(TokenType type, Any value, int line_no, int column)
    : m_type(type), m_value(value), m_line_no(line_no), m_column(column) {}

Token::~Token() {
}


string Token::getStringRepr() {
    using std::to_string;

    string type = map_token_type_string.at(m_type);
	if (m_type == TokenType::INTEGER_CONST) {
		return "Token(" + type + ", "
            + to_string(Any::anyCast<int>(m_value)) + ")"
            + "line: " + to_string(m_line_no)
            + "column: " + to_string(m_column);
	}
	else if (m_type == TokenType::REAL_CONST) {
		return "Token(" + type + ", "
		    + to_string(Any::anyCast<double>(m_value)) + ")"
            + "line: " + to_string(m_line_no)
            + "column: " + to_string(m_column);
	}
	else {
		return "Token(" + type + ", \""
            + Any::anyCast<string>(m_value) + "\")"
            + "line: " + to_string(m_line_no)
            + "column: " + to_string(m_column);
	}

}

TokenType Token::getType() const {
    return m_type;
}

Any Token::getVal() const {
    return m_value;
}


} // namespace ESI
