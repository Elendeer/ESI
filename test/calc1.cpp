// Token types

// EOF (end-of-file) token is used to indicate that
// there is no more input left for lexical analysiss
#include<iostream>
// #include<vector>
#include<string>


using std::string;

string repr(int num) {
    // convert a interger to a string representation
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
    string m_type;
    int m_value;
    // token types : interger, plus, or EOF
    // token value : 0-9, '+', or None
public:
    Token(string type = "None", int value = 0);
    Token(const Token& obj) = default;
    // 注意默认构造函数

    string str_repr();
    // String representation of the class instance.
    // Examples:
    // Token(INTERGER, 3)
    // Token(PLUS, '+')

    friend class Interpreter;
};
Token::Token(string type, int value) : m_type(type), m_value(value) {}

string Token::str_repr() {
    string type = m_type;
    string value = repr(m_value);
    return "Token(" + type + ", " + value + ")";
}

/**************************************/

class Interpreter {
private:
    int m_pos; // index of m_text
    string m_text;
    Token m_current_token;

public:
    Interpreter(string text);

    void error();
    Token get_next_token();
    void eat(string token_type);
    int expr();
};
Interpreter::Interpreter(string text) : m_text(text), m_pos(0) {}
// text : client string input, e.g. "3+5"

void Interpreter::error() {
    throw "Error parsing input";
}

Token Interpreter::get_next_token() {
    /*
    Lexical analyzer (also know as scanner or tokenizer)
    This function is responsible for breaking a sentance
    apart into tokens. One token at a time.
    */
    string text = m_text;

    if (m_pos > text.length() - 1) {
        // if index past the end of the m_text
        return Token("EOF", -1);
    }

    char curren_char = text[m_pos];

    if (curren_char >= '0' && curren_char <= '9') {
        // if curren_char is digit
        int value = (int)curren_char - '0';
        //highlight! curren_char is a char!
        Token token("INTERGER", value);
        ++m_pos;
        return token;
    }

    if (curren_char == '+') {
        Token token("PLUS", (int)curren_char);
        ++m_pos;
        return token;
    }

    error();
    Token token("NONE", -1);
    return token;
    // error后面的两句安慰vsc用的，其实执行不到此处
}

void Interpreter::eat(string token_type) {
    // compare the current token type with the passed token
    // type and if they match then "eat" the current token
    // and assign the next token to the self.current_token,
    // otherwise raise an exception.
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
    */
    // set current token to the first token taken from the input
    m_current_token = get_next_token();

    // we expect the current token to be a single-digit integer
    Token left = m_current_token;
    eat("INTERGER");

    // we expect the current token to be a '+' token
    Token op = m_current_token;
    eat("PLUS");

    // we expect the current token to be a single-digit integer
    Token right = m_current_token;
    eat("INTERGER");
    //after the above call the self.current_token is set to
    // EOF token

    // at this point INTEGER PLUS INTEGER sequence of tokens
    // has been successfully found and the method can just
    // return the result of adding two integers, thus
    // effectively interpreting client input
    int result = left.m_value + right.m_value;
    return result;
}

int main() {
    while (true) {
        string text;

        std::cout << "calc1> " ;

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