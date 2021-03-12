/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 20:31:02
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-12 17:05:54
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

Any SymbolTableBuilder::visit(AST *node) {

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
    else {
        generic_visit(node);
    }

    return Any();
}

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
    Program * program_node = dynamic_cast<Program * >(node);

    visit(program_node->getBlock());

    return Any();
}

Any SymbolTableBuilder::visitBlock(AST * node) {
    Block * block_node = dynamic_cast<Block * >(node);

    for (auto p : block_node->getDeclarations()) {
        visit(p);
    }
    visit(block_node->getCompoundStatement());

    return Any();
}

Any SymbolTableBuilder::visitVarDecl(AST * node) {
    VarDecl * var_decl_node = dynamic_cast<VarDecl * >(node);

    Var * var_node = dynamic_cast<Var *>(var_decl_node->getVarChild());
    Type * type_node = dynamic_cast<Type *>(var_decl_node->getTypeChild());

    string var_name = var_node->getVal();
    string var_type_str = type_node->getVal();

    Symbol * var_type_symbol = m_table.lookup(var_type_str);

    // So far, parser ensure that var_type_symbol is impossible
    // to be nullptr.
    if (var_type_symbol == nullptr) {
        throw runtime_error(
            "Undefined symbol : " + var_type_str
        );
    }

    SymbolType var_type = var_type_symbol->getType();

    m_table.define(new Symbol(var_name, var_type));

    return Any();
}

Any SymbolTableBuilder::visitType(AST * node) {
    if (node != nullptr) return Any();
    return Any();
}

// ===== =====
// ===== =====
// ===== =====

void SymbolTableBuilder::build() {
    if (m_root == nullptr) return ;

    try {
        visit(m_root);

        m_table.print();
    }
    catch (const runtime_error & error) {

        std::cout << "When building symbol table from AST :"
            << std::endl << "\t" << error.what() << std::endl;
    }
}

} // namespace ESI
