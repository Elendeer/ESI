/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 20:31:02
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-04-03 10:17:12
 * @Description  :
*********************************************/
//
// 1. When visiting the node in AST, we first print
// what scope we’re entering.
// 2. We create a separate scoped symbol table
// to represent the global scope.
// When we construct an instance of ScopedSymbolTable,
// we explicitly pass the scope name and scope level arguments
// to the class constructor.
// 3. We assign the address of the newly created scope
// to the instance variable m_p_current_scope.
// Other visitor methods that insert and look up symbols
// in scoped symbol tables will use the m_p_current_scope.
// 4. We visit a subtree. This is the old part.
// 5. Before leaving the global scope
// we print the contents of the global scope (scoped symbol table)
// 6. We also print the message that we’re leaving the global scope


#include "../inc/semantic_analyzer.hpp"

using std::string;

using std::cout;
using std::endl;

namespace ESI {

SemanticAnalyzer::SemanticAnalyzer(AST * root)
	: NodeVisitor(root),
    m_build_in_type_scope("build-in tyep", -1),
    m_p_current_scope(nullptr) {
        // Build-in type symbols
        m_build_in_type_scope.define(new Symbol("INTEGER", SymbolType::INTEGER));
        m_build_in_type_scope.define(new Symbol("REAL", SymbolType::REAL));
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
    else if (node->getType() == NodeType::PORCEDURE_DECL) {
        visitProcedureDecl(node);
    }
    else {
        generic_visit(node);
    }

    return Any();
}

Any SemanticAnalyzer::visitUnaryOp(AST *node) {
    UnaryOp * unary_op_node = dynamic_cast<UnaryOp *>(node);

    visit(unary_op_node->getExpr());

    return Any();
}

Any SemanticAnalyzer::visitBinOp(AST *node) {
    BinOp * bin_op_node = dynamic_cast<BinOp *>(node);

    visit(bin_op_node->getLeft());
    visit(bin_op_node->getRight());
    return Any();
}

Any SemanticAnalyzer::visitNum(AST *node) {
    if (node != nullptr) return Any();
    return Any();
}

// ===== =====

Any SemanticAnalyzer::visitCompound(AST *node) {
    Compound * compound_node = dynamic_cast<Compound *>(node);
    for (auto p : compound_node->getChildren()) {
        visit(p);
    }
    return Any();
}

Any SemanticAnalyzer::visitNoOp() {
    return Any();
}

Any SemanticAnalyzer::visitAssign(AST *node) {
    Assign * assign_node = dynamic_cast<Assign *>(node);

    visit(assign_node->getLeft());
    visit(assign_node->getRight());

    return Any();
}

Any SemanticAnalyzer::visitVar(AST *node) {
    Var * var_node = dynamic_cast<Var*>(node);

    string name = var_node->getVal();

    Symbol * p_symbol = m_p_current_scope->lookup(name);

    if (p_symbol == nullptr) {
        string message = "Undefinded symobl(identifier) : "
            + name;
        throw SemanticError(message);
    }

    return Any();
}

// ===== =====

Any SemanticAnalyzer::visitProgram(AST * node) {
    Program * program_node = dynamic_cast<Program * >(node);

    cout << "ENTER global scope" << endl;

    // Global scope have no enclosing scope.
    ScopedSymbolTable global_scope = ScopedSymbolTable("global", 1);
    m_p_current_scope = & global_scope;

    visit(program_node->getBlock());

    global_scope.print();
    cout << "LEAVE global scope" << endl;

    // nullptr after all.
    m_p_current_scope = m_p_current_scope->getEnclosingScope();

    return Any();
}

Any SemanticAnalyzer::visitBlock(AST * node) {
    Block * block_node = dynamic_cast<Block * >(node);

    for (AST * p : block_node->getDeclarations()) {
        visit(p);
    }
    visit(block_node->getCompoundStatement());

    return Any();
}

Any SemanticAnalyzer::visitVarDecl(AST * node) {
    VarDecl * var_decl_node = dynamic_cast<VarDecl * >(node);

    Var * var_node = dynamic_cast<Var *>(var_decl_node->getVarChild());
    // Get variable name string.
    string var_name = var_node->getVal();

    // Dumplicat declaration checking.
    if (m_p_current_scope->lookup(var_name, true) != nullptr) {
        throw SemanticError(
            "Duplicat declaration of symbol(identifier) " + var_name +
            " found in scope: " +
            m_p_current_scope->getScopeName()
        );
    }

    Type * type_node = dynamic_cast<Type *>(var_decl_node->getTypeChild());
    string var_type_str = type_node->getVal();
    Symbol * var_type_symbol = m_build_in_type_scope.lookup(var_type_str);
    // Get variable symble type .
    SymbolType var_type = var_type_symbol->getType();

    m_p_current_scope->define(new Symbol(var_name, var_type));

    return Any();
}

Any SemanticAnalyzer::visitType(AST * node) {
    if (node != nullptr) return Any();
    return Any();
}

// ===== =====

Any SemanticAnalyzer::visitProcedureDecl(AST * node) {
    ProcedureDecl * procedure_node = dynamic_cast<ProcedureDecl *>(node);
    string proc_name = procedure_node->getName();

    // Symbol creating
    ProcedureSymbol * proc_symbol = new ProcedureSymbol(proc_name);
    m_p_current_scope->define(proc_symbol);

    cout << "ENTER scope: " << proc_name << endl;
    // Create scope for this procedure.
    ScopedSymbolTable procedure_scope = ScopedSymbolTable(
        proc_name,
        m_p_current_scope->getScopeLevel() + 1,
        m_p_current_scope);

    m_p_current_scope = & procedure_scope;

    // Put parameter symbols into procedure scope and procedure symbol.
    for (AST * node : procedure_node->getParams()) {
        Param * param_node = dynamic_cast<Param *>(node);

        Type * type_node = dynamic_cast<Type *>(param_node->getTypeChild());
        Symbol * p_type_symbol = m_build_in_type_scope.lookup(
                type_node->getVal());
        // get parameter type.
        SymbolType param_type = p_type_symbol->getType();

        Var * var_node = dynamic_cast<Var *>(param_node->getVarChild());
        // get parameter name.
        string param_name = var_node->getVal();

        VarSymbol * var_symbol = new VarSymbol(param_name, param_type);
        m_p_current_scope->define(var_symbol);
        proc_symbol->pushParameter(var_symbol);
    }

    visitBlock(procedure_node->getBlock());

    procedure_scope.print();

    cout << "LEAVE scope: " << proc_name << endl;
    // this scope is local, will be delete after this function ended.
    // m_p_current_scope will pointing to nothing after that.
    // And we will reset this pointer to tmp.
    m_p_current_scope = m_p_current_scope->getEnclosingScope();


    return Any();
}

// ===== =====
// ===== ===== public
// ===== =====

void SemanticAnalyzer::analyze() {
    if (m_root == nullptr) return ;

    try {
        visit(m_root);
    }
    catch (const Exception & error) {

        std::cout << "When building symbol table from AST :"
            << std::endl << "\t" << error.what() << std::endl;

        throw SemanticError(
            "error met when semantic analyzing, stop."
            );
    }
}

void SemanticAnalyzer::printSymbolTable() {
	m_build_in_type_scope.print();
}

// ===== =====
// ===== ===== SemanticError
// ===== =====

SemanticError::SemanticError(const string & message) :
    Exception(message) {}

SemanticError::~SemanticError() {}

const string SemanticError::what() const {
    return "SemanticError met: <<" + m_msg + ">>";
}
} // namespace ESI
