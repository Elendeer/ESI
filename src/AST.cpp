/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 16:05:51
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-04-23 09:19:19
 * @Description  :
 *********************************************/

// TODO: contral

#include "../inc/AST.hpp"

#include <iostream>

using std::string;
using std::vector;
using std::unordered_map;

namespace ESI {

const unordered_map<NodeType, std::string> AST::map_node_type_string {
    {NodeType::BASE, "BASE"},
    {NodeType::NUM, "NUM"},
    {NodeType::BINOP, "BINOP"},
    {NodeType::UNARYOP, "UNARYOP"},

    {NodeType::COMPOUND, "COMPOUND"},
    {NodeType::ASSIGN, "ASSIGN"},
    {NodeType::VAR, "VAR"},
    {NodeType::NOOP, "NOOP"},

    {NodeType::PROGRAM, "PROGRAM"},
    {NodeType::BLOCK, "BLOCK"},
    {NodeType::VAR_DECL, "VAR_DECL"},
    {NodeType::TYPE, "TYPE"},

    {NodeType::PROCEDURE_DECL, "PORCEDURE_DECL"}
};

/*********************************************
 * AST node base class
 *********************************************/

AST::AST(NodeType type, Token token) : m_nodeType(type), m_token(token) {
}

// Recursively transfer the destruction funtion of the nodes of the
// substree with the object as its root.
AST::~AST() {
    // std::cout << "AST node deleted : ";
    // m_token.print_str_repr();
    // std::cout << std::endl;

    for (auto p : m_children) {
        if (p != nullptr) {
            delete p;
            // std::cout << "~AST()" << std::endl;
        }
    }
}

// ===== =====

string AST::getTypeString() const {
    return map_node_type_string.at(m_nodeType);
}

NodeType AST::getType() const {
    return m_nodeType;
}
Token AST::getToken() const {
    return m_token;
}

/*********************************************
 * BinOp node
 *********************************************/

BinOp::BinOp(AST *left, Token op, AST *right)
    : AST(NodeType::BINOP, op), m_left(left), m_right(right) {

    m_children.push_back(left);
    m_children.push_back(right);
}

BinOp::~BinOp() {
    // std::cout << "~BinOp()" << std::endl;
}

AST * BinOp::getLeft() const {
    return m_left;
}
AST * BinOp::getRight() const {
    return m_right;
}

/*********************************************
 * UnaryOp node
 *********************************************/

UnaryOp::UnaryOp(Token op, AST * expr)
    : AST(NodeType::UNARYOP, op), m_expr(expr) {

    m_children.push_back(expr);
}

AST * UnaryOp::getExpr() const {
    return m_expr;
}

UnaryOp::~UnaryOp() {
    // std::cout << "~UnaryOp()" << std::endl;
}

/*********************************************
 * Num node
 *********************************************/

Num::Num(Token token)
    : AST(NodeType::NUM, token) {}

Num::~Num() {
    // std::cout << "~Num()" << std::endl;
}

/*********************************************
 * Compound node
 *********************************************/

Compound::Compound() : AST(NodeType::COMPOUND, Token()) {}

Compound::~Compound() {
    // std::cout << "~Compound()" << std::endl;
}

vector<AST *> Compound::getChildren() const {
    return m_children;
}

void Compound::pushChild(AST * node) {
    m_children.push_back(node);
}

/*********************************************
 * Assign node
 *********************************************/

Assign::Assign(AST *left, Token op, AST *right)
    : AST(NodeType::ASSIGN, op), m_left(left), m_right(right) {

    m_children.push_back(left);
    m_children.push_back(right);
}

Assign::~Assign() {
    // std::cout << "~Assign()" << std::endl;
}

AST * Assign::getLeft() const {
    return m_left;
}
AST * Assign::getRight() const {
    return m_right;
}

/*********************************************
 * Variable node
 *********************************************/

Var::Var(Token token) : AST(NodeType::VAR, token) {
    m_value = Any::anyCast<string>(token.getVal());
}

string Var::getVal() const {
    return m_value;
}

Var::~Var() {
    // std::cout << "~Var()" << std::endl;
}

/*********************************************
 * Block node
*********************************************/

Block::Block(std::vector<AST*> & declarations, AST* compound_statement) :
    AST(NodeType::BLOCK, Token()),
    m_declarations(declarations),
    m_compound_statement(compound_statement) {

    for (auto item : declarations) {
        m_children.push_back(item);
    }
    m_children.push_back(compound_statement);
}
Block::~Block() {
    // std::cout << "block deleted" << std::endl;
}

vector<AST *> Block::getDeclarations() const {
    return m_declarations;
}

AST * Block::getCompoundStatement() const {
    return m_compound_statement;
}

/*********************************************
 * Program node
*********************************************/

Program::Program(string name, AST* block) :
    AST(NodeType::PROGRAM, Token()),
    m_name(name), m_block(block) {

    m_children.push_back(block);
}
Program::~Program() {
}

string Program::getName() const {
    return m_name;
}

AST * Program::getBlock() const {
    return m_block;
}

/*********************************************
 * Type node
*********************************************/

VarDecl::VarDecl(AST * variable, AST * type) :
    AST(NodeType::VAR_DECL, Token()),
    m_variable_child(variable), m_type_child(type) {

    m_children.push_back(variable);
    m_children.push_back(type);
}

VarDecl::~VarDecl() {}

AST * VarDecl::getVarChild() const {
    return m_variable_child;
}
AST * VarDecl::getTypeChild() const {
    return m_type_child;
}


/*********************************************
 * Type node
*********************************************/

Type::Type(Token type) : AST(NodeType::TYPE, type) {
    m_value = Any::anyCast<string>(type.getVal());
}
Type::~Type() {
}

string Type::getVal() const {
    return m_value;
}


/*********************************************
 * No-operation node
*********************************************/

NoOp::NoOp() : AST(NodeType::NOOP, Token()) {}

NoOp::~NoOp() {
    // std::cout << "~NoOp()" << std::endl;
}

// ===== =====
// ===== =====
// ===== =====

/*********************************************
 * Parameter node
*********************************************/

Param::Param(AST * var_node, AST * type_node)
	: AST(NodeType::PARAM, Token()),
	m_var_node(var_node), m_type_node(type_node) {

        m_children.push_back(var_node);
        m_children.push_back(type_node);
    }

Param::~Param() {
    // std::cout << "param deleted" << std::endl;
}

AST * Param::getVarChild() const {
	return m_var_node;
}

AST * Param::getTypeChild() const {
	return m_type_node;
}

/*********************************************
 * Procedure declaration node
*********************************************/

ProcedureDecl::ProcedureDecl(
    string name,
    vector<AST *> & parameters,
    AST * block) :

