/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 16:05:51
* @LastEditors  : Elendeer
* @LastEditTime : 2020-06-07 16:30:04
* @Description  :
*********************************************/

#include "../inc/AST.hpp"

namespace ESI {

/*********************************************
 * AST node base class
 *********************************************/
AST::AST(AST* left, Token token, AST* right)
    : m_left(left), m_token(token), m_right(right) {}

AST* AST::getLeft() const {
    return m_left;
}
AST* AST::getRight() const {
    return m_right;
}
Token AST::getToken() const {
    return m_token;
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
BinOp::BinOp(AST* left, Token op, AST* right)
    : AST(left, op, right), m_nodeType(BINOP) {}

NodeType BinOp::getType() const {
    return m_nodeType;
}

BinOp::~BinOp() {}

/*********************************************
 * UnaryOp node
 *********************************************/
UnaryOp::UnaryOp(Token op, AST* right)
    : AST(NULL, op, right), m_nodeType(UNARYOP) {}

NodeType UnaryOp::getType() const {
    return m_nodeType;
}

UnaryOp::~UnaryOp() {}

/*********************************************
 * Num node
 *********************************************/
Num::Num(Token token)
    : AST(NULL, token, NULL),
      m_token(token),
      m_value(token.getVal()),
      m_nodeType(NUM) {}

NodeType Num::getType() const {
    return m_nodeType;
}

Num::~Num() {}

}  // namespace ESI
