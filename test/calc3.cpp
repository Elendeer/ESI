/*
 * @Author: Elendeer
 * @Date: 2020-05-27 18:08:53
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-05-29 11:43:31
 * @Description: file content
 */

#include<iostream>
#include<string>
#include<exception>


using std::string;

enum TokenType { // define enum type to record the type of a token.
    NONE, INTERGER, PLUS, MINUS, eEOF
};
const string getStringFromEnum[] = {"NONE", "INTERGER", "PLUS", "MINUS", "EOF"};

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

    friend class Interpreter;
};
Token::Token(TokenType type, int value) : m_type(type), m_value(value) {}

/**
 * @description:
    String representation of the class instance.
    Examples:
    Token(INTERGER, 3)
    Token(PLUS, '+')
 * @param {none}
 * @return: string
 */
string Token::str_repr() {
    string type = getStringFromEnum[m_type];
    string value = repr(m_value);
    return "Token(" + type + ", " + value + ")";
}

/**************************************/

class Interpreter {
private:
    int m_pos; // index of m_text
    string m_text;
    Token m_current_token;
    char m_current_char;

public:
    Interpreter(string text);

    void error();

    void advance();
    void skip_whitespace();
    int interger();

    Token get_next_token();
    void eat(TokenType token_type);
    int term();
    int expr();
};
Interpreter::Interpreter(string text) : m_text(text), m_pos(0), m_current_char(m_text[m_pos]) {
    // text : client string input, e.g. "3+5"
}

void Interpreter::error() {
    throw std::runtime_error("Invalid syntax");
}
// Advance the 'm_pos' pointer and set the 'm_current_char' variable.
void Interpreter::advance() {
    ++m_pos;
    if (m_pos > m_text.length() - 1) {
        m_current_char = NOCHAR; // indicates end of input
    }
    else {
        m_current_char = m_text[m_pos];
    }
}
void Interpreter::skip_whitespace() {
    while (m_current_char == ' ') {
        advance();
    }
}
// Return a (multidigit) integer consumed from the input.
int Interpreter::interger() {
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
Token Interpreter::get_next_token() {

    while (m_current_char != NOCHAR) {
        if (m_current_char == ' ') {
            skip_whitespace();
            continue;
        }
        if (m_current_char >= '0' && m_current_char <= '9') {
            return Token(INTERGER, interger());
        }
        if (m_current_char == '+') {
            advance();
            return Token(PLUS, '+');
        }
        if (m_current_char == '-') {
            advance();
            return Token(MINUS, '-');
        }

        error();
    }

    return Token(eEOF, NOVAL);
}

/*
Parser / Interpreter code
*/

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
        m_current_token = get_next_token();
    }
    else {
        error();
    }
}
/**
 * @description: Return an INTERGER token value.
 * @param {}
 * @return: int
 */
int Interpreter::term() {
    int value = m_current_token.m_value;
    eat(INTERGER);
    return value;
}

/**
 * @description: This function is both parser and interpreter.
 * @param {}
 */
int Interpreter::expr() {
    // set current token to the first token taken from the input
    m_current_token = get_next_token();

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

        std::cout << "calc3> " ;

        try {
            std::getline(std::cin, text);
        }
        catch (const char *) {
            break;
        }

        if (text.length() == 0) {
            continue;
        }

        Interpreter interpreter(text);
        int result = interpreter.expr();

        std::cout << result << std::endl;
    }
    return 0;
}