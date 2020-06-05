/*
 * @Author: Elendeer
 * @Date: 2020-06-05 16:22:37
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-05 18:38:47
 * @Description: file content
 */

#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

// #include"../inc/AST.hpp"
#include"../inc/parser.hpp"


namespace ESI {

// As a virtual base class
class NodeVisitor {
protected:
    virtual void generic_visit(AST* node) = 0;

public:
    virtual int visit(AST* node) = 0;
};

// interpreter is a node-visitor
class Interpreter : public NodeVisitor {
private:
    Parser m_parser;

    int visit_BinOp(AST* node);
    int visit_Num(AST* node);

    virtual void generic_visit(AST* node);

public:
    Interpreter(Parser parser);

    virtual int visit(AST* node);

    int interpret();
};
} // namepace ESI

#endif
