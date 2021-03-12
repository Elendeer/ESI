/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 20:27:27
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-12 09:18:55
 * @Description  :
*********************************************/

#include "node_visitor.hpp"
#include "symbol_table.hpp"

namespace ESI {

class SymbolTableBuilder : public NodeVisitor {
private :
    SymbolTable m_table;
    virtual void generic_visit(AST *node);

public :
    SymbolTableBuilder(AST * root);
    virtual ~SymbolTableBuilder();

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
};

} // namespace ESI