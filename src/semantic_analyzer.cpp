/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 20:31:02
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-17 16:55:42
 * @Description  :
*********************************************/

#include "../inc/semantic_analyzer.hpp"

using std::string;
using std::runtime_error;

namespace ESI {

SemanticAnalyzer::SemanticAnalyzer(AST * root) :
    NodeVisitor(root) {

    // Build-in type symbols
    m_table.define(new Symbol("INTEGER", SymbolType::INTEGER));
    m_table.define(new Symbol("REAL", SymbolType::REAL));
}

SemanticAnalyzer::~SemanticAnalyzer() {}

void SemanticAnalyzer::generic_visit(AST *node) {
    throw std::runtime_error(
        (string) "No " + node->getTypeString() + " type method");
}

// ===== =====

Any SemanticAnalyzer::visit(AST *node) {

    if (node == nullptr) {
        return Any();
    }

    if (node->getType() == NodeType::PROGRAM) {
        return visitProgram(node);
    }
    else if (node->getType() == NodeType::NUM) {
        return visit_Num(node);
    }
    else if (node->getType() == NodeType::BINOP) {
        return visit_BinOp(node);
    }
    else if (node->getType() == NodeType::BLOCK) {
        return visitBlock(node);
    }
    else if (node->getType() == NodeType::UNARYOP) {
        return visit_UnaryOp(node);
    }
    else if (node->getType() == NodeType::ASSIGN) {
        visit_Assign(node);
    }
    else if (node->getType() == NodeType::VAR) {
        return visit_Var(node);
    }
    else if (node->getType() == NodeType::COMPOUND) {
        visit_Compound(node);
    }
    else if (node->getType() == NodeType::NOOP) {
        visit_NoOp();
    }
    else if (node->getType() == NodeType::VAR_DECL) {
        visitVarDecl(node);
    }
    else if (node->getType() == NodeType::PORCEDURE_DECL) {
        visitProcedureDecl(node);
    }
    else {
        generic_visit(node);
    }

    return Any();
}

Any SemanticAnalyzer::visit_UnaryOp(AST *node) {
    UnaryOp * unary_op_node = dynamic_cast<UnaryOp *>(node);

    visit(unary_op_node->getExpr());

    return Any();
}

Any SemanticAnalyzer::visit_BinOp(AST *node) {
    BinOp * bin_op_node = dynamic_cast<BinOp *>(node);

    visit(bin_op_node->getLeft());
    visit(bin_op_node->getRight());
    return Any();
}

Any SemanticAnalyzer::visit_Num(AST *node) {
    if (node != nullptr) return Any();
    return Any();
}

// ===== =====

Any SemanticAnalyzer::visit_Compound(AST *node) {
    Compound * compound_node = dynamic_cast<Compound *>(node);
    for (auto p : compound_node->getChildren()) {
        visit(p);
    }
    return Any();
}

Any SemanticAnalyzer::visit_NoOp() {
    return Any();
}

Any SemanticAnalyzer::visit_Assign(AST *node) {
    Assign * assign_node = dynamic_cast<Assign *>(node);

    visit(assign_node->getLeft());
    visit(assign_node->getRight());

    return Any();
}

Any SemanticAnalyzer::visit_Var(AST *node) {
    Var * var_node = dynamic_cast<Var*>(node);

    string name = var_node->getVal();

    Symbol * p_symbol = m_table.lookup(name);

    if (p_symbol == nullptr) {
        string message = "Undefinded symobl(identifier) : "
            + name;
        throw runtime_error(message);
    }

    return Any();
}

// ===== =====

Any SemanticAnalyzer::visitProgram(AST * node) {
    Program * program_node = dynamic_cast<Program * >(node);

    visit(program_node->getBlock());

    return Any();
}

Any SemanticAnalyzer::visitBlock(AST * node) {
    Block * block_node = dynamic_cast<Block * >(node);

    for (auto p : block_node->getDeclarations()) {
        visit(p);
    }
    visit(block_node->getCompoundStatement());

    return Any();
}

Any SemanticAnalyzer::visitVarDecl(AST * node) {
    VarDecl * var_decl_node = dynamic_cast<VarDecl * >(node);

    Var * var_node = dynamic_cast<Var *>(var_decl_node->getVarChild());
    string var_name = var_node->getVal();
    if (m_table.lookup(var_name) != nullptr) {
        throw runtime_error(
            "Duplicat declaration of symbol(identifier) " + var_name +
            " found."
        );
    }

    Type * type_node = dynamic_cast<Type *>(var_decl_node->getTypeChild());
    string var_type_str = type_node->getVal();
    Symbol * var_type_symbol = m_table.lookup(var_type_str);

    SymbolType var_type = var_type_symbol->getType();

    m_table.define(new Symbol(var_name, var_type));

    return Any();
}

Any SemanticAnalyzer::visitType(AST * node) {
    if (node != nullptr) return Any();
    return Any();
}

// ===== =====
// ===== =====
// ===== =====

void SemanticAnalyzer::analyze() {
    if (m_root == nullptr) return ;

    try {
        visit(m_root);

        // m_table.print();
    }
    catch (const runtime_error & error) {

        std::cout << "When building symbol table from AST :"
            << std::endl << "\t" << error.what() << std::endl;

        throw runtime_error(
            "error met when semantic analyzing, stop."
            );
    }
}

// ===== =====

Any SemanticAnalyzer::visitProcedureDecl(AST * node) {
    // Do nothing.
    if (node == nullptr) return Any();
    return Any();
}

} // namespace ESI
