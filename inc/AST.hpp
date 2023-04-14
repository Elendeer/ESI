/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 08:19:49
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2023-04-05 20:01:04
 * @Description  : Abstract syntax tree header
 * Base class AST support basic node menegerment.
 * Derived classes support more specific node definition.
 * For example, type of chlidren of derived classes is different
 * from one derived classes to another, so base class will not
 * support specific get function.
 *********************************************/

#ifndef INC_AST_HPP_
#define INC_AST_HPP_

#include <string>
#include <vector>
#include <unordered_map>

#include "token.hpp"
#include "symbol.hpp"

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
    TYPE,

    // ===== =====
    PROCEDURE_DECL,
	PARAM,
    PROCEDURE_CALL,

    STRING,
    BOOLEAN,

    FUNCTION_DECL,
    FUNCTION_CALL,

    READ,
    WRITE,

    IF,
    WHILE
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

    // Return the string representation of m_nodeType.
    std::string getTypeString() const;

    // Return node type of a AST node
    NodeType getType() const;

    // Returns the token in current node.
    Token getToken() const;

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
// All children are statements(statement list).
class Compound : public AST {
private:
public:
    Compound();
    virtual ~Compound();

    // Returns a vector that contains all children of
    // current node, which is a vector of statement.
    // (statement list)
    std::vector<AST *> getChildren() const;

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
    std::string m_var_name;

public:
    Var(Token token);
    virtual ~Var();

    // Return the name of the variable inside the node.
    std::string getVarName() const;
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
    Type(Token type_token);
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

// ===== =====
// ===== =====
// ===== =====

// Parameter node
// No token inside.
class Param : public AST {
private:
	AST * m_var_node;
	AST * m_type_node;

public:
	Param(AST * var_node, AST * type_node);
	virtual ~Param();

	AST * getVarChild() const;
	AST * getTypeChild() const;
};

// Represent a node of declaration of a procedure.
class ProcedureDecl : public AST {
private:
    std::string m_name;
    AST * m_block;
    std::vector<AST *> m_parameters;

public:
    ProcedureDecl(
        std::string name,
        std::vector<AST *> & parameters,
        AST * block);

    virtual ~ProcedureDecl();

    std::string getName() const ;

    // Get parameters.
    // Return a vector contains pointers pointing to
    // parameters.
    std::vector<AST *> getParams() const;

    AST * getBlock() const ;
};

// Token inside should be token of id of procedure name.
// Actual parameters pointers should pointing to nodes on heap.
class ProcedureCall : public AST {
private :
    // procedure name
    std::string m_proc_name;

    // actual parameters
    // All actual parameters are child (node).
    std::vector<AST *> m_actual_param;

    // procedure symbol
    ProcedureSymbol m_proc_symbol;
    Block * m_proc_block;

public :
    ProcedureCall(
        std::string procedure_name,
        std::vector<AST *> & actual_parameters,
        Token name_id_token,
        ProcedureSymbol procudure_symbol = ProcedureSymbol("none", 0));

    virtual ~ProcedureCall();

    std::string getProcedureName() const;
    std::vector<AST *> getActualParameters() const;
    ProcedureSymbol getProcedureSymbol() const;

    void setProcedureSymbol(const ProcedureSymbol & procedure_symbol);

};

// String node
class String : public AST {
private:

public:
    String(Token token);
    ~String();
};

class Boolean : public AST {
private:

public:
    Boolean(Token token);
    ~Boolean();
};

// ===== =====

// Function declaration node.
class FunctionDecl : public AST {
private:
    std::string m_name;
    AST * m_type_node;
    AST * m_block;
    std::vector<AST *> m_parameters;

public:
    FunctionDecl(
        std::string name,
        std::vector<AST *> & parameters,
        AST * type_node,
        AST * block);

    virtual ~FunctionDecl();

    std::string getName() const ;

    // Get parameters.
    // Return a vector contains pointers pointing to
    // parameters.
    std::vector<AST *> getParams() const;

    // Return piontor of the type node.
    AST * getType() const;
    // Return piontor of the block node.
    AST * getBlock() const ;
};

// Function call node.
// Token inside should be token of id of function name.
// Actual parameters pointers should pointing to nodes on heap.
class FunctionCall : public AST {
private:
    // function name
    std::string m_func_name;

    // actual parameters
    // All actual parameters are child (node).
    std::vector<AST *> m_actual_param;

    // procedure symbol
    FunctionSymbol m_func_symbol;
    Block * m_func_block;

public:
    FunctionCall(
        std::string function_name,
        std::vector<AST *> & actual_parameters,
        Token name_id_token,
        FunctionSymbol function_symbol =
            FunctionSymbol("none", 0, SymbolType::NONE));

    virtual ~FunctionCall();

    std::string getFunctionName() const;
    std::vector<AST *> getActualParameters() const;
    FunctionSymbol getFunctionSymbol() const;

    void setFunctionSymbol(const FunctionSymbol & function_symbol);
};


// Node of read statement.
// No token inside.
class Read : public AST {
private:
    std::vector<Var * > m_read_vars;

public:
    Read(
        std::vector<Var *> & read_vars);

    virtual ~Read();

    std::vector<Var *> getReadVars() const;
};

// Node of write statement.
// No token inside.
class Write : public AST {
private:
    // Pointing to the expression which going to be write.
    AST * m_p_expr;
    bool m_is_writeln;

public:
    Write(
        AST * p_expr,
        bool is_writeln);

    virtual ~Write();

    AST * getExpr() const;

    bool isWriteln() const;
};

// Node of if statement.
// No token inside.
class If : public AST {
private:
    // The condition in if.
    AST * m_p_condition;
    // Code body of if statement, may be a compound statement
    // or a single statement.
    AST * m_p_body;
    // Pointing to next If node if still have a else,
    // store nullptr if not.
    AST * m_p_else;

public:
    If(
        AST * p_condition,
        AST * p_body,
        AST * p_else);

    virtual ~If();

    // Return the pointer pointing to the condition expression node.
    AST * getCondition() const;
    // Return a pointer pointing to code body of the if.
    AST * getBody() const;
    // Return nullptr if do not have a eles.
    AST * getElse() const;
};

// Node of while statement.
// No token inside.
class While : public AST {
private:
    AST * m_p_condition;
    AST * m_p_body;

public:
    While(AST * p_condition, AST * p_body);
    virtual ~While();

    AST * getCondition() const ;
    AST * getBody() const ;
};

} // namespace ESI

#endif
