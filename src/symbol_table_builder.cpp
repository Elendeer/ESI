/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 20:31:02
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-12 15:28:58
 * @Description  :
*********************************************/

#include "../inc/symbol_table_builder.hpp"

using std::string;
using std::runtime_error;

namespace ESI {

SymbolTableBuilder::SymbolTableBuilder(AST * root) :
    NodeVisitor(root) {

    // Build-in type symbols
    m_table.define(new Symbol("INTEGER", SymbolType::INTEGER));
    m_table.define(new Symbol("REAL", SymbolType::REAL));
}

SymbolTableBuilder::~SymbolTableBuilder() {}

void SymbolTableBuilder::generic_visit(AST *node) {
    throw std::runtime_error(
        (string) "No " + node->getTypeString() + " type method");
}

// ===== =====

Any SymbolTableBuilder::visit_UnaryOp(AST *node) {
    UnaryOp * unary_op_node = dynamic_cast<UnaryOp *>(node);

    visit(unary_op_node->getExpr());

    return Any();
}

Any SymbolTableBuilder::visit_BinOp(AST *node) {
    BinOp * bin_op_node = dynamic_cast<BinOp *>(node);

    visit(bin_op_node->getLeft());
    visit(bin_op_node->getRight());
    return Any();
}

Any SymbolTableBuilder::visit_Num(AST *node) {
    if (node != nullptr) return Any();
    return Any();
}

// ===== =====

Any SymbolTableBuilder::visit_Compound(AST *node) {
    Compound * compound_node = dynamic_cast<Compound *>(node);
    for (auto p : compound_node->getChildren()) {
        visit(p);
    }
    return Any();
}

Any SymbolTableBuilder::visit_NoOp() {
    return Any();
}

Any SymbolTableBuilder::visit_Assign(AST *node) {
    // visit left and right is find to, but less efficient.

    Assign * assign_node = dynamic_cast<Assign *>(node);

    AST * var_node = assign_node->getLeft();
    string var_name = dynamic_cast<Var *>(var_node)->getVal();

    Symbol * p_symbol = m_table.lookup(var_name);

    if (p_symbol == nullptr) {
        string message = "Undefinded symobl : "
            + var_name;
        throw runtime_error(message);
    }

    return Any();
}

Any SymbolTableBuilder::visit_Var(AST *node) {
    Var * var_node = dynamic_cast<Var*>(node);

    string name = var_node->getVal();

    Symbol * p_symbol = m_table.lookup(name);

    if (p_symbol == nullptr) {
        string message = "Undefinded symobl : "
            + name;
        throw runtime_error(message);
    }

    return Any();
}

// ===== =====

Any SymbolTableBuilder::visitProgram(AST * node) {
    if (node != nullptr) return Any();
    return Any();
}

Any SymbolTableBuilder::visitBlock(AST * node) {
    if (node != nullptr) return Any();
    return Any();
}

Any SymbolTableBuilder::visitVarDecl(AST * node) {
    if (node != nullptr) return Any();
    return Any();
}

Any SymbolTableBuilder::visitType(AST * node) {
    if (node != nullptr) return Any();
    return Any();
}

} // namespace ESI
