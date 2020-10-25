/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 08:41:25
* @LastEditors  : Elendeer
* @LastEditTime : 2020-06-11 12:12:21
* @Description  :
*********************************************/

#include "../inc/token.hpp"


namespace ESI {
/**
 * @description: convert a interger to a string representation
 */
string repr(int num) {
    string s;
    while (num != 0) {
        int n = num % 10;
        num /= 10;
        s = (char)(n + '0') + s;
    }
    return s;
}



/*********************************************
* @description: Overload the construction function to fit different
* input value (int / string).
*********************************************/
Token::Token() : m_type(TokenType::NONE), m_value(0), m_strVal("") {}

Token::Token(TokenType type, int value) : m_type(type), m_value(value) {
    m_strVal = "";
}
Token::Token(TokenType type, string value) : m_type(type), m_strVal(value) {
    m_value = 0;
}

/**
 * @description:
    String representation of the class instance.
    Examples:
    Token(INTEGER, 3)
    Token(MUL, '+')
*/
std::string Token::str_repr() {
    std::string type = TokenTypeString[(int)m_type];
    if (m_type == TokenType::INTEGER) {
        std::string value = repr(m_value);
        return "Token(" + type + ", " + value + ")";
    } else {
        return "Token(" + type + ", " + m_strVal + ")";
    }
}

TokenType Token::getType() const {
    return m_type;
}
int Token::getVal() const {
    return m_value;
}
string Token::getStrVal() const {
    return m_strVal;
}

}  // namespace ESI
