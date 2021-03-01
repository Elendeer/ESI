/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 08:41:25
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-01 17:39:17
* @Description  :
*********************************************/

#include <iostream>

#include "../inc/token.hpp"

using std::string;

namespace ESI {

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

    string type = TokenTypeString[(int)m_type];
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
