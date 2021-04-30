/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 16:33:54
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-04-27 19:58:28
 * @Description  :
 *********************************************/

#include "../inc/interpreter.hpp"

#include <iostream>
#include <stdexcept>

using std::string;
using std::vector;

using std::cout;
using std::endl;

namespace ESI {

Interpreter::Interpreter(AST * root, bool if_print_stack)
    : NodeVisitor(root), m_if_print_stack(if_print_stack) {
    }

Interpreter::~Interpreter() {}

Any Interpreter::visit(AST *node) {

    if (node == nullptr) {
        return Any();
    }

    if (node->getType() == NodeType::PROGRAM) {
        return visitProgram(node);
    }
    else if (node->getType() == NodeType::NUM) {
        return visitNum(node);
    }
    else if (node->getType() == NodeType::BINOP) {
        return visitBinOp(node);
    }
    else if (node->getType() == NodeType::BLOCK) {
        return visitBlock(node);
    }
    else if (node->getType() == NodeType::UNARYOP) {
        return visitUnaryOp(node);
    }
    else if (node->getType() == NodeType::ASSIGN) {
        visitAssign(node);
    }
    else if (node->getType() == NodeType::VAR) {
        return visitVar(node);
    }
    else if (node->getType() == NodeType::COMPOUND) {
        visitCompound(node);
    }
    else if (node->getType() == NodeType::NOOP) {
        visitNoOp();
    }
    else if (node->getType() == NodeType::VAR_DECL) {
        visitVarDecl(node);
    }
    else if (node->getType() == NodeType::PROCEDURE_DECL) {
        visitProcedureDecl(node);
    }
    else if (node->getType() == NodeType::PROCEDURE_CALL) {
        visitProcedureCall(node);
    }
    else if (node->getType() == NodeType::STRING) {
        return visitString(node);
    }
    else if (node->getType() == NodeType::BOOLEAN) {
        return visitBoolean(node);
    }
    else {
        generic_visit(node);
    }

    return Any();
}

void Interpreter::generic_visit(AST *node) {
    throw InterpreterError(
        (string) "No " + node->getTypeString() + " type method");
}

Any Interpreter::visitUnaryOp(AST *node) {
    UnaryOp * p_unaryop_node = dynamic_cast<UnaryOp *>(node);

    TokenType type = p_unaryop_node->getToken().getType();
    if (type == TokenType::PLUS) {
        return +visit(p_unaryop_node->getExpr());

    } else if (type == TokenType::MINUS) {
        return -visit(p_unaryop_node->getExpr());

    } else {
        // nothing else
        // TODO: exception
        return Any();
    }
}

Any Interpreter::visitBinOp(AST *node) {
    BinOp* bin_node = dynamic_cast<BinOp *>(node);

    TokenType type = bin_node->getToken().getType();
    if (type == TokenType::PLUS) {
        return visit(bin_node->getLeft()) + visit(bin_node->getRight());
    }
    else if (type == TokenType::MINUS) {
        return visit(bin_node->getLeft()) - visit(bin_node->getRight());
    }
    else if (type == TokenType::MUL) {
        return visit(bin_node->getLeft()) * visit(bin_node->getRight());
    }
    else if (type == TokenType::INTEGER_DIV) {
        return visit(bin_node->getLeft()) / visit(bin_node->getRight());
    }
    else if (type == TokenType::FLOAT_DIV) {
        return visit(bin_node->getLeft()) / visit(bin_node->getRight());
    }
    else {
        // nothing else
        // TODO: exception
        return Any();
    }
}

Any Interpreter::visitNum(AST *node) {
    if (node->getToken().getType() == TokenType::INTEGER_CONST) {
        return node->getToken().getVal();
    }
    else if (node->getToken().getType() == TokenType::REAL_CONST) {
        return node->getToken().getVal();
    }
    else {
        throw std::runtime_error(
            "Unsupported tokentype met when visiting a Num node"
        );
    }
}

/*********************************************
 * Program about
 *********************************************/

Any Interpreter::visitCompound(AST *node) {
    Compound * compound_node = dynamic_cast<Compound *>(node);

    for (AST *child : compound_node->getChildren()) {
        visit(child);
    }
    return Any();
}

Any Interpreter::visitNoOp() {
    return Any();
}

Any Interpreter::visitAssign(AST *node) {
    Assign* assign_node = dynamic_cast<Assign *>(node);

    string var_name = dynamic_cast<Var *>(assign_node->getLeft())->getVal();
    Any var_value = visit(assign_node->getRight());

    ActivationRecord & ar = m_call_stack.peek();
    ar[var_name] = var_value;

    return Any();
}

Any Interpreter::visitVar(AST *node) {
    string var_name = dynamic_cast<Var *>(node)->getVal();

    ActivationRecord & ar = m_call_stack.peek();
    Any var_value = ar.at(var_name);

    return var_value;
}

Any Interpreter::visitProgram(AST *node) {
    Program * program_node = dynamic_cast<Program *>(node);

    string program_name = program_node->getName();

    ActivationRecord ar = ActivationRecord(
            program_name,
            ARType::PROGRAM,
            1);

    m_call_stack.push(ar);

    // log
    if (m_if_print_stack) {
        cout << "ENTER PROGRAM: " << program_name << endl;
        printStack();
    }

    visit(program_node->getBlock());

    // log
    if (m_if_print_stack) {
        cout << "LEAVE PROGRAM: " << program_name << endl;
        printStack();
    }

    m_call_stack.pop();

    return Any();
}

Any Interpreter::visitBlock(AST *node) {
    Block* block_node = dynamic_cast<Block *>(node);

    for (auto p : block_node->getDeclarations()) {
        visit(p);
    }
    visit(block_node->getCompoundStatement());

    return Any();
}

Any Interpreter::visitVarDecl(AST *node) {
    // Do nothing.
    if (node != nullptr) return Any();
    return Any();
}

Any Interpreter::visitType(AST *node) {
    // Do nothing.
    if (node != nullptr) return Any();
    return Any();
}

// ===== =====

Any Interpreter::visitProcedureDecl(AST * node) {
    // Do nothing.
    ProcedureDecl * procedure_node = dynamic_cast<ProcedureDecl *>(node);
    string procedure_name = procedure_node->getName();

    return Any();
}

Any Interpreter::visitProcedureCall(AST * node) {
    ProcedureCall * procedure_call_node = dynamic_cast<ProcedureCall *>(node);

    string procedure_name = procedure_call_node->getProcedureName();

    ProcedureSymbol procedure_symbol =
        procedure_call_node->getProcedureSymbol();

    ActivationRecord ar = ActivationRecord(
            procedure_name,
            ARType::PROCEDURE,
            procedure_symbol.getLevel() + 1);


    vector<VarSymbol> formal_parameters =
        procedure_symbol.getParams();
    vector<AST *> actual_parameters =
        procedure_call_node->getActualParameters();

    long unsigned int idx = 0;
    while (idx < formal_parameters.size() ) {
        VarSymbol parameter_symbol = formal_parameters.at(idx);
        AST * parameter_node = actual_parameters.at(idx);

        string var_name = parameter_symbol.getName();
        ar[var_name] = visit(parameter_node);

        ++ idx;
    }

    m_call_stack.push(ar);

    // log
    if (m_if_print_stack) {
        cout << "ENTER PROCEDURE: " << procedure_name << endl;
        printStack();
    }

    visit((AST *)procedure_symbol.getProcedureBlock());

    // log
    if (m_if_print_stack) {
        cout << "LEAVE PROCEDURE: " << procedure_name << endl;
        printStack();
    }

    m_call_stack.pop();

    return Any();
}

Any Interpreter::visitString(AST * node) {
    String * string_node = dynamic_cast<String *>(node);

    return string_node -> getToken().getVal();
}

Any Interpreter::visitBoolean(AST * node) {
    Boolean * boolean_node = dynamic_cast<Boolean * >(node);

    return boolean_node -> getToken().getVal();
}

// ===== =====
// ===== ===== public
// ===== =====

void Interpreter::interpret() {
    if (m_root == nullptr) {
        return ;
    }

    try {
        Any result = visit(m_root);
    }
    catch (const InterpreterError &error) {

        std::cout << "When interpreting AST :" << std::endl;
        std::cout << "\t" << error.what() << std::endl;

        throw InterpreterError(
            "error met when interpreting, stop."
            );

    }
}

void Interpreter::printStack() {
    m_call_stack.print();
}

// ===== =====
// ===== ===== InterpreterError
// ===== =====

InterpreterError::InterpreterError(const string & message) :
    Exception(message) {}

InterpreterError::~InterpreterError() {}

const string InterpreterError::what() const {
    return "InterpreterError met: <<" + m_msg + ">>";
}

} // namespace ESI
