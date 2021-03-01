/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 15:45:21
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-02-18 15:05:31
 * @Description  :
*********************************************/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "AST.hpp"
#include "lexer.hpp"

namespace ESI {

// Organizing AST according tokens and grammar.
// Only produce AST, will not manager to delete it.
class Parser {
private:
    Lexer m_lexer;
    Token m_current_token;
    AST * mp_ast_root;

    // ===== Functions =====

    // Throw a exception of invalid syntex.
    void error();

    void eat(TokenType token_type);

    // ===== non-terminals =====


    AST *factor();
    AST *term();
    AST *expr();

    AST *program();
    AST *block();
    std::vector<AST *> declarations();
    std::vector<AST *> variableDeclaration();
    AST * typeSpec();

    AST *compoundStatement();
    std::vector<AST *> statementList();
    AST *statement();
    AST *assignmentStatement();
    AST *variable();
    AST *empty();

public:
    // Might throw exception when init.
    Parser(const Lexer &lexer);
    Parser(const Parser &) = default;
    ~Parser();

    // Return a AST node pointor pointing root of AST.
    // May throw exception when Syntax error is met.
    AST *parse();

    // Return a AST node pointor pointing root of AST.
    // Used by interpreter only when parsing error is met.
    AST * getAstRoot() const ;
};

} // namespace ESI

#endif
