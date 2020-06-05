/*
 * @Author: Elendeer
 * @Date: 2020-06-05 08:19:49
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-05 20:11:01
 * @Description: file content
 */

#ifndef AST_HPP_
#define AST_HPP_

#include <string>

#include "token.hpp"

namespace ESI {

// enum type for nodes of abstract
enum NodeType { NUM, BINOP };
const string NodeTypeString[] = {"NUM", "BINOP"};

/**
 * @description: abstract syntax tree (node) calss
 * and is derived classes BinOp / Num
 */
class AST {
   protected:
    AST *m_left;
    Token m_token;
    AST *m_right;

   public:
    AST(AST* left = NULL, Token token = Token(), AST* right = NULL);

    /**
     * @description: Return the type of node according to polymorphism.
     * NUM / BINOP
     */
    virtual NodeType getType() const = 0;

    virtual Token getToken() const = 0;
    virtual AST* getLeft() const;
    virtual AST* getRight() const;

    virtual ~AST();
};

class BinOp : public AST {
   private:
    NodeType m_nodeType;

   public:
    BinOp(AST* left, Token op, AST* right);

    virtual NodeType getType() const;
    virtual Token getToken() const;
};

class Num : public AST {
   private:
    Token m_token;
    int m_value;  // this one looks useless
    NodeType m_nodeType;

   public:
    Num(Token token);

    virtual NodeType getType() const;
    virtual Token getToken() const;
};

}  // namespace ESI

#endif
