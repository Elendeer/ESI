/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 16:05:51
 * @LastEditors  : ,: Daniel_Elendeer
 * @LastEditTime : ,: 2020-10-25 13:34:06
 * @Description  :
 *********************************************/

#include <iostream>
#include "../inc/AST.hpp"

namespace ESI {

/*********************************************
 * AST node base class
 *********************************************/
AST::AST(NodeType type, AST *left, Token token, AST *right)
    : m_nodeType(type),
      m_left(left),
      m_token(token),
      m_right(right) {}

NodeType AST::getType() const {
    return m_nodeType;
}

Token AST::getToken() const {
    return m_token;
}
AST *AST::getLeft() const {
    return m_left;
}
AST *AST::getRight() const {
    return m_right;
}
/*********************************************
 * @description: Return a empty vector.
*********************************************/
std::vector<AST *> AST::getChildren() const {
    return std::vector<AST *>();
}

/*********************************************
 * @description: Do nothing.
*********************************************/
void AST::pushChild(AST* node) {
    std::cout << node << std::endl;
    return;
}

// recursively transfer the destruction funtion of the nodes of the
// substree with the object as its root.
AST::~AST() {
    if (m_left != NULL) {
        delete m_left;
    }
    if (m_right != NULL) {
        delete m_right;
    }
}

/*********************************************
 * BinOp node
 *********************************************/
BinOp::BinOp(AST *left, Token op, AST *right)
    : AST(NodeType::BINOP, left, op, right) {}

BinOp::~BinOp() {}

/*********************************************
 * UnaryOp node
 *********************************************/
UnaryOp::UnaryOp(Token op, AST *right)
    : AST(NodeType::UNARYOP, NULL, op, right) {}

UnaryOp::~UnaryOp() {}

/*********************************************
 * Num node
 *********************************************/
Num::Num(Token token)
    : AST(NodeType::NUM, NULL, token, NULL),
      m_token(token),
      m_value(token.getVal()) {}

Num::~Num() {}

/*********************************************
 * Compound node
 *********************************************/
Compound::Compound() : AST(NodeType::COMPOUND) {}

std::vector<AST *> Compound::getChildren() const {
    return m_Children;
}

void Compound::pushChild(AST *node) {
    m_Children.push_back(node);
}

Compound::~Compound() {
    // Don't need to delete the vector,
    // it will be deleted when the object is deleted.
    for (AST *p : m_Children) {
        delete p;
    }
}

/*********************************************
 * Assign node
 *********************************************/
Assign::Assign(AST *left, Token op, AST *right) : AST(NodeType::ASSIGN, left, op, right) {}

/*********************************************
 * Variable node
 *********************************************/
Var::Var(Token token) : AST(NodeType::VAR, NULL, token, NULL) {
    m_value = token.getStrVal();
}

std::string Var::getVal() const {
    return m_value;
}

/*********************************************
 * No-operation node
*********************************************/
NoOp::NoOp() : AST() {}

} // namespace ESI
