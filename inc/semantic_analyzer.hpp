/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 20:27:27
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-04-19 20:41:42
 * @Description  :
*********************************************/
#ifndef INC_SYMBOL_TABLE_BUILDER_HPP_
#define INC_SYMBOL_TABLE_BUILDER_HPP_

#include "node_visitor.hpp"
#include "scoped_symbol_table.hpp"
#include "exception.hpp"

namespace ESI {

class SemanticAnalyzer : public NodeVisitor {
private :
    ScopedSymbolTable m_build_in_type_scope;
    ScopedSymbolTable * m_p_current_scope;

    bool m_if_print;

    // ===== functions =====

    virtual void generic_visit(AST *node);

    // Throw a semantic error.
    void error(
        std::string message,
        ErrorCode error_code = ErrorCode::NONE,
        Token token = Token());

    virtual Any visit(AST * node);

    Any visitUnaryOp(AST *node);
    Any visitBinOp(AST *node);
    Any visitNum(AST *node);

    Any visitCompound(AST *node);
    Any visitNoOp();
    Any visitAssign(AST *node);
    Any visitVar(AST *node);

    // S
    Any visitProgram(AST * node);
    Any visitBlock(AST * node);
    Any visitVarDecl(AST * node);
    Any visitType(AST * node);

    Any visitProcedureDecl(AST * node);

public :
    SemanticAnalyzer(AST * root, bool if_print);
    virtual ~SemanticAnalyzer();

    // Run semantic analyze, may throw exception.
    void analyze();

    void printBuildInTypeSymbolTable();
};

// Error thrown by SemanticAnalyzer.
class SemanticError : public Exception {
private :

public :
    SemanticError(
        const std::string & message,
        ErrorCode error_code = ErrorCode::NONE,
        Token token = Token());

    virtual ~SemanticError();

    virtual const std::string what() const ;
};


} // namespace ESI

#endif
