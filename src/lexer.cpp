#include "../inc/lexer.hpp"

#include <stdexcept> // std::runtime error
#include <iostream>

using std::string;

namespace ESI {

const char Lexer::NOCHAR = (char)(-1);

const std::unordered_map<string, Token> Lexer::reservedKeywords {
    {"PROGRAM", Token(TokenType::PROGRAM, (std::string)"PROGRAM")},
    {"VAR", Token(TokenType::VAR, (std::string)"VAR")},
    {"INTEGER", Token(TokenType::INTEGER, (std::string)"INTEGER")},
    {"REAL", Token(TokenType::REAL, (std::string)"REAL")},
    {"INTEGER_DIV", Token(TokenType::INTEGER_DIV, (std::string)"INTEGER_DIV")},
    {"FLOAT_DIV", Token(TokenType::FLOAT_DIV, (std::string)"FLOAT_DIV")},
    {"BEGIN", Token(TokenType::BEGIN, (std::string)"BEGIN")},
    {"END", Token(TokenType::END, (std::string)"END")}
};

Token Lexer::id() {
    std::string result = "";

    while (
        m_current_char != NOCHAR
        && ((m_current_char >= '0' && m_current_char <= '9')
        || (m_current_char >= 'a' && m_current_char <= 'z')
        || (m_current_char >= 'A' && m_current_char <= 'Z'))) {

        result += m_current_char;
        advance();
    }

    // If it's a reserved word
    if (reservedKeywords.find(result) != reservedKeywords.end()) {
        // Using operator [] may change the map,
        // which is a const here.
        return Token(reservedKeywords.at(result));
    }

    return Token(TokenType::ID, result);
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
    while (m_current_char == ' '
    || m_current_char == '\t'
    || m_current_char == '\n') {

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
        advance();
        int power = 10;

        while (m_current_char >= '0' && m_current_char <= '9') {
            result = result + (double)(m_current_char - '0') / power;
            power *= 10;
            advance();
        }

        return Token(TokenType::REAL_CONST, result);
    }
    else {
        return Token(TokenType::INTEGER_CONST, (int)result);
    }
}


// Constructor.
Lexer::Lexer(const string & text)
    : m_text(text), m_pos(0), m_current_char(m_text[m_pos]) {
    // text : client string input, e.g. "3+5"
}

Lexer::~Lexer() {

}


Token Lexer::get_next_token() {
    while (m_current_char != NOCHAR) {

        if (m_current_char == ' ' ||
            m_current_char == '\t' ||
            m_current_char == '\n' ) {

            skip_whitespace();
            continue;
        }
        else if (m_current_char == '{') {
            advance();
            skip_comment();
            continue;
        }
        // Arithmetic expression about
        else if (m_current_char >= '0' && m_current_char <= '9') {
            return number();
        }

        else if (m_current_char == '*') {
            advance();
            return Token(TokenType::MUL, "*");
        }
        else if (m_current_char == '/') {
            advance();
            return Token(TokenType::FLOAT_DIV, "/");
        }
        else if (m_current_char == '+') {
            advance();
            return Token(TokenType::PLUS, "+");
        }
        else if (m_current_char == '-') {
            advance();
            return Token(TokenType::MINUS, "-");
        }

        else if (m_current_char == '(') {
            advance();
            return Token(TokenType::LPAREN, "(");
        }
        else if (m_current_char == ')') {
            advance();
            return Token(TokenType::RPAREN, ")");
        }
        // Symbols about
        else if ((m_current_char >= 'a' && m_current_char <= 'z') || (m_current_char >= 'A' && m_current_char <= 'Z')) {
            return id();
        }

        else if (m_current_char == ':' && peek() == '=') {
            advance();
            advance();
            return Token(TokenType::ASSIGN, ":=");
        }
        else if (m_current_char == ':') {
            advance();
            return Token(TokenType::COLON, ":");
        }

        else if (m_current_char == ';') {
            advance();
            return Token(TokenType::SEMI, ";");
        }
        else if (m_current_char == '.') {
            advance();
            return Token(TokenType::DOT, ".");
        }
        else if (m_current_char == ',') {
            advance();
            return Token(TokenType::COMMA, ",");
        }

        else {
            error();
        }
    }

    // No value inside.
    return Token(TokenType::eEOF, Any());
}

} // namespace ESI
