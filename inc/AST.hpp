/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 08:19:49
* @LastEditors  : Elendeer
* @LastEditTime : 2020-06-07 15:11:06
 * @Description  : Abstract syntax tree header
 *********************************************/

#ifndef AST_HPP_
#define AST_HPP_

#include <string>

#include "token.hpp"

namespace ESI {

// enum type for nodes of abstract syntax tree
enum NodeType { NUM, BINOP, UNARYOP };
const string NodeTypeString[] = {"NUM", "BINOP", "UNARYOP"};

/**
 * @description: abstract syntax tree (node) calss
 *
 */
class AST {
   protected:
    AST* m_left;
    Token m_token;
    AST* m_right;

   public:
    AST(AST* left = NULL, Token token = Token(), AST* right = NULL);

    /**
     * @description: Return the type of node according to polymorphism.
     */
    virtual NodeType getType() const = 0;

    Token getToken() const;
    AST* getLeft() const;
    AST* getRight() const;

    virtual ~AST();
};

/*********************************************
 * Derived classes
 *********************************************/

class BinOp : public AST {
   private:
    NodeType m_nodeType;

   public:
    BinOp(AST* left, Token op, AST* right);

    virtual NodeType getType() const;

    virtual ~BinOp();
};

class UnaryOp : public AST {
private:
    NodeType m_nodeType;

public:
    // Unary operator modify rvalue
    UnaryOp(Token op, AST* right);

    virtual NodeType getType() const;

    virtual ~UnaryOp();
};

class Num : public AST {
   private:
    Token m_token;
    int m_value;  // this one looks useless
    NodeType m_nodeType;

   public:
    Num(Token token);

    virtual NodeType getType() const;

    virtual ~Num();
};

}  // namespace ESI

#endif
