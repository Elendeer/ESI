/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 16:22:37
 * @LastEditors  : ,: Daniel_Elendeer
 * @LastEditTime : ,: 2020-10-25 13:21:18
* @Description  :
*********************************************/

#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

// #include"../inc/AST.hpp"
#include "../inc/parser.hpp"

#include <map>

namespace ESI {

// As a abstract base class
class NodeVisitor {
protected:
    virtual void generic_visit(AST *node) = 0;

public:
    virtual int visit(AST *node) = 0;
};

// interpreter is a node-visitor
class Interpreter : public NodeVisitor {
private:
    Parser m_parser;
    std::map<std::string, int> m_GLOBAL_SCOPE;

    int visit_UnaryOp(AST *node);
    int visit_BinOp(AST *node);
    int visit_Num(AST *node);

    void visit_Compound(AST *node);
    void visit_NoOp();
    void visit_Assign(AST *node);
    int visit_Var(AST *node);

    virtual void generic_visit(AST *node);

public:
    Interpreter(Parser parser);

    virtual int visit(AST *node);

    void interpret();

    void printScope();
};
} // namespace ESI

#endif
