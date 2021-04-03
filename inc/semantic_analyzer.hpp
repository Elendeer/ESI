/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 20:27:27
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-04-03 09:13:05
 * @Description  :
*********************************************/
#ifndef INC_SYMBOL_TABLE_BUILDER_HPP_
#define INC_SYMBOL_TABLE_BUILDER_HPP_

#include "node_visitor.hpp"
#include "scoped_symbol_table.hpp"

namespace ESI {

class SemanticAnalyzer : public NodeVisitor {
private :
    ScopedSymbolTable m_build_in_type_scope;
    ScopedSymbolTable * m_p_current_scope;

    // ===== functions =====

    virtual void generic_visit(AST *node);

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
    SemanticAnalyzer(AST * root);
    virtual ~SemanticAnalyzer();

    // Run semantic analyze, may throw exception.
    void analyze();

    void printSymbolTable();
};

} // namespace ESI

#endif
