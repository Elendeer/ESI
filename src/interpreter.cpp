/*
 * @Author: Elendeer
 * @Date: 2020-06-05 16:33:54
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-05 20:53:59
 * @Description: file content
 */

#include "../inc/interpreter.hpp"

#include <stdexcept>

namespace ESI {

Interpreter::Interpreter(Parser parser) : m_parser(parser) {}

/**
 * @description: It will transfer a funtion
 * to visit a node depends on type of the node.
 */
int Interpreter::visit(AST* node) {
    if (node->getType() == NUM) {
        return visit_Num(node);
    } else if (node->getType() == BINOP) {
        return visit_BinOp(node);
    } else {
        return 0;
    }
}

void Interpreter::generic_visit(AST* node) {
    throw std::runtime_error((string) "No " + NodeTypeString[node->getType()] + " type method");
}

int Interpreter::visit_BinOp(AST* node) {
    TokenType type = node->getToken().getType();
    if (type == PLUS) {
        return visit(node->getLeft()) + visit(node->getRight());
    } else if (type == MINUS) {
        return visit(node->getLeft()) - visit(node->getRight());
    } else if (type == MUL) {
        return visit(node->getLeft()) * visit(node->getRight());
    } else if (type == DIV) {
        return visit(node->getLeft()) / visit(node->getRight());
    } else {
        return 0;
    }
}

int Interpreter::visit_Num(AST* node) {
    return node->getToken().getVal();
}

int Interpreter::interpret() {
    AST* tree = m_parser.parse();
    int result = visit(tree);

    delete tree;

    return result;
}

}  // namespace ESI
