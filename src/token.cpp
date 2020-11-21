/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 08:41:25
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-11-21 12:05:27
* @Description  :
*********************************************/

#include <iostream>
#include "../inc/token.hpp"

namespace ESI {

/*********************************************
* Overload the construction function to fit different
* input value (int / string).
*********************************************/

// Appointment: None type token by default.
Token::Token() : m_type(TokenType::NONE) {
    m_value.p_str = new string("NONE");
}

Token::Token(TokenType type, int value) : m_type(type) {
    m_value.p_int = new int(value);
}
Token::Token(TokenType type, double value) : m_type(type) {
	m_value.p_double = new double (value);
}
Token::Token(TokenType type, const string &value) : m_type(type) {
    m_value.p_str = new string(value);
}


void Token::print_str_repr() {
    using std::cout;

    string type = TokenTypeString[(int)m_type];
	if (m_type == TokenType::INTEGER_CONST) {
		cout << "Token(" + type + ", " <<
		*m_value.p_int << ")";
	}
	else if (m_type == TokenType::REAL_CONST) {
		cout << "Token(" + type + ", " <<
		*m_value.p_double << ")";
	}
	else {
		cout << "Token(" + type + ", " <<
		*m_value.p_str << ")";
	}
}

TokenType Token::getType() const {
    return m_type;
}

void * Token::getVal() const {
    if (m_type == TokenType::INTEGER_CONST) {
		return m_value.p_int;
    }
	else if (m_type == TokenType::REAL_CONST) {
		return m_value.p_double;
	}
	else {
		return m_value.p_str;
	}
}

Token::~Token() {
    if (m_type == TokenType::INTEGER_CONST) {
        delete m_value.p_int;
    }
    else if (m_type == TokenType::REAL_CONST) {
        delete m_value.p_double;
    }
    else {
        delete m_value.p_str;
    }
}

} // namespace ESI
