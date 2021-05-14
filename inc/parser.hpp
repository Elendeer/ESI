/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 15:45:21
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-05-14 09:14:03
 * @Description  :
*********************************************/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "AST.hpp"
#include "lexer.hpp"
#include "exception.hpp"

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
    void error(
            std::string message,
            ErrorCode error_code = ErrorCode::NONE,
            Token token = Token());

    void eat(TokenType token_type);

    // ===== non-terminals =====


    AST *factor();
    AST *term();
    AST *expr();

    AST *program();
    AST *block();
    std::vector<AST *> declarations();
    std::vector<AST *> variableDeclaration();
    AST * procedureDeclaration();
    AST * typeSpec();

    AST *compoundStatement();
    std::vector<AST *> statementList();
    AST *statement();
    AST *assignmentStatement();
    AST *variable();
    AST *empty();

    std::vector<AST *> formalParameterList();
    std::vector<AST *> formalParameters();
    AST * procedureCallStatement();

    AST * functionDeclaration();
    AST * functionCall();

    AST * readStatement();
    AST * writeStatement();

public:
    // Might throw exception when init.
    Parser(const Lexer &lexer);
    Parser(const Parser &) = default;
    ~Parser();

    // Return a AST node pointor pointing root of AST.
    // May throw exception when Syntax error is met.
    // Return a nullptr if so.
    AST *parse();

    // Return a AST node pointor pointing root of AST.
    // Used by interpreter only when parsing error is met.
    AST * getAstRoot() const ;
};

// Error thrown by Parser.
class ParserError : public Exception {
private :

public :
    ParserError(
        const std::string & message,
        ErrorCode error_code = ErrorCode::NONE,
        Token token = Token());

    virtual ~ParserError();

    virtual const std::string what() const;
};

} // namespace ESI

#endif
