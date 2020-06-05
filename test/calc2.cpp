/*
添加了枚举类型和枚举到string的数组映射
The get_next_token method was refactored a bit. The logic to increment the pos pointer was factored into a separate method advance.
Two more methods were added: skip_whitespace to ignore whitespace characters and integer to handle multi-digit integers in the input.
The expr method was modified to recognize INTEGER -> MINUS -> INTEGER phrase in addition to INTEGER -> PLUS -> INTEGER phrase. The method now also interprets both addition and subtraction after having successfully recognized the corresponding phrase.
 */

// Token types

// EOF (end-of-file) token is used to indicate that
// there is no more input left for lexical analysiss
#include<iostream>
#include<string>


using std::string;

enum tokenType { //定义枚举类型用于记录token的类型
    NONE, INTERGER, PLUS, MINUS, eEOF
};
const string getStringFromEnum[] = {"NONE", "INTERGER", "PLUS", "MINUS", "EOF"};

// 表示无字符的字符常量
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

class Token {
private:
    tokenType m_type;
    int m_value;
    // token types : interger, plus, minus, or EOF
    // token value : 0-9, '+', '-', or None
public:
    Token(tokenType type = NONE, int value = 0);
    Token(const Token& obj) = default;
    // 注意默认构造函数

    string str_repr();

    friend class Interpreter;
};
Token::Token(tokenType type, int value) : m_type(type), m_value(value) {}

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
    void eat(tokenType token_type);
    int expr();
};
Interpreter::Interpreter(string text) : m_text(text), m_pos(0), m_current_char(m_text[m_pos]) {
    // text : client string input, e.g. "3+5"
}

void Interpreter::error() {
    throw "Error parsing input";
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
// Return a (multidigit) integer consumed from the input. 读到连续的数字结束为止
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

/**
 * @description:
    compare the current token type with the passed token
    type and if they match then "eat" the current token
    and assign the next token to the self.current_token,
    otherwise raise an exception.
 * @param {tokenType}
 * @return:
 */
void Interpreter::eat(tokenType token_type) {
    if (m_current_token.m_type == token_type) {
        m_current_token = get_next_token();
    }
    else {
        error();
    }
}

// this function is both parser and interpreter
int Interpreter::expr() {
    /*
    expr -> INTEGER PLUS INTEGER
    expr -> INTEGER MINUS INTEGER
    */
    // set current token to the first token taken from the input
    m_current_token = get_next_token();

    // we expect the current token to be a single-digit integer
    Token left = m_current_token;
    eat(INTERGER);
    std::cout << left.str_repr() << std::endl;

    // we expect the current token to be a '+' token
    Token op = m_current_token;
    if (op.m_type == PLUS) {
        eat(PLUS);
    }
    else {
        eat(MINUS);
    }
    std::cout << op.str_repr() << std::endl;

    // we expect the current token to be a single-digit integer
    Token right = m_current_token;
    eat(INTERGER);
    //after the above call the self.current_token is set to
    // EOF token

    // at this point the INTEGER PLUS INTEGER
    // or the INTERGER MINUS INTERGER sequence of tokens
    // has been successfully found and the method can just
    // return the result of adding or substracting two integers, thus
    // effectively interpreting client input
    int result;
    if (op.m_type == PLUS) {
        result = left.m_value + right.m_value;
    }
    else {
        result = left.m_value - right.m_value;
    }
    std::cout << right.str_repr() << std::endl;

    return result;
}

int main() {
    while (true) {
        string text;

        std::cout << "calc2> " ;

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