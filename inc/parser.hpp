/*
 * @Author: Elendeer
 * @Date: 2020-06-05 15:45:21
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-05 18:38:27
 * @Description: file content
 */

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "AST.hpp"
#include "lexer.hpp"

namespace ESI {

class Parser {
   private:
    Lexer m_lexer;
    Token m_current_token;

   public:
    Parser(Lexer lexer);
    Parser(const Parser&) = default;

    void error();

    void eat(TokenType token_type);

    // non-terminals
    AST* factor();
    AST* term();
    AST* expr();
    AST* parse();
};

} // namespace ESI

#endif
