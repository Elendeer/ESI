/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 15:45:21
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2023-04-14 16:00:45
 * @Description  :
*********************************************/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "AST.hpp"
#include "lexer.hpp"
#include "exception.hpp"

namespace ESI {

// Organizing AST according tokens and grammar.
// Only produce AST, will not manage to delete it except errors are met.
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

    //  Compare the current token type with the passed token
    //  type and if they match then "eat" the current token
    //  and assign the next token to the this->m_current_token,
    //  otherwise throw an exception.
    //
    //  Might throw exceptions in Lexer::error() or
    //  Parser::error().
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
    AST * arrayType();

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

    AST * relationalExpr();
    AST * logicalExpr();

    AST * ifStatement();
    AST * whileStatement();

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
