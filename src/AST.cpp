/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 16:05:51
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-11-19 16:34:25
 * @Description  :
 *********************************************/

// TODO: contral

#include "../inc/AST.hpp"

#include <iostream>

namespace ESI {

/*********************************************
 * AST node base class
 *********************************************/

AST::AST(NodeType type, Token token) : m_nodeType(type), m_token(token) {
}

NodeType AST::getType() const {
    return m_nodeType;
}
Token AST::getToken() const {
    return m_token;
}

AST *AST::getLeft() const {
    if (!m_children.empty())
        return m_children.front();
    else
        return nullptr;
}
AST *AST::getRight() const {
    if (!m_children.empty())
        return m_children.back();
    else
        return nullptr;
}

std::vector<AST *> AST::getChildren() const {
    return m_children;
}

void AST::pushChild(AST *node) {
    m_children.push_back(node);
    return;
}

// Recursively transfer the destruction funtion of the nodes of the
// substree with the object as its root.
AST::~AST() {
    for (auto p : m_children) {
        if (p != nullptr) {
            delete p;
            std::cout << "~AST()" << std::endl;
        }
    }
}

/*********************************************
 * BinOp node
 *********************************************/

BinOp::BinOp(AST *left, Token op, AST *right)
    : AST(NodeType::BINOP, op) {

    m_children.push_back(left);
    m_children.push_back(right);
}

BinOp::~BinOp() {
    std::cout << "~BinOp()" << std::endl;
}

/*********************************************
 * UnaryOp node
 *********************************************/

UnaryOp::UnaryOp(Token op, AST *right)
    : AST(NodeType::UNARYOP, op) {

    m_children.push_back(right);
}

AST *UnaryOp::getLeft() const {
    return nullptr;
}
AST *UnaryOp::getRight() const {
    return m_children.front();
}

UnaryOp::~UnaryOp() {
    std::cout << "~UnaryOp()" << std::endl;
}

/*********************************************
 * Num node
 *********************************************/

Num::Num(Token token)
    : AST(NodeType::NUM, token) {}

Num::~Num() {
    std::cout << "~Num()" << std::endl;
}

/*********************************************
 * Compound node
 *********************************************/

Compound::Compound() : AST(NodeType::COMPOUND, Token()) {

    std::cout << "Compound()" << std::endl;
}

Compound::~Compound() {
    std::cout << "~Compound()" << std::endl;
}

/*********************************************
 * Assign node
 *********************************************/

Assign::Assign(AST *left, Token op, AST *right)
    : AST(NodeType::ASSIGN, op) {

    m_children.push_back(left);
    m_children.push_back(right);
}

Assign::~Assign() {
    std::cout << "~Assign()" << std::endl;
}


/*********************************************
 * Variable node
 *********************************************/

Var::Var(Token token) : AST(NodeType::VAR, token) {
    m_value = token.getStrVal();
}

std::string Var::getVal() const {
    return m_value;
}

Var::~Var() {
    std::cout << "~Var()" << std::endl;
}

/*********************************************
 * No-operation node
*********************************************/

NoOp::NoOp() : AST(NodeType::NOOP, Token()) {}

NoOp::~NoOp() {
    std::cout << "~NoOp()" << std::endl;
}

} // namespace ESI
