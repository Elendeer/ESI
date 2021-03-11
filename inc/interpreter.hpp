/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 16:22:37
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-08 21:17:08
 * @Description  :
*********************************************/

#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

#include "parser.hpp"
#include "node_visitor.hpp"

#include <map>

namespace ESI {

// Interpreter is a node-visitor
class Interpreter : public NodeVisitor {
private:
    std::map<std::string, Any> m_GLOBAL_SCOPE;

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

    // virtual void generic_visit(AST *node);

public:
    Interpreter(AST * root);
    virtual ~Interpreter();

    // It will transfer a funtion
    // to visit a node depends on type of the node.
    virtual Any visit(AST *node);

    void interpret();

    void printScope();
};

} // namespace ESI

#endif
