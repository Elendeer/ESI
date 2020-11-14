#include "../inc/lexer.hpp"

#include <stdexcept> // std::runtime error
#include <iostream>

namespace ESI {

/*********************************************
* @description: Handle identifiers and reserved keywords.
*********************************************/
Token Lexer::id() {
    std::string result = "";

    while (m_current_char != NOCHAR && ((m_current_char >= '0' && m_current_char <= '9') || (m_current_char >= 'a' && m_current_char <= 'z') || (m_current_char >= 'A' && m_current_char <= 'Z'))) {

        result += m_current_char;
        advance();
    }

    for (int j = 0; j <= (int)reservedKeywordsString.size() - 1; ++j) {
        if (result == reservedKeywordsString[j]) {
            return reservedKeywordsToken[j];
        }
    }

    return Token(TokenType::ID, result);
}

/*********************************************
* @description: Construction function.
*********************************************/
Lexer::Lexer(string text)
    : m_text(text), m_pos(0), m_current_char(m_text[m_pos]) {
    // text : client string input, e.g. "3+5"
}

void Lexer::error() {
    throw std::runtime_error("Lexer : Invalid Syntax");
}

/*********************************************
* @description:
* Peek a char from input buffer without actually consuming the
* next char.
*********************************************/
char Lexer::peek() {
    int peek_pos = m_pos + 1;

    if (peek_pos > (int)m_text.length() - 1) {
        return NOCHAR;
    } else {
        return m_text[peek_pos];
    }
}

/*********************************************
* @description:
Advance the 'm_pos' pointer and set the 'm_current_char' variable.
*********************************************/
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

/*********************************************
* @description: Return a (multidigit) integer consumed from the input.
*********************************************/
int Lexer::interger() {
    int result = 0;
    while (m_current_char >= '0' && m_current_char <= '9') {
        result = result * 10 + (int)(m_current_char - '0');
        advance();
    }
    return result;
}

/*********************************************
* @description:
    Lexical analyzer (also know as scanner or tokenizer)
    This function is responsible for breaking a sentance
    apart into tokens. One token at a time.
*********************************************/
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
