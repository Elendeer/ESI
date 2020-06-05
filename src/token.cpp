/*
 * @Author: Elendeer
 * @Date: 2020-06-05 08:41:25
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-05 20:41:49
 * @Description: file content
 */

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



Token::Token(TokenType type, int value) : m_type(type), m_value(value) {}

/**
 * @description:
    String representation of the class instance.
    Examples:
    Token(INTEGER, 3)
    Token(MUL, '+')
*/
std::string Token::str_repr() {
    std::string type = TokenTypeString[m_type];
    std::string value = repr(m_value);
    return "Token(" + type + ", " + value + ")";
}

TokenType Token::getType() const {
    return m_type;
}
int Token::getVal() const {
    return m_value;
}

}  // namespace ESI
