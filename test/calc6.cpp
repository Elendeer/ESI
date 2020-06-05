/*
 * @Author: Elendeer
 * @Date: 2020-05-29 15:09:29
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-05-30 00:42:10
 * @Description: a whole calculator
 */
#include<iostream>
#include<string>
#include<exception>


using std::string;

enum TokenType { // define enum type to record the type of a token.
    NONE,
    INTEGER,
    MUL, DIV,
    PLUS, MINUS,
    LPAREN, RPAREN,
    eEOF
};
const string getStringFromEnum[] = {
    "NONE",
    "INTEGER",
    "MUL", "DIV",
    "PLUS", "MINUS",
    "LPAREN", "RPAREN",
    "EOF"
};

const char NOCHAR = '#';
const int NOVAL = -1;

/**
 * @description: convert a interger to a string representation
 * @param {int}
 * @return: string
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
string repr(char c) {
    // 由于Token类的成员为int，此重载暂时无用
    string s;
    s = s + c;
    return s;
}

class Token {
private:
    TokenType m_type;
    int m_value;
    // token types : interger, plus, minus, or EOF
    // token value : 0-9, '+', '-', or None
public:
    Token(TokenType type = NONE, int value = 0);
    Token(const Token& obj) = default;
    // pay attention to the default initialization function

    string str_repr();

    friend class Lexer;
    friend class Interpreter;
};
Token::Token(TokenType type, int value) : m_type(type), m_value(value) {}

/**
 * @description:
    String representation of the class instance.
    Examples:
    Token(INTEGER, 3)
    Token(MUL, '+')
 * @param {none}
 * @return: string
 */
string Token::str_repr() {
    string type = getStringFromEnum[m_type];
    string value = repr(m_value);
    return "Token(" + type + ", " + value + ")";
}

/**************************************/

class Lexer {
private:
    int m_pos; // index of m_text
    string m_text;
    // Token m_current_token;
    char m_current_char;

public:
    Lexer(string text);
    Lexer(const Lexer&) = default;

    void error();

    void advance();
    void skip_whitespace();
    int interger();

    Token get_next_token();
    // void eat(TokenType token_type);
    // int term();
    // int expr();
};
Lexer::Lexer(string text) : m_text(text), m_pos(0), m_current_char(m_text[m_pos]) {
    // text : client string input, e.g. "3+5"
}

void Lexer::error() {
    throw std::runtime_error("Invalid syntax");
}
// Advance the 'm_pos' pointer and set the 'm_current_char' variable.
void Lexer::advance() {
    ++m_pos;
    if (m_pos > m_text.length() - 1) {
        m_current_char = NOCHAR; // indicates end of input
    }
    else {
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

/*
Parser / Lexer code
*/

class Interpreter {
private:
    Lexer m_lexer;
    Token m_current_token;
public:
    Interpreter(Lexer lexer);

    void error();

    void eat(TokenType token_type);

    //non-terminals
    int factor();
    int term();
    int expr();
};
Interpreter::Interpreter(Lexer lexer) : m_lexer(lexer) {
    m_current_token = m_lexer.get_next_token();
}

void Interpreter::error() {
    throw std::runtime_error("Invalid syntax");
}

/**
 * @description:
    compare the current token type with the passed token
    type and if they match then "eat" the current token
    and assign the next token to the self.current_token,
    otherwise raise an exception.
 * @param {tokenType}
 * @return:
 */
void Interpreter::eat(TokenType token_type) {
    if (m_current_token.m_type == token_type) {
        m_current_token = m_lexer.get_next_token();
    }
    else {
        error();
    }
}
/**
 * @description: The next three functions are all parts of parser
 * and interpreter. Based on grammar.
 * factor : INTEGER | LPAREN expr RPAREN
 * @param {}
 * @return: int
 */
int Interpreter::factor() {
    int value;
    if (m_current_token.m_type == INTEGER) {
        value = m_current_token.m_value;
        eat(INTEGER);
    }
    else {
        eat(LPAREN);
        value = expr();
        eat(RPAREN);
    }
    return value;
}
/**
 * @description: term : factor((MUL | DIV) factor)*
 * @param {}
 * @return:
 */
int Interpreter::term() {
    int result = factor();
    while (m_current_token.m_type == MUL || m_current_token.m_type == DIV) {
        if (m_current_token.m_type == MUL) {
            eat(MUL);
            result *= factor();
        }
        else {
            eat(DIV);
            result /= factor();
        }
    }

    return result;
}
/**
 * @description: This function is both parser and interpreter.
 * Arithmetic expression parser / interpreter
 * expr : term ((PLUS | MINUS) term)*
 * @param {}
 */
int Interpreter::expr() {

    int result = term();
    while (m_current_token.m_type == PLUS || m_current_token.m_type == MINUS) {
        if (m_current_token.m_type == PLUS) {
            eat(PLUS);
            result += term();
        }
        else if (m_current_token.m_type == MINUS) {
            eat(MINUS);
            result -= term();
        }
    }

    return result;
}

int main() {
    while (true) {
        string text;

        std::cout << "calc6> " ;
        std::getline(std::cin, text);

        if (text.length() == 0) {
            continue;
        }
        if (text == "exit") {
            break;
        }

        Lexer lexer(text);
        int result;

        try {
            Interpreter interpreter(lexer);
            result = interpreter.expr();
        }
        catch (std::runtime_error error) {
            // break;
            std::cout << error.what() << std::endl;
            continue;
        }

        std::cout << result << std::endl;
    }
    return 0;
}