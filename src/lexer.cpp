#include <iostream>
#include <cstring>

#include "../inc/lexer.hpp"

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
    {"END", Token(TokenType::END, (std::string)"END")},

    {"PROCEDURE", Token(TokenType::PROCEDURE, (std::string)"PROCEDURE")},
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
    throw LexerError("Lexer : Invalid Syntax");
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
    if (m_current_char == '\n') {
        ++ m_line_no;
        m_column = 0;
    }

    ++m_pos;
    if ((long long unsigned)m_pos > m_text.length() - 1) {
        m_current_char = NOCHAR; // indicates end of input
    } else {
        m_current_char = m_text[m_pos];
        ++ m_column;
    }
}

void Lexer::skipWhitespace() {
    while (m_current_char == ' '
    || m_current_char == '\t'
    || m_current_char == '\n') {

        advance();
    }
}

void Lexer::skipComment() {
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

// ===== public =====


// Constructor.
// text : client string input, e.g. "3+5"
Lexer::Lexer(const string & text) :
    m_text(text),
    m_pos(0),
    m_current_char(m_text[m_pos]),
    m_line_no(1),
    m_column(1) {}

Lexer::~Lexer() {

}


Token Lexer::getNextToken() {
    while (m_current_char != NOCHAR) {

        if (m_current_char == ' ' ||
            m_current_char == '\t' ||
            m_current_char == '\n' ) {

            skipWhitespace();
            continue;
        }
        else if (m_current_char == '{') {
            advance();
            skipComment();
            continue;
        }
        // Arithmetic expression about
        else if (m_current_char >= '0' && m_current_char <= '9') {
            return number();
        }

        else if (m_current_char == '*') {
            advance();
            return Token(TokenType::MUL, (string)"*");
        }
        else if (m_current_char == '/') {
            advance();
            return Token(TokenType::FLOAT_DIV, (string)"/");
        }
        else if (m_current_char == '+') {
            advance();
            return Token(TokenType::PLUS, (string)"+");
        }
        else if (m_current_char == '-') {
            advance();
            return Token(TokenType::MINUS, (string)"-");
        }

        else if (m_current_char == '(') {
            advance();
            return Token(TokenType::LPAREN, (string)"(");
        }
        else if (m_current_char == ')') {
            advance();
            return Token(TokenType::RPAREN, (string)")");
        }
        // Symbols about
        else if ((m_current_char >= 'a' && m_current_char <= 'z')
                || (m_current_char >= 'A' && m_current_char <= 'Z')) {
            return id();
        }

        else if (m_current_char == ':' && peek() == '=') {
            advance();
            advance();
            return Token(TokenType::ASSIGN, (string)":=");
        }
        else if (m_current_char == ':') {
            advance();
            return Token(TokenType::COLON, (string)":");
        }

        else if (m_current_char == ';') {
            advance();
            return Token(TokenType::SEMI, (string)";");
        }
        else if (m_current_char == '.') {
            advance();
            return Token(TokenType::DOT, (string)".");
        }
        else if (m_current_char == ',') {
            advance();
            return Token(TokenType::COMMA, (string)",");
        }

        else {
            error();
        }
    }

    // No value inside.
    return Token(TokenType::eEOF, Any());
}


// ===== =====
// ===== ===== LexerError
// ===== =====

LexerError::LexerError(const string & message) :
    Exception(message) {}

LexerError::~LexerError() {}

const string LexerError::what() const {
    return m_msg;
}


} // namespace ESI