    AST(NodeType::PROCEDURE_DECL, Token()),
    m_name(name),
    m_block(block) {

        for (auto p : parameters) {
            m_children.push_back(p);
            m_parameters.push_back(p);
        }
        m_children.push_back(block);
    }

ProcedureDecl::~ProcedureDecl() {}

string ProcedureDecl::getName() const {
    return m_name;
}

vector<AST *> ProcedureDecl::getParams() const {
    return m_parameters;
}

AST * ProcedureDecl::getBlock() const {
    return m_block;
}

/*********************************************
 * ProcedureCall node
*********************************************/

ProcedureCall::ProcedureCall(
    string procedure_name,
    std::vector<AST *> & actual_parameters,
    Token token,
    ProcedureSymbol procedure_symbol) :
    AST(NodeType::PROCEDURE_CALL, token),
    m_proc_name(procedure_name),
    m_proc_symbol(procedure_symbol) {
        for (AST * p : actual_parameters) {
            m_actual_param.push_back(p);
            m_children.push_back(p);
        }
    }
ProcedureCall::~ProcedureCall() {}

string ProcedureCall::getProcedureName() const {
    return m_proc_name;
}

vector<AST *> ProcedureCall::getActualParameters() const {
    return m_actual_param;
}

ProcedureSymbol ProcedureCall::getProcedureSymbol() const {
    return m_proc_symbol;
}

void ProcedureCall::setProcedureSymbol(ProcedureSymbol & procedure_symbol) {
    m_proc_symbol = procedure_symbol;
}


} // namespace ESI
