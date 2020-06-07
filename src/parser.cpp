/*
 * @Author: Elendeer
 * @Date: 2020-06-05 16:09:33
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-05 20:52:53
 * @Description: file content
 */

#include "../inc/parser.hpp"

#include <stdexcept>

namespace ESI {

Parser::Parser(Lexer lexer) : m_lexer(lexer) {
    m_current_token = m_lexer.get_next_token();
}

void Parser::error() { throw std::runtime_error("Invalid syntax"); }

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
    } else {
        error();
    }
}
/**
 * @description: The next three functions are all parts of parser.
 * Based on grammar.
 * factor : (PLUS | MINUS) factor | INTEGER | LPAREN expr RPAREN
 */
AST *Parser::factor() {
    Token token = m_current_token;

    if (m_current_token.getType() == PLUS || m_current_token.getType() == MINUS) {

        if (m_current_token.getType() == PLUS) {
            eat(PLUS);
        } else {
            eat(MINUS);
        }

        return new UnaryOp(token, factor());

    } else if (m_current_token.getType() == INTEGER) {
        eat(INTEGER);

        return new Num(token);

    } else {
        eat(LPAREN);
        AST *node = expr();
        eat(RPAREN);
        return node;
    }
}
/**
 * @description: term : factor((MUL | DIV) factor)*
 */
AST *Parser::term() {
    AST *node = factor();

    Token token = m_current_token;
    while (m_current_token.getType() == MUL || m_current_token.getType() == DIV) {
        if (m_current_token.getType() == MUL) {
            eat(MUL);
        } else {
            eat(DIV);
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
    while (m_current_token.getType() == PLUS || m_current_token.getType() == MINUS) {
        if (m_current_token.getType() == PLUS) {
            eat(PLUS);
        } else {
            eat(MINUS);
        }

        node = new BinOp(node, token, term());
    }

    return node;
}

AST *Parser::parse() { return expr(); }

} // namespace ESI
