/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 08:19:49
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-12 10:28:48
 * @Description  : Abstract syntax tree header
 * Base class AST support basic node menegerment.
 * Derived classes support more specific node definition.
 *********************************************/

#ifndef AST_HPP_
#define AST_HPP_

#include <string>
#include <vector>
#include <unordered_map>

#include "token.hpp"

namespace ESI {

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


// Abstract syntax tree (node) base calss
class AST {
protected:
    NodeType m_nodeType;
    Token m_token;

    // Holds pointers to children nodes.
    std::vector<AST *> m_children;

    static const std::unordered_map<NodeType, std::string> map_node_type_string;

public:
    AST(NodeType type, Token token);
    virtual ~AST();

    std::string getTypeString() const;

    // Return node type of a AST node
    virtual NodeType getType() const;

    // Returns the token in current node.
    virtual Token getToken() const;

    // Returns a vector that contains all children of
    // current node.
    virtual std::vector<AST *> getChildren() const;
};

/*********************************************
 * Derived classes
 * All private pointers inside derived classes are
 * only alias of children pointer, don't need to new and/or delete.
 *********************************************/

// Binary operator
// Left and right pointer pointing to operands.
class BinOp : public AST {
private:
    AST * m_left;
    AST * m_right;

public:
    BinOp(AST *left, Token op, AST *right);
    virtual ~BinOp();

    AST * getLeft() const;
    AST * getRight() const;
};

// Unary operator
// Unary operator modify right-side-operand.
// Have only one child.
// Operator token inside.
class UnaryOp : public AST {
private:
    AST * m_expr;

public:
    UnaryOp(Token op, AST * expr);
    virtual ~UnaryOp();

    AST * getExpr() const;
};

// Number
class Num : public AST {
private:
public:
    Num(Token token);
    virtual ~Num();
};

// Represents a 'BEGIN ... END' block.
// No token inside.
// All children are statements.
class Compound : public AST {
private:
public:
    Compound();
    virtual ~Compound();

    void pushChild(AST * node);
};

// Assign AST node represents an
// assignment statement.
// In general, left child will be a variable, right child will
// be a expression.
class Assign : public AST {
private:
    AST * m_left;
    AST * m_right;
public:
    Assign(AST *left, Token op, AST *right);
    virtual ~Assign();

    AST * getLeft() const;
    AST * getRight() const;
};

// Variable node represents a variable.
// It is constructed out of ID token.
class Var : public AST {
private:
    std::string m_value;

public:
    Var(Token token);
    virtual ~Var();

    // Return the name of the variable inside the node.
    std::string getVal() const;
};

// The Block AST node holds declarations
// and a compound statement.
class Block : public AST {
private:
    std::vector<AST *> m_declarations;
    AST * m_compound_statement;

public:
    Block(std::vector<AST *> & declarations, AST *compound_statement);
    virtual ~Block();

    std::vector<AST *> getDeclarations() const;
    AST * getCompoundStatement() const;

};

// The Program AST node represents a program
// and will be root node.
class Program : public AST {
private:
    std::string m_name;
    AST * m_block;

public:
    Program(std::string name, AST *block);
    virtual ~Program();

    std::string getName() const;
    AST * getBlock() const;
};

// The VarDecl AST node represents a variable declaration.
// It holds a variable node and a type node.
// No token inside.
class VarDecl : public AST {
private:
    AST * m_variable_child;
    AST * m_type_child;
public:
    VarDecl(AST *variable, AST *type);
    virtual ~VarDecl();

    AST * getVarChild() const;
    AST * getTypeChild() const;
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
