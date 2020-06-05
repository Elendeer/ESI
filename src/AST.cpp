/*
 * @Author: Elendeer
 * @Date: 2020-06-05 16:05:51
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-05 20:54:44
 * @Description: file content
 */

#include "../inc/AST.hpp"


namespace ESI {

AST::AST(AST* left, Token token, AST* right)
    : m_left(left), m_token(token), m_right(right) {}

AST* AST::getLeft() const {
    return m_left;
}
AST* AST::getRight() const {
    return m_right;
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

BinOp::BinOp(AST* left, Token op, AST* right)
    : AST(left, op, right), m_nodeType(BINOP) {}

NodeType BinOp::getType() const {
    return m_nodeType;
}

Token BinOp::getToken() const {
    return m_token;
}

Num::Num(Token token)
    : AST(NULL, token, NULL),
      m_token(token),
      m_value(token.getVal()),
      m_nodeType(NUM) {}

NodeType Num::getType() const {
    return m_nodeType;
}

Token Num::getToken() const {
    return m_token;
}

}  // namespace ESI
