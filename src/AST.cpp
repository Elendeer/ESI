/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 16:05:51
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-12 17:12:57
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
    {NodeType::TYPE, "TYPE"}
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

} // namespace ESI
