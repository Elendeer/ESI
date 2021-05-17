/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 20:31:02
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-05-17 23:32:20
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
using std::to_string;

using std::cout;
using std::endl;
using std::vector;

namespace ESI {

SemanticAnalyzer::SemanticAnalyzer(AST * root, bool if_print)
	: NodeVisitor(root),
    m_build_in_type_scope("build-in tyep", -1),
    m_p_current_scope(nullptr),
    m_if_print(if_print) {
        // Build-in type symbols
        // Levels are set to -1
        m_build_in_type_scope.define(
                Symbol("INTEGER", -1, SymbolType::INTEGER));
        m_build_in_type_scope.define(
                Symbol("REAL", -1, SymbolType::REAL));
        m_build_in_type_scope.define(
                Symbol("STRING", -1, SymbolType::STRING));
        m_build_in_type_scope.define(
                Symbol("BOOLEAN", -1, SymbolType::BOOLEAN));
    }

SemanticAnalyzer::~SemanticAnalyzer() {}

// ===== =====

void SemanticAnalyzer::generic_visit(AST *node) {
    throw SemanticError(
        "No " + node->getTypeString() + " type method");
}

void SemanticAnalyzer::error(
    string message,
    ErrorCode error_code,
    Token token) {
        throw SemanticError(message, error_code, token);
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
    else if (node->getType() == NodeType::PROCEDURE_DECL) {
        visitProcedureDecl(node);
    }
    else if (node->getType() == NodeType::PROCEDURE_CALL) {
        visitProcedureCall(node);
    }
    else if (node->getType() == NodeType::STRING) {
        visitString(node);
    }
    else if (node->getType() == NodeType::BOOLEAN) {
        visitBoolean(node);
    }
    else if (node->getType() == NodeType::FUNCTION_DECL) {
        visitFunctionDecl(node);
    }
    else if (node->getType() == NodeType::FUNCTION_CALL) {
        visitFunctionCall(node);
    }
    else if (node->getType() == NodeType::READ) {
        visitRead(node);
    }
    else if (node->getType() == NodeType::WRITE) {
        visitWrite(node);
    }
    else if (node->getType() == NodeType::IF) {
        visitIf(node);
    }
    else if (node->getType() == NodeType::WHILE) {
        visitWhile(node);
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
    // Do nothing.
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

    Var * var_node = dynamic_cast<Var *>(
            assign_node->getLeft());

    visit(var_node);
    visit(assign_node->getRight());

    return Any();
}

Any SemanticAnalyzer::visitVar(AST *node) {
    Var * var_node = dynamic_cast<Var*>(node);

    string name = var_node->getVarName();

    Symbol * p_symbol = m_p_current_scope->lookup(name);

    if (p_symbol == nullptr) {
        string message =
            "Undefinded symobl(identifier) : " + name;

        error(message,
            ErrorCode::ID_NOT_FOUND,
            var_node->getToken());
    }

    return Any();
}

// ===== =====

Any SemanticAnalyzer::visitProgram(AST * node) {
    Program * program_node = dynamic_cast<Program * >(node);

    if (m_if_print) {
        cout << "ENTER global scope" << endl;
    }

    // Global scope have no enclosing scope.
    ScopedSymbolTable global_scope = ScopedSymbolTable("global", 1);
    m_p_current_scope = & global_scope;

    visit(program_node->getBlock());

    if (m_if_print) {
        global_scope.print();
        cout << "LEAVE global scope" << endl << endl;
    }

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
    string var_name = var_node->getVarName();

    // Dumplicat declaration checking.
    if (m_p_current_scope->lookup(var_name, true) != nullptr) {
        error(
            "Duplicat declaration of symbol(identifier) " + var_name +
            " found in scope: " +
            m_p_current_scope->getScopeName(),
            ErrorCode::DUPLICATE_ID,
            var_node->getToken()
        );
    }

    Type * type_node = dynamic_cast<Type *>(var_decl_node->getTypeChild());
    string var_type_str = type_node->getVal();
    Symbol * var_type_symbol = m_build_in_type_scope.lookup(var_type_str);

    if (var_type_symbol == nullptr) {
        error("Invailid Syntax: declare a variable with unknow type.",
                ErrorCode::UNKNOW_TYPE,
                var_node->getToken());
    }
    // Get variable symble type .
    SymbolType var_type = var_type_symbol->getType();

    m_p_current_scope->define(
            Symbol(var_name,
                m_p_current_scope->getScopeLevel(),
                var_type));

    return Any();
}

Any SemanticAnalyzer::visitType(AST * node) {
    if (node != nullptr) return Any();
    return Any();
}

// ===== =====

Any SemanticAnalyzer::visitProcedureDecl(AST * node) {
    ProcedureDecl * procedure_decl_node =
        dynamic_cast<ProcedureDecl *>(node);

    string proc_name = procedure_decl_node->getName();

    // Symbol creating
    // Must define the symbol first than take the pointer out,
    // because these two pointer is pointing to different object.
    //
    // The block pointer is accessed by the interpreter
    // when executing procedure call.
    m_p_current_scope->define(
            ProcedureSymbol(
                proc_name,
                m_p_current_scope->getScopeLevel(),
                procedure_decl_node->getBlock()));

    ProcedureSymbol * proc_symbol =
        dynamic_cast<ProcedureSymbol * >(
                m_p_current_scope->lookup(proc_name));

    if (proc_symbol == nullptr) {
        error("Undefined Symbol: " + proc_name,
                ErrorCode::ID_NOT_FOUND,
                procedure_decl_node->getToken());
    }

    // log
    if (m_if_print) {
        cout << "ENTER: " << proc_name << endl;
    }
    // Create scope for this procedure.
    ScopedSymbolTable procedure_scope = ScopedSymbolTable(
        proc_name,
        m_p_current_scope->getScopeLevel() + 1,
        m_p_current_scope);

    m_p_current_scope = & procedure_scope;

    // Put parameter symbols into procedure scope and procedure symbol.
    for (AST * node : procedure_decl_node->getParams()) {
        Param * param_node = dynamic_cast<Param *>(node);

        Type * type_node = dynamic_cast<Type *>(param_node->getTypeChild());
        Symbol * p_type_symbol = m_build_in_type_scope.lookup(
                type_node->getVal());
        // get parameter type.
        SymbolType param_type = p_type_symbol->getType();

        Var * var_node = dynamic_cast<Var *>(param_node->getVarChild());
        // get parameter name.
        string param_name = var_node->getVarName();

        // This symbol will be pushed into the procedure symbol as
        // a parameter, and will be deleted by the destructor
        // of the procedure symbol.
        VarSymbol var_symbol = VarSymbol(
                param_name,
                m_p_current_scope->getScopeLevel(),
                param_type);
        m_p_current_scope->define(var_symbol);
        proc_symbol->pushParameter(var_symbol);
    }

    // Define procedure itself inside this scope for
    // recursive procedure call.
    m_p_current_scope->define(*proc_symbol);

    visitBlock(procedure_decl_node->getBlock());

    // log
    if (m_if_print) {
        procedure_scope.print();
        cout << "LEAVE scope: " << proc_name << endl << endl;
    }

    // this scope is local, will be delete after this function ended.
    // m_p_current_scope will pointing to nothing after that.
    // And we will reset this pointer to tmp.
    m_p_current_scope = m_p_current_scope->getEnclosingScope();


    return Any();
}

Any SemanticAnalyzer::visitProcedureCall(AST * node) {
    ProcedureCall * procedure_call_node =
        dynamic_cast<ProcedureCall *>(node);

    string procedure_name =
        procedure_call_node -> getProcedureName();

    // try to get symbol.
    Symbol * p_symbol = m_p_current_scope -> lookup(procedure_name);
    if (p_symbol == nullptr) {
        error(
            "Procedure call no matched: Undefined procedure name. ",
            ErrorCode::ID_NOT_FOUND,
            procedure_call_node -> getToken());
    }

    // If function call be used as a statement, it will be
    // recognized as a procedure call.
    if (p_symbol->getCategory() != SymbolCategory::PROCEDURE_SYMBOL) {
        error("Symbol " + procedure_name + " is not a procedure. " ,
            ErrorCode::WRONG_USAGE,
            procedure_call_node->getToken());
    }

    ProcedureSymbol * p_procedure_symbol =
        dynamic_cast<ProcedureSymbol *>(p_symbol);

    // To get formal parameter symbol vector
    // from symbol table
    // and actual parameter AST vector from AST node.
    // Try to compare the number of formal parameters and
    // actual parameters.

    vector<VarSymbol> formal_parameters =
        p_procedure_symbol -> getParams();

    vector<AST *> actual_parameters =
        procedure_call_node -> getActualParameters();


    // parameter number no matched
    if (formal_parameters.size() != actual_parameters.size()) {
        string message =
            "Procedure call not matched: Wrong number of parameters. "
            + (string)"formal/actual: "
            + to_string(formal_parameters.size()) + "/"
            + to_string(actual_parameters.size()) + ". ";
        error(
            message,
            ErrorCode::WRONG_PARAMS_NUM,
            procedure_call_node -> getToken());
    }

    // parameter number matched

    for (AST * p : actual_parameters) {
        visit(p);
    }

    // put Procedure Symbol into ProcedureCall node
    procedure_call_node->setProcedureSymbol(*p_procedure_symbol);

    return Any();
}

Any SemanticAnalyzer::visitString(AST * node) {
    // Do nothing
    if (node == nullptr) return Any();
    return Any();
}

Any SemanticAnalyzer::visitBoolean(AST * node) {
    // Do nothing.
    if (node != nullptr) return Any();
    return Any();
}

Any SemanticAnalyzer::visitFunctionDecl(AST * node) {
    FunctionDecl * function_decl_node =
        dynamic_cast<FunctionDecl *>(node);

    string func_name = function_decl_node->getName();


    // get function symbol type.

    Type * function_type_node =
        dynamic_cast<Type *>(function_decl_node->getType());
    Symbol * p_function_type_symbol =
        m_build_in_type_scope.lookup(function_type_node->getVal());
    SymbolType function_symbol_type = p_function_type_symbol->getType();

    // Symbol creating
    // Must define the symbol first than take the pointer out,
    // because these two pointer is pointing to different object.
    //
    // The block pointer will be accessed by the interpreter
    // when executing procedure call.
    m_p_current_scope->define(
            FunctionSymbol(
                func_name,
                m_p_current_scope->getScopeLevel(),
                function_symbol_type,
                function_decl_node->getBlock()));

    FunctionSymbol * func_symbol =
        dynamic_cast<FunctionSymbol *>(
                m_p_current_scope->lookup(func_name));

    if (func_symbol == nullptr) {
        error("Undefined Symbol: " + func_name,
                ErrorCode::ID_NOT_FOUND,
                function_decl_node->getToken());
    }

    // log
    if (m_if_print) {
        cout << "ENTER: " << func_name << endl;
    }

    // Create scope for this function
    ScopedSymbolTable function_scope = ScopedSymbolTable(
        func_name,
        m_p_current_scope->getScopeLevel() + 1,
        m_p_current_scope);

    // change current scope to the new created one.
    m_p_current_scope = & function_scope;

    // define a return variable according to function name.
    VarSymbol return_var_symbol = VarSymbol(
        func_name,
        m_p_current_scope->getScopeLevel(),
        function_symbol_type
    );
    m_p_current_scope->define(return_var_symbol);

    // Put parameter symbols into function scope and function symbol.
    for (AST * node : function_decl_node->getParams()) {
        Param * param_node = dynamic_cast<Param *>(node);

        Type * type_node = dynamic_cast<Type *>(param_node->getTypeChild());
        Symbol * p_type_symbol =
            m_build_in_type_scope.lookup(type_node->getVal());

        // get parameter type.
        SymbolType param_type = p_type_symbol->getType();

        Var * var_node = dynamic_cast<Var *>(param_node->getVarChild());
        // get parameter name.
        string param_name = var_node->getVarName();

        // This symbol will be pushed into the function symbol as
        // a parameter, and will be deleted by the destructor
        // of the function symbol.
        VarSymbol var_symbol = VarSymbol(
                param_name,
                m_p_current_scope->getScopeLevel(),
                param_type);
        m_p_current_scope->define(var_symbol);
        func_symbol->pushParameter(var_symbol);
    }

    visitBlock(function_decl_node->getBlock());

    // log
    if (m_if_print) {
        function_scope.print();
        cout << "LEAVE scope: " << func_name << endl << endl;
    }

    // this scope is local, will be delete after this function ended.
    // m_p_current_scope will pointing to nothing after that.
    // And we will reset this pointer to tmp.
    m_p_current_scope = m_p_current_scope->getEnclosingScope();


    return Any();
}

Any SemanticAnalyzer::visitFunctionCall(AST * node) {
    FunctionCall * function_call_node =
        dynamic_cast<FunctionCall *>(node);

    string function_name =
        function_call_node -> getFunctionName();

    // try to get symbol.
    Symbol * p_symbol = m_p_current_scope -> lookup(function_name);
    if (p_symbol == nullptr) {
        error(
            "Function call no matched: Undefined function name. ",
            ErrorCode::ID_NOT_FOUND,
            function_call_node -> getToken());
    }

    if (p_symbol->getCategory() != SymbolCategory::FUNCTION_SYMBOL) {
        error("Symbol " + function_name + " is not a function. ",
            ErrorCode::WRONG_USAGE,
            function_call_node->getToken());
    }

    FunctionSymbol * p_function_symbol =
        dynamic_cast<FunctionSymbol *>(p_symbol);

    // To get formal parameter symbol vector
    // from symbol table
    // and actual parameter AST vector from AST node.
    // Try to compare the number of formal parameters and
    // actual parameters.

    vector<VarSymbol> formal_parameters =
        p_function_symbol -> getParams();

    vector<AST *> actual_parameters =
        function_call_node -> getActualParameters();


    // parameter number no matched
    if (formal_parameters.size() != actual_parameters.size()) {
        string message =
            "Function call not matched: Wrong number of parameters. "
            + (string)"formal/actual: "
            + to_string(formal_parameters.size()) + "/"
            + to_string(actual_parameters.size()) + ". ";
        error(
            message,
            ErrorCode::WRONG_PARAMS_NUM,
            function_call_node -> getToken());
    }

    // parameter number matched

    // visit each parameter
    for (AST * p : actual_parameters) {
        visit(p);
    }

    // put Function Symbol into ProcedureCall node
    function_call_node->setFunctionSymbol(*p_function_symbol);

    return Any();
}

Any SemanticAnalyzer::visitRead(AST * node ) {
    Read * p_read_node = dynamic_cast<Read *>(node);

    vector<Var *> read_vars = p_read_node->getReadVars();
    for (Var * p : read_vars) {
        visit(p);
    }

    return Any();
}

Any SemanticAnalyzer::visitWrite(AST * node ) {
    Write * p_write_node = dynamic_cast<Write *>(node);

    AST * p_expr = p_write_node->getExpr();
    visit(p_expr);

    return Any();
}

Any SemanticAnalyzer::visitIf(AST * node ) {
    If * p_if_node = dynamic_cast<If * >(node);

    AST * p_condition = p_if_node->getCondition();
    AST * p_body = p_if_node->getBody();
    AST * p_else = p_if_node->getElse();

    visit(p_condition);
    visit(p_body);
    if (p_else != nullptr) {
        visit(p_else);
    }

    return Any();
}

Any SemanticAnalyzer::visitWhile(AST * node ) {
    While * p_if_node = dynamic_cast<While * >(node);

    AST * p_condition = p_if_node->getCondition();
    AST * p_body = p_if_node->getBody();

    visit(p_condition);
    visit(p_body);

    return Any();
}

// ===== =====
// ===== ===== public
// ===== =====

void SemanticAnalyzer::analyze() {
    if (m_root == nullptr) return ;

    visit(m_root);
}

void SemanticAnalyzer::printBuildInTypeSymbolTable() {
	m_build_in_type_scope.print();
}

// ===== =====
// ===== ===== SemanticError
// ===== =====

SemanticError::SemanticError(
    const string & message,
    ErrorCode error_code,
    Token token) :
    Exception(message, error_code, token) {}

SemanticError::~SemanticError() {}

const string SemanticError::what() const {
    return "SemanticError met: <<" + m_msg + ">>";
}
} // namespace ESI
