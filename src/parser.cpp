/*
 * @Author: Elendeer
 * @Date: 2020-06-05 16:09:33
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-05 20:52:53
 * @Description: file content
 */

#include "../inc/parser.hpp"

#include <stdexcept>
#include <iostream>

namespace ESI {

Parser::Parser(Lexer lexer) : m_lexer(lexer) {
    m_current_token = m_lexer.get_next_token();
}

void Parser::error() {
    throw std::runtime_error("Invalid syntax");
    // std::cout << "Invalid syntax" << std::endl;
}

/*********************************************
 * @description:
 *  compare the current token type with the passed token
 *  type and if they match then "eat" the current token
 *  and assign the next token to the self.current_token,
 *  otherwise raise an exception.
*********************************************/
void Parser::eat(TokenType token_type) {
    if (m_current_token.getType() == token_type) {
        m_current_token = m_lexer.get_next_token();
    } else {
        error();
    }
}


/*********************************************
 * Arithmetic expressions about
*********************************************/

/*********************************************
 * @description:
 * The next three functions are all parts of parser.
 * Based on grammar.
 * factor : PLUS factor
 *          | MINUS factor
 *          | INTEGER
 *          | LPAREN expr RPAREN
 *          | variable
*********************************************/
AST *Parser::factor() {
    Token token = m_current_token;

    if (m_current_token.getType() == TokenType::PLUS) {
        eat(TokenType::PLUS);
        return new UnaryOp(token, factor());

    } else if (m_current_token.getType() == TokenType::MINUS) {
        eat(TokenType::MINUS);
        return new UnaryOp(token, factor());

    } else if (m_current_token.getType() == TokenType::INTEGER) {
        eat(TokenType::INTEGER);

        return new Num(token);

    } else if (m_current_token.getType() == TokenType::LPAREN){
        eat(TokenType::LPAREN);
        AST *node = expr();
        eat(TokenType::RPAREN);
        return node;

    } else {
        return variable();
    }
}
/**
 * @description: term : factor((MUL | DIV) factor)*
 */
AST *Parser::term() {
    AST *node = factor();

    Token token = m_current_token;
    while (m_current_token.getType() == TokenType::MUL || m_current_token.getType() == TokenType::DIV) {
        if (m_current_token.getType() == TokenType::MUL) {
            eat(TokenType::MUL);
        } else {
            eat(TokenType::DIV);
        }

        node = new BinOp(node, token, factor());
    }

    return node;
}
/**
 * @description: expr : term ((PLUS | MINUS) term)*
 */
AST *Parser::expr() {
    AST *node = term();

    Token token = m_current_token;
    while (m_current_token.getType() == TokenType::PLUS || m_current_token.getType() == TokenType::MINUS) {
        if (m_current_token.getType() == TokenType::PLUS) {
            eat(TokenType::PLUS);
        } else {
            eat(TokenType::MINUS);
        }

        node = new BinOp(node, token, term());
    }

    return node;
}

/*********************************************
 * Programs about
*********************************************/

/*********************************************
 * @description:
 * program : compound_statement DOT
*********************************************/
AST* Parser::program() {
    AST* node = compound_statement();
    eat(TokenType::DOT);

    return node;
}

/*********************************************
 * @description:
 * compound_statement : BEGIN statement_list END
*********************************************/
AST* Parser::compound_statement() {
    eat(TokenType::BEGIN);
    std::vector<AST*> nodes = statement_list();
    eat(TokenType::END);

    AST* root = new Compound();
    for (AST* node : nodes) {
        root->pushChild(node);
    }

    return root;
}

/*********************************************
 * @description:
 * statement_list : statement
 *                | statement SEMI statement_list
*********************************************/
std::vector<AST*> Parser::statement_list() {
    AST* node = statement();

    using std::vector;
    vector<AST*> result;
    result.push_back(node);

    // std::cout << TokenTypeString[(int)m_current_token.getType()] << std::endl;
    while (m_current_token.getType() == TokenType::SEMI) {
        eat(TokenType::SEMI);
        // std::cout << "Eat!" << std::endl;
        result.push_back(statement());
    }

    if (m_current_token.getType() == TokenType::ID) {
        error();
        // return result;
    }

    return result;
}

/*********************************************
 * @description:
 * statement : compound_statement
 *          | assignment_statement
 *          | empty
*********************************************/
AST* Parser::statement() {
    AST* node = NULL;
    if (m_current_token.getType() == TokenType::BEGIN) {
        node = compound_statement();

    } else if (m_current_token.getType() == TokenType::ID) {
        node = assignment_statement();

    } else {
        node = empty();
    }

    return node;
}

/*********************************************
 * @description:
 * assignment_statement : variable ASSIGN expr
*********************************************/
AST* Parser::assignment_statement() {
    AST* left = variable();
    Token token = m_current_token;

    eat(TokenType::ASSIGN);

    AST* right = expr();

    AST* node = new Assign(left, token, right);
    return node;
}

/*********************************************
 * @description:
 * variable : ID
*********************************************/
AST* Parser::variable() {
    AST* node = new Var(m_current_token);
    eat(TokenType::ID);
    return node;
}

/*********************************************
 * @description:
 * An empty production.
*********************************************/
AST* Parser::empty() {
    return new NoOp();
}

AST *Parser::parse() {
    AST* node = program();
    if (m_current_token.getType() != TokenType::eEOF) {
        error();

        delete node;
        return NULL;
    }

    return node;
}

} // namespace ESI
