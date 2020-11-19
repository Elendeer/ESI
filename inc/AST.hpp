/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 08:19:49
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-11-19 16:22:53
 * @Description  : Abstract syntax tree header
 *********************************************/

// TODO: Reconstruct node classes. Children-functions in
// base class, left-right-funcs in derived classes.

#ifndef AST_HPP_
#define AST_HPP_

#include <string>
#include <vector>

#include "token.hpp"

namespace ESI {


/*********************************************
 * enum types & reflections
*********************************************/

// enum type for nodes of abstract syntax tree
enum class NodeType {
    BASE,
    NUM,
    BINOP,
    UNARYOP,

    COMPOUND,
    ASSIGN,
    VAR,
    NOOP
};
const string NodeTypeString[] = {
    "BASE",
    "NUM",
    "BINOP",
    "UNARYOP",

    "COMPOUND",
    "ASSIGN",
    "VAR",
    "NOOP"
};


/*********************************************
* classes
*********************************************/

/*********************************************
* @description: abstract syntax tree (node) base calss
*********************************************/
class AST {
protected:
    NodeType m_nodeType;
    Token m_token;

    // Holds pointers to children nodes.
    std::vector<AST*> m_children;

public:

    AST(NodeType type, Token token);

    // Return node type of a AST node
    virtual NodeType getType() const;

    // Returns the token in current node.
    virtual Token getToken() const;

    // Returns the pointer to its left child.
    // Apointment:
    // m_children.front() is the left child,
    // m_children.back() is the right child.
    virtual AST *getLeft() const;

    // Returns the pointer to its right child.
    // Apointment:
    // m_children.front() is the left child,
    // m_children.back() is the right child.
    virtual AST *getRight() const;

    // Returns a vector that contains all children of
    // current node.
    virtual std::vector<AST*> getChildren() const;


    virtual void pushChild(AST* node);

    virtual ~AST();
};


/*********************************************
 * Derived classes
 *********************************************/

// Binary operator
class BinOp : public AST {
private:

public:
    // Apointment:
    // m_children.front() is the left child,
    // m_children.back() is the right child.
    BinOp(AST *left, Token op, AST *right);

    virtual ~BinOp();
};

// Unary operator
class UnaryOp : public AST {
private:

public:
    // Unary operator modify right-side-operand.
    // Apointment:
    // Only have a pointor inside m_children, which pointing
    // to the right child.
    UnaryOp(Token op, AST *right);

    // Returns the pointer to its left child, which is nullptr
    // for unary operator.
    virtual AST*getLeft() const;

    // Returns the pointer to its right child.
    virtual AST *getRight() const;

    virtual ~UnaryOp();
};


// Number
class Num : public AST {
private:

public:
    Num(Token token);

    virtual ~Num();
};


// Represents a 'BEGIN ... END' block.
class Compound : public AST {
private:

public:
    // No token inside.
    Compound();

    virtual ~Compound();
};


// Assign AST node represents an
// assignment statement.
class Assign : public AST {
private:

public:
    // Apointment:
    // m_children.front() is the left child,
    // m_children.back() is the right child.
    Assign(AST* left, Token op, AST* right);

    virtual ~Assign();
};


// Variable node represents a variable.
// It is constructed out of ID toekn.
class Var : public AST {
private:
    std::string m_value;

public:
    Var(Token token);

    std::string getVal() const;

    virtual ~Var();
};

// No-operation node is used to represent
// an empty statement.
class NoOp : public AST {
private:

public:
    NoOp();

    virtual ~NoOp();
};

} // namespace ESI

#endif
