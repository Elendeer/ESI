/*
 * @Author: Elendeer
 * @Date: 2020-05-30 00:38:20
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-04 22:29:03
 * @Description: start to use AST
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
const string TokenTypeString[] = {
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

/**********************************************
 * LEXER
 **********************************************/

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

    TokenType getType() const {
        return m_type;
    }
    int getVal() {
        return m_value;
    }
    // friend class Lexer;
    // friend class Parser;
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
    string type = TokenTypeString[m_type];
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

/**********************************************
 * PARSER
 **********************************************/

// enum type for nodes of abstract
enum NodeType {
    NUM, BINOP
};
string NodeTypeString[] = {
    "NUM", "BINOP"
};

class AST {
protected:
    AST* m_left, *m_right;
    Token m_token;

public:
    AST(AST* left = NULL, Token token = Token(),  AST* right = NULL);

    /**
     * @description: Return the type of node according to polymorphism.
     * NUM / BINOP
     */
    virtual NodeType getType() const = 0;

    virtual Token getToken() const = 0;
    virtual AST* getLeft() const;
    virtual AST* getRight() const;

    virtual ~AST();
};
AST::AST(AST* left, Token token, AST* right) : m_left(left), m_token(token), m_right(right) {}

AST* AST::getLeft() const {
    return m_left;
}
AST* AST::getRight() const {
    return m_right;
}

// recursively transfer the destruction funtion of the nodes of the
// substree with the object as its root.
AST::~AST() {
    if (m_left != NULL) {
        delete m_left;
    }
    if (m_right != NULL) {
        delete m_right;
    }
}


class BinOp : public AST {
private:
    NodeType m_nodeType;
public:
    BinOp(AST* left, Token op, AST* right);

    virtual NodeType getType() const;
    virtual Token getToken() const;
};
BinOp::BinOp(AST* left, Token op, AST* right) : AST(left, op, right), m_nodeType(BINOP) {}

NodeType BinOp::getType() const {
    return m_nodeType;
}

Token BinOp::getToken() const {
    return m_token;
}


class Num : public AST {
private:
    Token m_token;
    int m_value; // this one looks useless
    NodeType m_nodeType;

public:
    Num(Token token);

    virtual NodeType getType() const;
    virtual Token getToken() const;
};
Num::Num(Token token) : AST(NULL, token, NULL), m_token(token), m_value(token.getVal()), m_nodeType(NUM) {}

NodeType Num::getType() const {
    return m_nodeType;
}

Token Num::getToken() const {
    return m_token;
}


class Parser {
private:
    Lexer m_lexer;
    Token m_current_token;
public:
    Parser(Lexer lexer);
    Parser(const Parser&) = default;

    void error();

    void eat(TokenType token_type);

    //non-terminals
    AST* factor();
    AST* term();
    AST* expr();
    AST* parse();
};
Parser::Parser(Lexer lexer) : m_lexer(lexer) {
    m_current_token = m_lexer.get_next_token();
}

void Parser::error() {
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
void Parser::eat(TokenType token_type) {
    if (m_current_token.getType() == token_type) {
        m_current_token = m_lexer.get_next_token();
    }
    else {
        error();
    }
}
/**
 * @description: The next three functions are all parts of parser.
 * Based on grammar.
 * factor : INTEGER | LPAREN expr RPAREN
 */
AST* Parser::factor() {
    Token token = m_current_token;
    if (m_current_token.getType() == INTEGER) {
        eat(INTEGER);
        return new Num(token);
    }
    else {
        eat(LPAREN);
        AST* node = expr();
        eat(RPAREN);
        return node;
    }
}
/**
 * @description: term : factor((MUL | DIV) factor)*
 */
AST* Parser::term() {

    AST* node = factor();

    Token token = m_current_token;
    while (m_current_token.getType() == MUL || m_current_token.getType() == DIV) {
        if (m_current_token.getType() == MUL) {
            eat(MUL);
        }
        else {
            eat(DIV);
        }

        node = new BinOp(node, token, factor());
    }

    return node;
}
/**
 * @description: expr : term ((PLUS | MINUS) term)*
 */
AST* Parser::expr() {

    AST* node = term();

    Token token = m_current_token;
    while (m_current_token.getType() == PLUS || m_current_token.getType() == MINUS) {
        if (m_current_token.getType() == PLUS) {
            eat(PLUS);
        }
        else {
            eat(MINUS);
        }

        node = new BinOp(node, token, term());
    }

    return node;
}

AST* Parser::parse() {
    return expr();
}

/**********************************************
 * INTERPRETER
 **********************************************/

// As a virtual base class
class NodeVisitor {
protected:
    virtual void generic_visit(AST* node) = 0;

public:
    virtual int visit(AST* node) = 0;
};

// interpreter is a node-visitor
class Interpreter : public NodeVisitor {
private:
    Parser m_parser;

    int visit_BinOp(AST* node);
    int visit_Num(AST* node);

    virtual void generic_visit(AST* node);

public:
    Interpreter(Parser parser);

    virtual int visit(AST* node);

    int interpret();
};
Interpreter::Interpreter(Parser parser) : m_parser(parser) {}

/**
 * @description: It will transfer a funtion
 * to visit a node depends on type of the node.
 */
int Interpreter::visit(AST* node) {
    if (node->getType() == NUM) {
        return visit_Num(node);
    }
    if (node->getType() == BINOP) {
        return visit_BinOp(node);
    }
}

void Interpreter::generic_visit(AST* node) {
    throw std::runtime_error((string)"No " + NodeTypeString[node->getType()] + " type method");
}

int Interpreter::visit_BinOp(AST* node) {
    TokenType type = node->getToken().getType();
    if (type == PLUS) {
        return visit(node->getLeft()) + visit(node->getRight());
    }
    else if (type == MINUS) {
        return visit(node->getLeft()) - visit(node->getRight());
    }
    else if (type == MUL) {
        return visit(node->getLeft()) * visit(node->getRight());
    }
    else if (type == DIV) {
        return visit(node->getLeft()) / visit(node->getRight());
    }
}

int Interpreter::visit_Num(AST* node) {
    return node->getToken().getVal();
}

int Interpreter::interpret() {
    AST* tree = m_parser.parse();
    int result = visit(tree);

    delete tree;

    return result;
}


int main() {
    while (true) {
        string text;

        std::cout << "espi> " ;
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
            Parser parser(lexer);
            Interpreter interpreter(parser);
            result = interpreter.interpret();
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