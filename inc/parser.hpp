/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 15:45:21
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-11-21 10:03:34
 * @Description  :
*********************************************/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "AST.hpp"
#include "lexer.hpp"

namespace ESI {

class Parser {
private:
    Lexer m_lexer;
    Token m_current_token;

    // A pointer point to root node of AST.
    // Exist since the first memory allocate.
    AST *m_tmp_root;

public:
    Parser(const Lexer &lexer);
    Parser(const Parser &) = default;

    void error();

    void eat(TokenType token_type);

    // non-terminals

    AST *factor();
    AST *term();
    AST *expr();

    AST *program();
    AST *compound_statement();
    std::vector<AST *> statement_list();
    AST *statement();
    AST *assignment_statement();
    AST *variable();
    AST *empty();

    AST *parse();

    AST *getTmpRoot() const;
};

} // namespace ESI

#endif
