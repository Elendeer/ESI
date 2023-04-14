/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 16:05:51
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2023-04-14 22:18:49
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

    {NodeType::PROCEDURE_DECL, "PORCEDURE_DECL"},

    {NodeType::STRING, "STRING"},
    {NodeType::BOOLEAN, "BOOLEAN"},
    {NodeType::FUNCTION_DECL, "FUNCTION_DECL"},
    {NodeType::FUNCTION_CALL, "FUNCTION_CALL"},

    {NodeType::READ, "READ"},
    {NodeType::WRITE, "WRITE"},

    {NodeType::IF, "IF"},
    {NodeType::WHILE, "WHILE"}
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
    if (map_node_type_string.find(m_nodeType)
        == map_node_type_string.end()){
            return "[AST type string no found]";
        }

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

Var::Var(Token token, bool is_array)
    : AST(NodeType::VAR, token), m_is_array(is_array) {
    m_var_name = Any::anyCast<string>(token.getVal());
}

Var::~Var() {
    // std::cout << "~Var()" << std::endl;
}

string Var::getVarName() const {
    return m_var_name;
}

bool Var::isArray() const {
    return m_is_array;
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

Type::Type(Token type_token)
    : AST(NodeType::TYPE, type_token),
    m_is_array(false),
    m_array_type_child(nullptr),
    m_array_start_child(nullptr),
    m_array_end_child(nullptr) {
        m_value = Any::anyCast<string>(type_token.getVal());
        m_children.push_back(m_array_type_child);
        m_children.push_back(m_array_start_child);
        m_children.push_back(m_array_end_child);
    }
Type::Type(Token type_token, AST * array_type,
    AST * array_start, AST * array_end)
    : AST(NodeType::TYPE, type_token),
    m_is_array(true),
    m_array_type_child(array_type),
    m_array_start_child(array_start),
    m_array_end_child(array_end) {
        m_value = Any::anyCast<string>(type_token.getVal());
        m_children.push_back(m_array_type_child);
        m_children.push_back(m_array_start_child);
        m_children.push_back(m_array_end_child);
    }

Type::~Type() {
}

string Type::getVal() const {
    return m_value;
}

string Type::getArrayTypeVal() const {
    if (!m_is_array) return "";

    Type * p_array_type_node = dynamic_cast<Type *>(m_array_type_child);
    return p_array_type_node -> getVal();
}
AST * Type::getArrayTypeChild() const {
    return m_array_type_child;
}


AST * Type::getArrayStart() const {
    return m_array_start_child;
}
AST * Type::getArrayEnd() const {
    return m_array_end_child;
}

bool Type::isArrayType() const {
    return m_is_array;
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
    Token name_id_token,
    ProcedureSymbol procedure_symbol) :
        AST(NodeType::PROCEDURE_CALL, name_id_token),
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

void ProcedureCall::setProcedureSymbol(
    const ProcedureSymbol & procedure_symbol) {
        m_proc_symbol = procedure_symbol;
    }

/*********************************************
 * String node
*********************************************/

String::String(Token token) :
    AST(NodeType::STRING, token) {}

String::~String() {}

/*********************************************
 * Boolean node
*********************************************/

Boolean::Boolean(Token token) :
    AST(NodeType::BOOLEAN, token) {}

Boolean::~Boolean() {}


/*********************************************
 * Function declaration node
*********************************************/

FunctionDecl::FunctionDecl(
    string name,
    vector<AST *> & parameters,
    AST * type_node,
    AST * block) :

    AST(NodeType::FUNCTION_DECL, Token()),
    m_name(name),
    m_type_node(type_node),
    m_block(block) {

        for (auto p : parameters) {
            m_children.push_back(p);
            m_parameters.push_back(p);
        }
        m_children.push_back(type_node);
        m_children.push_back(block);
    }

FunctionDecl::~FunctionDecl() {
}

string FunctionDecl::getName() const {
    return m_name;
}

vector<AST *> FunctionDecl::getParams() const {
    return m_parameters;
}

AST * FunctionDecl::getBlock() const {
    return m_block;
}

AST * FunctionDecl::getType() const {
    return m_type_node;
}

/*********************************************
 * Function call node
*********************************************/

FunctionCall::FunctionCall(
    string function_name,
    vector<AST *> & actual_parameters,
    Token name_id_token,
    FunctionSymbol function_symbol):
        AST(NodeType::FUNCTION_CALL, name_id_token),
        m_func_name(function_name),
        m_func_symbol(function_symbol) {
            for (AST * p : actual_parameters) {
                m_actual_param.push_back(p);
                m_children.push_back(p);
            }
        }

FunctionCall::~FunctionCall() {}

string FunctionCall::getFunctionName() const {
    return m_func_name;
}

vector<AST *> FunctionCall::getActualParameters() const {
    return m_actual_param;
}

FunctionSymbol FunctionCall::getFunctionSymbol() const {
    return m_func_symbol;
}

void FunctionCall::setFunctionSymbol(
    const FunctionSymbol & function_symbol) {
        m_func_symbol = function_symbol;
    }

/*********************************************
 * Read node
*********************************************/

Read::Read(vector<Var *> & read_vars):
    AST(NodeType::READ, Token()) {
        for (Var * p : read_vars) {
            m_read_vars.push_back(p);
            m_children.push_back(p);
        }
    }

Read::~Read() {}

vector<Var *> Read::getReadVars() const {
    return m_read_vars;
}

/*********************************************
 * Write node
*********************************************/

Write::Write(AST * p_expr, bool is_writeln) :
    AST(NodeType::WRITE, Token()), m_p_expr(p_expr) {
        m_children.push_back(p_expr);
        m_is_writeln = is_writeln;
    }

Write::~Write() {}

AST * Write::getExpr() const {
    return m_p_expr;
}

bool Write::isWriteln() const {
    return m_is_writeln;
}

/*********************************************
 * If node
*********************************************/

If::If(
        AST * p_condition,
        AST * p_body,
        AST * p_else) :
            AST(NodeType::IF, Token()),
            m_p_condition(p_condition),
            m_p_body(p_body),
            m_p_else(p_else) {
                m_children.push_back(p_condition);
                m_children.push_back(p_body);

                if (p_else != nullptr)
                    m_children.push_back(p_else);
            }
If::~If() {}

AST * If::getCondition() const {
    return m_p_condition;
}

AST * If::getBody() const {
    return m_p_body;
}

AST * If::getElse() const {
    return m_p_else;
}

/*********************************************
 * If node
*********************************************/

While::While(AST * p_condition, AST * p_body):
    AST(NodeType::WHILE, Token()),
    m_p_condition(p_condition),
    m_p_body(p_body) {
        m_children.push_back(p_condition);
        m_children.push_back(p_body);
    }

While::~While() {}

AST * While::getCondition() const {
    return m_p_condition;
}

AST * While::getBody() const {
    return m_p_body;
}

} // namespace ESI
