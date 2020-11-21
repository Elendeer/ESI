#include "../inc/lexer.hpp"

#include <stdexcept> // std::runtime error
#include <iostream>

namespace ESI {

Token Lexer::id() {
    std::string result = "";

    while (m_current_char != NOCHAR && ((m_current_char >= '0' && m_current_char <= '9') || (m_current_char >= 'a' && m_current_char <= 'z') || (m_current_char >= 'A' && m_current_char <= 'Z'))) {

        result += m_current_char;
        advance();
    }

    // If it's a reserved word
    if (reservedKeywords.find(result) != reservedKeywords.end())
        // Can't ues operator [] for it may change the map,
        // which is a const here.
        return reservedKeywords.at(result);

    return Token(TokenType::ID, result);
}

// Construction function.
Lexer::Lexer(const string & text)
    : m_text(text), m_pos(0), m_current_char(m_text[m_pos]) {
    // text : client string input, e.g. "3+5"
}

void Lexer::error() {
    throw std::runtime_error("Lexer : Invalid Syntax");
}

char Lexer::peek() {
    int peek_pos = m_pos + 1;

    if (peek_pos > (int)m_text.length() - 1) {
        return NOCHAR;
    } else {
        return m_text[peek_pos];
    }
}

void Lexer::advance() {
    ++m_pos;
    if ((long long unsigned)m_pos > m_text.length() - 1) {
        m_current_char = NOCHAR; // indicates end of input
    } else {
        m_current_char = m_text[m_pos];
    }
}
void Lexer::skip_whitespace() {
    while (m_current_char == ' ') {
        advance();
    }
}
void Lexer::skip_comment() {
    while (m_current_char != '}') {
        advance();
    }
    // Skip the closing curly brase.
    advance();
}

Token Lexer::number() {
    double result = 0;

    while (m_current_char >= '0' && m_current_char <= '9') {
        result = result * 10 + (int)(m_current_char - '0');
        advance();
    }
    if (m_current_char == '.') {
        int power = 10;

        while (m_current_char >= '0' && m_current_char <= '9') {
            result = result + (double)(m_current_char - '0') / power;
            power *= 10;
        }

        return Token(TokenType::REAL_CONST, result);
    }
    else {
        return Token(TokenType::INTEGER_CONST, (int)result);
    }
}

Token Lexer::get_next_token() {
    while (m_current_char != NOCHAR) {
        // Arithmetic expression about
        if (m_current_char == ' ') {
            skip_whitespace();
            continue;
        }
        if (m_current_char >= '0' && m_current_char <= '9') {
            return Token(TokenType::INTEGER, interger());
        }
        if (m_current_char == '*') {
            advance();
            return Token(TokenType::MUL, "*");
        }
        if (m_current_char == '/') {
            advance();
            return Token(TokenType::DIV, "/");
        }
        if (m_current_char == '+') {
            advance();
            return Token(TokenType::PLUS, "+");
        }
        if (m_current_char == '-') {
            advance();
            return Token(TokenType::MINUS, "-");
        }
        if (m_current_char == '(') {
            advance();
            return Token(TokenType::LPAREN, "(");
        }
        if (m_current_char == ')') {
            advance();
            return Token(TokenType::RPAREN, ")");
        }
        // Symbols about
        if ((m_current_char >= 'a' && m_current_char <= 'z') || (m_current_char >= 'A' && m_current_char <= 'Z')) {
            return id();
        }
        if (m_current_char == ':' && peek() == '=') {
            advance();
            advance();
            return Token(TokenType::ASSIGN, ":=");
        }
        if (m_current_char == ';') {
            advance();
            return Token(TokenType::SEMI, ";");
        }
        if (m_current_char == '.') {
            advance();
            return Token(TokenType::DOT, ".");
        }

        error();
    }

    return Token(TokenType::eEOF, NOVAL);
}

} // namespace ESI
