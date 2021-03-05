/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 08:41:25
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-05 12:20:32
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
    {TokenType::BEGIN, "BEGIN"},
    {TokenType::END, "END"},
    {TokenType::PROGRAM, "PROGRAM"},
    {TokenType::VAR, "VAR"},

    // Types, which are also reserved keywords.
    {TokenType::INTEGER, "INTEGER"},
    {TokenType::REAL, "REAL"},

    // Values
    {TokenType::INTEGER_CONST, "INTEGER_CONST"},
    {TokenType::REAL_CONST, "REAL_CONST"},

    {TokenType::MUL, "MUL"},
    {TokenType::INTEGER_DIV, "INTEGER_DIV"}, // the DIV reserved keyword
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

Token::Token() : m_type(TokenType::NONE) {
    m_value = Any((string)"NONE");
}

Token::Token(TokenType type, Any value)
    : m_type(type), m_value(value) {}

Token::~Token() {
}


void Token::print_str_repr() {
    using std::cout;

    string type = map_token_type_string.at(m_type);
	if (m_type == TokenType::INTEGER_CONST) {
		cout << "Token(" + type + ", " <<
		Any::anyCast<int>(m_value) << ")";
	}
	else if (m_type == TokenType::REAL_CONST) {
		cout << "Token(" + type + ", " <<
		Any::anyCast<double>(m_value) << ")";
	}
	else {
		cout << "Token(" + type + ", " <<
		Any::anyCast<string>(m_value) << ")";
	}
}

TokenType Token::getType() const {
    return m_type;
}

Any Token::getVal() const {
    return m_value;
}


} // namespace ESI
