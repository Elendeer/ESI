/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 16:22:37
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-05-08 17:05:25
 * @Description  :
*********************************************/

#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

#include "parser.hpp"
#include "node_visitor.hpp"
#include "scoped_symbol_table.hpp"
#include "call_stack.hpp"

#include <map>

namespace ESI {

// Interpreter is a node-visitor
class Interpreter : public NodeVisitor {
private:
    CallStack m_call_stack;
    bool m_if_print_stack;


    // It will transfer a funtion
    // to visit a node depends on type of the node.
    virtual Any visit(AST *node);

    virtual void generic_visit(AST *node);

    Any visitUnaryOp(AST *node);
    Any visitBinOp(AST *node);
    Any visitNum(AST *node);

    Any visitCompound(AST *node);
    Any visitNoOp();
    Any visitAssign(AST *node);
    Any visitVar(AST *node);

    Any visitProgram(AST * node);
    Any visitBlock(AST * node);
    Any visitVarDecl(AST * node);
    Any visitType(AST * node);

    Any visitProcedureDecl(AST * node);
    Any visitProcedureCall(AST * node);

    Any visitString(AST * node);
    Any visitBoolean(AST * node);

    Any visitFunctionDecl(AST * node);

public:
    Interpreter(AST * root, bool if_print_stack);
    virtual ~Interpreter();

    // Interpret the source code by walking through the AST.
    // May throw exception.
    void interpret();

    void printStack();
};

// Error throw by Interpreter.
class InterpreterError : public Exception {
private :

public:
    InterpreterError(const std::string & message);
    virtual ~InterpreterError();

    virtual const std::string what() const ;
};

} // namespace ESI

#endif
