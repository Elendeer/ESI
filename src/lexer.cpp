/*
 * @Author: Elendeer
 * @Date: 2020-06-05 15:36:09
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-05 20:50:55
 * @Description: file content
 */

#include "../inc/lexer.hpp"

#include <stdexcept>  // std::runtime error

namespace ESI {

Lexer::Lexer(string text)
    : m_text(text), m_pos(0), m_current_char(m_text[m_pos]) {
    // text : client string input, e.g. "3+5"
}

void Lexer::error() {
    throw std::runtime_error("Invalid syntax");
}
// Advance the 'm_pos' pointer and set the 'm_current_char' variable.
void Lexer::advance() {
    ++m_pos;
    if ((long long unsigned)m_pos > m_text.length() - 1) {
        m_current_char = NOCHAR;  // indicates end of input
    } else {
        m_current_char = m_text[m_pos];
    }
}
void Lexer::skip_whitespace() {
    while (m_current_char == ' ') {
        advance();
    }
}
// Return a (multidigit) integer consumed from the input.
int Lexer::interger() {
    int result = 0;
    while (m_current_char >= '0' && m_current_char <= '9') {
        result = result * 10 + (int)(m_current_char - '0');
        advance();
    }
    return result;
}

/**
 * @description:
    Lexical analyzer (also know as scanner or tokenizer)
    This function is responsible for breaking a sentance
    apart into tokens. One token at a time.
* @param {none}
* @return: Token
*/
Token Lexer::get_next_token() {
    while (m_current_char != NOCHAR) {
        if (m_current_char == ' ') {
            skip_whitespace();
            continue;
        }
        if (m_current_char >= '0' && m_current_char <= '9') {
            return Token(INTEGER, interger());
        }
        if (m_current_char == '*') {
            advance();
            return Token(MUL, '*');
        }
        if (m_current_char == '/') {
            advance();
            return Token(DIV, '/');
        }
        if (m_current_char == '+') {
            advance();
            return Token(PLUS, '+');
        }
        if (m_current_char == '-') {
            advance();
            return Token(MINUS, '-');
        }
        if (m_current_char == '(') {
            advance();
            return Token(LPAREN, '(');
        }
        if (m_current_char == ')') {
            advance();
            return Token(RPAREN, ')');
        }

        error();
    }

    return Token(eEOF, NOVAL);
}

}  // namespace ESI
