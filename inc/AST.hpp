/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 08:19:49
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-02-16 13:27:18
 * @Description  : Abstract syntax tree header
 *********************************************/

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
    NOOP,

    PROGRAM,
    BLOCK,
    VAR_DECL,
    TYPE
};

const static std::string NodeTypeString[] = {
    "BASE",
    "NUM",
    "BINOP",
    "UNARYOP",

    "COMPOUND",
    "ASSIGN",
    "VAR",
    "NOOP",

    "PROGRAM",
    "BLOCK",
    "VAR_DECL",
    "TYPE"
};
/*********************************************
* classes
*********************************************/

// Abstract syntax tree (node) base calss
class AST {
protected:
    NodeType m_nodeType;
    Token m_token;

    // Holds pointers to children nodes.
    std::vector<AST *> m_children;

public:
    AST(NodeType type, Token token);
    virtual ~AST();

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
    virtual std::vector<AST *> getChildren() const;

    virtual void pushChild(AST *node);
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
    virtual ~UnaryOp();

    // Returns the pointer to its left child, which is nullptr
    // for unary operator.
    virtual AST *getLeft() const;

    // Returns the pointer to its right child.
    virtual AST *getRight() const;
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
    Assign(AST *left, Token op, AST *right);
    virtual ~Assign();
};

// Variable node represents a variable.
// It is constructed out of ID toekn.
class Var : public AST {
private:
    std::string m_value;

public:
    Var(Token token);
    virtual ~Var();

    std::string getVal() const;
};

// The Block AST node holds declarations
// and a compound statement.
class Block : public AST {
private:
public:
    // Appointment :
    // Every elements except the last one in m_children
    // are variable declaration nodes.
    // m_children.back() is compound statement node.
    // No Token inside.
    Block(std::vector<AST *> & declarations, AST *compound_statement);
    virtual ~Block();
};

// The Program AST node represents a program
// and will be root node.
class Program : public AST {
private:
    std::string m_name;

public:
    // Appointment :
    // m_children.front() is block node.
    // No Token inside.
    Program(std::string name, AST *block);
    virtual ~Program();
};

// The VarDecl AST node represents a variable declaration.
// It holds a variable node and a type node.
class VarDecl : public AST {
private:
public:
    // Appointment :
    // m_children.front() is variable node.
    // m_children.back() is type node.
    // No Token inside.
    VarDecl(AST *variable, AST *type);
    virtual ~VarDecl();
};

// The Type AST node represents a variable type.
class Type : public AST {
private:
    // m_value is the value of Token inside.
    std::string m_value;

public:
    Type(Token type);
    virtual ~Type();

    std::string getVal() const;
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
