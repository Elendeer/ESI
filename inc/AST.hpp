/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 08:19:49
 * @LastEditors  : ,: Daniel_Elendeer
 * @LastEditTime : ,: 2020-10-25 13:31:23
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
    AST *m_left;
    Token m_token;
    AST *m_right;

public:
    AST(NodeType type = NodeType::BASE, AST *left = NULL, Token token = Token(), AST *right = NULL);

    // Return node type of a AST node
    NodeType getType() const;

    Token getToken() const;
    AST *getLeft() const;
    AST *getRight() const;
    virtual std::vector<AST*> getChildren() const;
    virtual void pushChild(AST* node);

    virtual ~AST();
};

/*********************************************
 * Derived classes
 *********************************************/

class BinOp : public AST {
private:

public:
    BinOp(AST *left, Token op, AST *right);

    virtual ~BinOp();
};

class UnaryOp : public AST {
private:

public:
    // Unary operator modify right-side-operand
    UnaryOp(Token op, AST *right);

    virtual ~UnaryOp();
};

class Num : public AST {
private:
    Token m_token;
    int m_value; // this one looks useless
    NodeType m_nodeType;

public:
    Num(Token token);

    virtual ~Num();
};

/*********************************************
 * @description: Represents a 'BEGIN ... END' block.
*********************************************/
class Compound : public AST {
private:
    std::vector<AST*> m_Children;

public:
    Compound();

    virtual std::vector<AST*> getChildren() const;
    virtual void pushChild(AST* node);

    virtual ~Compound();
};

/*********************************************
 * @description: Assign AST node represents an
 *  assignment statement.
*********************************************/
class Assign : public AST {
private:

public:
    Assign(AST* left, Token op, AST* right);

    virtual ~Assign() = default;
};

/*********************************************
 * @description: The Var node represents a variable.
 * It is constructed out of ID toekn.
*********************************************/
class Var : public AST {
private:
    std::string m_value;

public:
    Var(Token token);

    std::string getVal() const;

    virtual ~Var() = default;
};

/*********************************************
 * @description: NoOp node is used to represent
 *  an empty statement.
*********************************************/
class NoOp : public AST {
private:

public:
    NoOp();

    virtual ~NoOp() = default;
};

} // namespace ESI

#endif
