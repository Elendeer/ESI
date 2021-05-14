#include "../inc/lexer.hpp"

#include <iostream>
#include <cstring>
#include <algorithm>

using std::string;
using std::transform;

namespace ESI {

// ===== =====
// ===== ===== Lexer, private
// ===== =====

const char Lexer::NOCHAR = (char)(-1);

// Build resered keywords according to enum class TokenType.
void Lexer::buildReservedKeywordMap() {
    // Enum class TokenType will make all reserved words between
    // TokenType::PROGRAM and TokenType::END.
    for (int i = (int)TokenType::PROGRAM; i <= (int)TokenType::END; ++ i ) {
        string token_str = Token::map_token_type_string.at((TokenType)i);
        m_reserved_keyword_map[token_str] =
            Token((TokenType)i, token_str);

        // Lower case version keywords is available too.

        string lower_token_str;
        lower_token_str.resize(token_str.size());

        transform(token_str.begin(), token_str.end(),
            lower_token_str.begin(), tolower);

        m_reserved_keyword_map[lower_token_str] =
            Token((TokenType)i, token_str);
    }
}

void Lexer::error(string message, ErrorCode error_code) {
    string msg = message
            + " At: line " + std::to_string(m_line_no)
            + ", column " + std::to_string(m_column) + ".";

    throw LexerError(msg, error_code);
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

        return Token(TokenType::REAL_CONST,
                result,
                m_line_no,
                m_column);
    }
    else {
        return Token(TokenType::INTEGER_CONST,
                (int)result,
                m_line_no,
                m_column);
    }
}

Token Lexer::id() {
    string result = "";

    while (
        m_current_char != NOCHAR
        && ((m_current_char >= '0' && m_current_char <= '9')
        || (m_current_char >= 'a' && m_current_char <= 'z')
        || (m_current_char >= 'A' && m_current_char <= 'Z'))) {

        result += m_current_char;
        advance();
    }

    // If it's a reserved word
    if (m_reserved_keyword_map.find(result) != m_reserved_keyword_map.end()) {
        return Token(
                m_reserved_keyword_map.at(result),
                m_line_no,
                m_column);
    }

    return Token(
            TokenType::ID,
            result,
            m_line_no,
            m_column);
}

Token Lexer::readString() {
    string result = "";

    while (m_current_char != NOCHAR) {
        if (m_current_char == '\'' && peek() == '\'') {
            // '\'' make the next '\'' a normal character.
            advance();
        }
        else if (m_current_char == '\'' && peek() != '\'') {
            // skip the last '\''
            advance();
            break;
        }

        result += m_current_char;
        advance();
    }

    return Token(
            TokenType::STRING,
            result,
            m_line_no,
            m_column);
}


// ===== =====
// ===== ===== public
// ===== =====


// Constructor.
// text : client string input, e.g. "3+5"
Lexer::Lexer(const string & text) :
    m_text(text),
    m_pos(0),
    m_current_char(m_text[m_pos]),
    m_line_no(1),
    m_column(1) {
        buildReservedKeywordMap();
    }

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
            return Token(
                    TokenType::MUL,
                    (string)"*",
                    m_line_no,
                    m_column);
        }
        else if (m_current_char == '/') {
            advance();
            return Token(
                    TokenType::FLOAT_DIV,
                    (string)"/",
                    m_line_no,
                    m_column);
        }
        else if (m_current_char == '+') {
            advance();
            return Token(
                    TokenType::PLUS,
                    (string)"+",
                    m_line_no,
                    m_column);
        }
        else if (m_current_char == '-') {
            advance();
            return Token(
                    TokenType::MINUS,
                    (string)"-",
                    m_line_no,
                    m_column);
        }

        else if (m_current_char == '(') {
            advance();
            return Token(
                    TokenType::LPAREN,
                    (string)"(",
                    m_line_no,
                    m_column);
        }
        else if (m_current_char == ')') {
            advance();
            return Token(
                    TokenType::RPAREN,
                    (string)")",
                    m_line_no,
                    m_column);
        }
        // Symbols about
        else if ((m_current_char >= 'a' && m_current_char <= 'z')
                || (m_current_char >= 'A' && m_current_char <= 'Z')) {
            return id();
        }

        else if (m_current_char == ':' && peek() == '=') {
            advance();
            advance();
            return Token(
                    TokenType::ASSIGN,
                    (string)":=",
                    m_line_no,
                    m_column);
        }
        else if (m_current_char == ':') {
            advance();
            return Token(
                    TokenType::COLON,
                    (string)":",
                    m_line_no,
                    m_column);
        }

        else if (m_current_char == ';') {
            advance();
            return Token(
                    TokenType::SEMI,
                    (string)";",
                    m_line_no,
                    m_column);
        }
        else if (m_current_char == '.') {
            advance();
            return Token(
                    TokenType::DOT,
                    (string)".",
                    m_line_no,
                    m_column);
        }
        else if (m_current_char == ',') {
            advance();
            return Token(
                    TokenType::COMMA,
                    (string)",",
                    m_line_no,
                    m_column);
        }
        else if (m_current_char == '\'') {
            advance();
            return readString();
        }
        else if (m_current_char == '=') {
            advance();
            return Token(
                    TokenType::EQUAL,
                    (string)"=",
                    m_line_no,
                    m_column);
        }
        else if (m_current_char == '<' && peek() == '>') {
            advance();
            advance();
            return Token(
                    TokenType::NOT_EQUAL,
                    (string)"<>",
                    m_line_no,
                    m_column);
        }
        else if (m_current_char == '<') {
            advance();
            return Token(
                    TokenType::LESS_THAN,
                    (string)"<",
                    m_line_no,
                    m_column);
        }
        else if (m_current_char == '<' && peek() == '=') {
            advance();
            advance();
            return Token(
                    TokenType::LESS_THAN_OR_EQUAL_TO,
                    (string)"<=",
                    m_line_no,
                    m_column);
        }
        else if (m_current_char == '>') {
            advance();
            return Token(
                    TokenType::GREATER_THAN,
                    (string)">",
                    m_line_no,
                    m_column);
        }
        else if (m_current_char == '>' && peek() == '=') {
            advance();
            advance();
            return Token(
                    TokenType::GREATER_THAN_OR_EQUAL_TO,
                    (string)">=",
                    m_line_no,
                    m_column);
        }
        else {
            error("Invailid Character met.", ErrorCode::NONE);
        }
    }

    // No value inside.
    return Token(TokenType::eEOF,
            Any(),
            m_line_no,
            m_column);
}

char Lexer::getCurrentChar() const {
    return m_current_char;
}


// ===== =====
// ===== ===== LexerError
// ===== =====

LexerError::LexerError(
        const std::string & message,
        ErrorCode error_code,
        Token token) :
        Exception(message, error_code, token) {}

LexerError::~LexerError() {}

const string LexerError::what() const {
    return "LexerError met: <<" + m_msg + ">>";
}


} // namespace ESI
