/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 20:27:27
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-15 22:09:35
 * @Description  :
*********************************************/
#ifndef INC_SYMBOL_TABLE_BUILDER_HPP_
#define INC_SYMBOL_TABLE_BUILDER_HPP_

#include "node_visitor.hpp"
#include "symbol_table.hpp"

namespace ESI {

class SymbolTableBuilder : public NodeVisitor {
private :
    SymbolTable m_table;
    virtual void generic_visit(AST *node);

    virtual Any visit(AST * node);

    Any visit_UnaryOp(AST *node);
    Any visit_BinOp(AST *node);
    Any visit_Num(AST *node);

    Any visit_Compound(AST *node);
    Any visit_NoOp();
    Any visit_Assign(AST *node);
    Any visit_Var(AST *node);

    Any visitProgram(AST * node);
    Any visitBlock(AST * node);
    Any visitVarDecl(AST * node);
    Any visitType(AST * node);

    Any visitProcedureDecl(AST * node);

public :
    SymbolTableBuilder(AST * root);
    virtual ~SymbolTableBuilder();

    void build();
    void printSymbolTable();
};

} // namespace ESI

#endif