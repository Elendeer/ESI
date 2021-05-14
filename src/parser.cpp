/*
 * @Author: Elendeer
 * @Date: 2020-06-05 16:09:33
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-05 20:52:53
 * @Description: Implement of parser.
 *      为了保证AST构建的过程中不发生内存泄漏，
 *      本文件内的所有根据语法构建AST的函数应该满足下列标准：
 *      - 函数内通过new或者函数获得节点之后还有函数可能抛出异常时，
 *          用try-catch捕获，
 *          从而将已经new的节点及时delete。
 *      - 函数内保证异常触发后持续上抛，即使本函数new的节点已经全部被delete。
 *      - 异常信息推迟到parsing的最上层才显示。
 *
 *      程序中的大多数try-catch是依照上述原则设计的，在阅读代码时可以
 *      根据上述原则来理解它们的作用。
 *
 *      To ensure that there are no memory leaks during the AST build
 *      process,
 *      all functions in this file that build AST according the grammar
 *      should meet the following criteria:
 *      - If there is an exception that may be thrown by the function
 *          after a node is newed (or gained from another function),
 *          try-catch is used to delete the node
 *          that has already been newed.
 *      - The function guarantees that it will continue to throw
 *          after the exception is triggered, even if all the nodes
 *          newed by this function have been deleted.
 *      -Exception message showing is deferred until the uppermost level
 *          of the parsing.
 *
 *      Most try-catches in this file are designed according to
 *      these criteria, you can use them to understand what those
 *      try-catches do when you read the code.
 */

#include "../inc/parser.hpp"

#include <iostream>
#include <stdexcept>

using std::string;
using std::vector;

namespace ESI {

// May throw exception when initing.
Parser::Parser(const Lexer &lexer) :
    m_lexer(lexer), mp_ast_root(nullptr) {

    m_current_token = m_lexer.getNextToken();
}
Parser::~Parser() {
}

void Parser::error(
        string message,
        ErrorCode error_code,
        Token token) {

            throw ParserError(message, error_code, token);
        }

//  Compare the current token type with the passed token
//  type and if they match then "eat" the current token
//  and assign the next token to the this->m_current_token,
//  otherwise throw an exception.
//
//  Might throw exceptions in Lexer::error() or
//  Parser::error().
void Parser::eat(TokenType token_type) {
    if (m_current_token.getType() == token_type) {
        m_current_token = m_lexer.getNextToken();
    }
    else {
        error(
            "Invailid Syntax : Unexpected token.\texpected "
            + Token::map_token_type_string.at(token_type)
            + ", met "
            + Token::map_token_type_string.at(m_current_token.getType())
            + ". ",
            ErrorCode::UNEXPECTED_TOKEN,
            m_current_token
        );
    }
}

/*********************************************
 * Arithmetic expressions about
*********************************************/

// The next three functions are all parts of parser.
// Based on grammar.
// factor : PLUS factor
//          | MINUS factor
//          | INTEGER_CONST
//          | REAL_CONST
//          | STRING
//          | TRUE
//          | FALSE
//          | LPAREN relational_expr RPAREN
//          | variable
//          | function_call
// Memmory allocations inside, may thorw exceptions.
AST *Parser::factor() {
    // For keeping current token.
    // m_current_token will change after function eat() is called.
    Token token = m_current_token;

    if (token.getType() == TokenType::PLUS) {
        eat(TokenType::PLUS);

        return new UnaryOp(token, factor());
    }
    else if (token.getType() == TokenType::MINUS) {
        eat(TokenType::MINUS);

        return new UnaryOp(token, factor());
    }
    else if (token.getType() == TokenType::INTEGER_CONST) {
        eat(TokenType::INTEGER_CONST);

        return new Num(token);
    }
    else if (token.getType() == TokenType::REAL_CONST) {
        eat(TokenType::REAL_CONST);

        return new Num(token);
    }
    else if (token.getType() == TokenType::STRING) {
        eat(TokenType::STRING);

        return new String(token);
    }
    else if (token.getType() == TokenType::TRUE) {
        eat(TokenType::TRUE);

        return new Boolean(token);
    }
    else if (token.getType() == TokenType::FALSE) {
        eat(TokenType::FALSE);

        return new Boolean(token);
    }
    else if (token.getType() == TokenType::LPAREN) {
        eat(TokenType::LPAREN);

        AST * node = relationalExpr();

        try {
            eat(TokenType::RPAREN);
        }
        catch (const ParserError & error) {
            if (node != nullptr) {
                delete node;
                node = nullptr;
            }
            throw error;
        }

        return node;
    }
    else if (token.getType() == TokenType::ID
        && m_lexer.getCurrentChar() == '(') {
            return functionCall();
    }
    else {
        return variable();
    }
}

// term : factor((MUL | INTEGER_DIV | FLOAT_DIV) factor)*
AST *Parser::term() {
    AST *node = factor();

    // For keeping current token.
    // m_current_token will change after function eat() is called.
    Token token = m_current_token;

    try {

    while (m_current_token.getType() == TokenType::MUL
        || m_current_token.getType() == TokenType::INTEGER_DIV
        || m_current_token.getType() == TokenType::FLOAT_DIV) {

            eat(m_current_token.getType());
            node = new BinOp(node, token, factor());
        }

    return node;

    } // try
    catch (const ParserError & error) {
        if (node != nullptr) delete node;
        throw error;
    }
}

// expr : term ((PLUS | MINUS) term)*
AST *Parser::expr() {
    AST *node = term();

    // For keeping current token.
    // m_current_token will change after function eat() is called.
    Token token = m_current_token;

    try {

    while (m_current_token.getType() == TokenType::PLUS
        || m_current_token.getType() == TokenType::MINUS) {

            eat(m_current_token.getType());
            node = new BinOp(node, token, term());
        }

    return node;

    } // try
    catch (const ParserError & error) {
        if (node != nullptr) delete node;
        throw error;
    }
}

/*********************************************
 * Programs about
*********************************************/

// program : PROGRAM variable SEMI block DOT
AST *Parser::program() {
    eat(TokenType::PROGRAM);
    AST * var_node = variable();
    std::string program_name = dynamic_cast<Var *>(var_node) -> getVarName();

    try {
        eat(TokenType::SEMI);
    }
    catch (const ParserError & error) {
        if (var_node != nullptr) delete var_node;
        throw error;
    }

    AST * block_node = nullptr;
    try {
        block_node = block();
        eat(TokenType::DOT);
    }
    catch (const ParserError & error) {
        if (var_node != nullptr) delete var_node;
        if (block_node != nullptr) delete block_node;
        throw error;
    }


    return new Program(program_name, block_node);
}

// block : declarations compound_statement
AST * Parser::block() {
    vector<AST *> declaration_nodes = declarations();
    AST * compound_statement_node = nullptr;

    try {
        compound_statement_node = compoundStatement();

        return new Block(declaration_nodes, compound_statement_node);
    }
    catch (const ParserError & error) {
        if (!declaration_nodes.empty())
            for (auto p : declaration_nodes)
                if (p != nullptr)
                    delete p;
        if (compound_statement_node != nullptr)
            delete compound_statement_node;

        throw error;
    }

}

// declarations : (VAR (variable_declaration SEMI)+)?
//     (procedure_declaration | function_declaration)*
vector<AST *> Parser::declarations() {
    vector<AST *> declarations;

    try {

    // declarations : (VAR (variable_declaration SEMI)+)?
    // ? for one time or none.
    if (m_current_token.getType() == TokenType::VAR) {
        eat(TokenType::VAR);

        while (m_current_token.getType() == TokenType::ID) {
            // Pointors pointing to variable nodes(Var).
            std::vector<AST *> var_decl = variableDeclaration();

            for (auto variable_node : var_decl) {
                declarations.push_back(variable_node);
            }

            eat(TokenType::SEMI);
        } // while

    } // while

    // (procedure_declaration | function_declaration)*
    while (m_current_token.getType() == TokenType::PROCEDURE
        || m_current_token.getType() == TokenType::FUNCTION) {
            if (m_current_token.getType() == TokenType::PROCEDURE) {
                AST * procedure_decl_node = procedureDeclaration();
                declarations.push_back(procedure_decl_node);
            }
            else { // function
                AST * function_decl_node = functionDeclaration();
                declarations.push_back(function_decl_node);
            }
    } // while


    } // try
    catch (const ParserError & error) {

        if (!declarations.empty())
            for (auto p : declarations)
                if (p != nullptr)
                    delete p;

        throw error;
    }


    return declarations;
}

// variable_declaration : ID (COMMA ID)* COLON type_spec
vector<AST *> Parser::variableDeclaration() {
    vector<AST *> var_nodes;

    // For m_current_token will change after function eat() is called.
    Token tmp_token = m_current_token;
    AST* p_tmp_type_node = nullptr;

    eat(TokenType::ID);
    var_nodes.push_back(new Var(tmp_token));

    try {
        while (m_current_token.getType() == TokenType::COMMA) {
            eat(TokenType::COMMA);
            tmp_token = m_current_token;
            eat(TokenType::ID);

            var_nodes.push_back(new Var(tmp_token));
        }
        eat(TokenType::COLON);

        // There is a memory allocation of a node inside function typeSpec()
        // and it will return a pointer poiting to that.
        // Type node may be used more than one time (e.g. a, b : INTEGER),
        // so this node will be used as a template.
        // Delete this pointer on time is necessary.
        p_tmp_type_node = typeSpec();
    } // try
    catch (const ParserError & error ) {
        if (!var_nodes.empty())
            for (auto p : var_nodes)
                if (p != nullptr) {
                    delete p;
                    p = nullptr;
                }
        throw error;
    }

    vector<AST *> var_decl;

    try {
        for (auto p_var_node : var_nodes) {
            AST * p_type_node = new Type(p_tmp_type_node -> getToken());
            var_decl.push_back(new VarDecl(p_var_node, p_type_node));
        }

        delete p_tmp_type_node;
        p_tmp_type_node = nullptr;

        return var_decl;
    }// try
    catch (const ParserError & error) {
        if (p_tmp_type_node != nullptr) {
            delete p_tmp_type_node;
            p_tmp_type_node = nullptr;
        }
        if (!var_decl.empty())
            for (auto p : var_decl)
                if (p != nullptr) {
                    delete p;
                    p = nullptr;
                }
        throw error;
    }

}

// procedure_declaration:
// PROCEDURE ID (LPAREN formal_parameter_list RPAREN)? SEMI block SEMI
AST * Parser::procedureDeclaration() {
    AST *  procedure_node = nullptr;

    // Procedure daclarations will use it.
    AST * p_block = nullptr;
    // Procedure daclarations will use it.
    // Empty vector by default.
    vector<AST *> params;
    params.clear();

    try {
        eat(TokenType::PROCEDURE);
        string name = Any::anyCast<string>(m_current_token.getVal());
        eat(TokenType::ID);

        if (m_current_token.getType() == TokenType::LPAREN) {
            eat(TokenType::LPAREN);
            params = formalParameterList();
            eat(TokenType::RPAREN);
        }

        eat(TokenType::SEMI);

        p_block = block();
        eat(TokenType::SEMI);
        procedure_node = new ProcedureDecl(name, params, p_block);

        // If not, will cause a sigment fault of duplicate deleting.
        // (when error is met).
        p_block = nullptr;

    } // try
    catch (const ParserError & error) {
        if (p_block != nullptr) {
            delete p_block;
            p_block = nullptr;
        }

        if (!params.empty())
            for (auto p : params)
                if (p != nullptr) {
                    delete p;
                    p = nullptr;
                }

        if (procedure_node != nullptr) {
            delete procedure_node;
            procedure_node = nullptr;
        }

        throw error;
    }

    return procedure_node;
}

// type_spec : INTERGER | REAL | STRING | BOOL
AST * Parser::typeSpec() {
    Token token = m_current_token;
    if (m_current_token.getType() == TokenType::INTEGER) {
        eat(TokenType::INTEGER);
        return new Type(token);
    }
    else if (m_current_token.getType() == TokenType::REAL) {
        eat(TokenType::REAL);
        return new Type(token);
    }
    else if (m_current_token.getType() == TokenType::STRING) {
        eat(TokenType::STRING);
        return new Type(token);
    }
    else if (m_current_token.getType() == TokenType::BOOLEAN) {
        eat(TokenType::BOOLEAN);
        return new Type(token);
    }
    else {
        error("Invailid Syntax : Expected typeSpec token");
    }

    // useless.
    return nullptr;
}



// compound_statement : BEGIN statement_list END
AST *Parser::compoundStatement() {
    eat(TokenType::BEGIN);
    std::vector<AST *> nodes = statementList();
    try {
        eat(TokenType::END);
        Compound *root = new Compound();

        for (AST *node : nodes) {
            root->pushChild(node);
        }

        // Return a AST pointes pointing to a Compound object.
        return root;
    }
    catch (const ParserError & error) {
        if (!nodes.empty())
            for (auto p : nodes)
                if (p != nullptr) {
                    delete p;
                    p = nullptr;
                }
        throw error;
    }
}

// statement_list : statement
//                | statement SEMI statement_list
vector<AST *> Parser::statementList() {
    AST *node = statement();

    vector<AST *> result;
    result.push_back(node);

    try {
        while (m_current_token.getType() == TokenType::SEMI) {
            eat(TokenType::SEMI);
            // std::cout << "Eat!" << std::endl;
            result.push_back(statement());
        }
    }
    catch (const ParserError & error) {
        if (!result.empty())
            for (auto p : result)
                if (p != nullptr) {
                    delete p;
                    p = nullptr;
                }
        throw error;
    }


    return result;
}

// statement : compound_statement
//          | assignment_statement
//          | procedure_call_statement
//          | read_statement
//          | write_statement
//          | empty
AST *Parser::statement() {
    AST *node = nullptr;
    if (m_current_token.getType() == TokenType::BEGIN) {
        node = compoundStatement();
    }
    else if (m_current_token.getType() == TokenType::ID
            && m_lexer.getCurrentChar() == '(') {
        node = procedureCallStatement();
    }
    else if (m_current_token.getType() == TokenType::ID) {
        node = assignmentStatement();
    }
    else if (m_current_token.getType() == TokenType::READ) {
        node = readStatement();
    }
    else if (m_current_token.getType() == TokenType::WRITE
            || m_current_token.getType() == TokenType::WRITELN) {
        node = writeStatement();
    }
    else {
        node = empty();
    }

    return node;
}

// assignment_statement : variable ASSIGN relational_expr
AST *Parser::assignmentStatement() {
    AST *left = variable();
    Token token = m_current_token;

    try {
        eat(TokenType::ASSIGN);
    }
    catch (const ParserError & error) {
        if (left != nullptr) {
            delete left;
            left = nullptr;
        }
    }

    AST *right = nullptr;
    try {
        right = relationalExpr();
    }
    catch (const ParserError & error) {
        if (left != nullptr) delete left;
        throw error;
    }

    try {
        AST *node = new Assign(left, token, right);
        return node;
    }
    catch (const ParserError & error) {
        if (left != nullptr) delete left;
        if (right != nullptr) delete right;
        throw error;
    }
}

// variable : ID
AST *Parser::variable() {
    AST *node = new Var(m_current_token);

    try {
        eat(TokenType::ID);
        return node;
    }
    catch (const ParserError & error) {
        if (node != nullptr) {
            delete node;
            node = nullptr;
        }
        throw error;
    }
}

// An empty production.
AST *Parser::empty() {
    return new NoOp();
}

// ===== =====

// formal_parameter_list : formal_parameters
//         | formal_parameters SEMI formal_parameter_list
vector<AST *> Parser::formalParameterList() {
    vector<AST *> params;
    params.clear();
    params = formalParameters();

    if (m_current_token.getType() == TokenType::SEMI) {
        eat(TokenType::SEMI);
        try {
            vector<AST *> tmp = formalParameterList();
            for (auto p : tmp) {
                params.push_back(p);
            }
        }
        catch (const ParserError & error) {
            if (!params.empty())
                for (auto p : params)
                    if (p != nullptr) delete p;
            throw error;
        }
    }

    return params;
}

// formal_parameters : ID (COMMA ID)* COLON type_spec
vector<AST *> Parser::formalParameters() {
    vector<AST *> var_nodes;

    // For m_current_token will change after function eat() is called.
    Token tmp_token = m_current_token;
    AST* p_type_node = nullptr;

    eat(TokenType::ID);
    var_nodes.push_back(new Var(tmp_token));

    try {
        while (m_current_token.getType() == TokenType::COMMA) {
            eat(TokenType::COMMA);
            tmp_token = m_current_token;
            eat(TokenType::ID);

            var_nodes.push_back(new Var(tmp_token));
        }
        eat(TokenType::COLON);

        // There is a memory allocation of a node inside function typeSpec()
        // and it will return a pointer poiting to that.
        // Type node may be used more than one time (e.g. a, b : INTEGER),
        // so this node will be used as a template.
        // Delete this pointer on time is necessary.
        p_type_node = typeSpec();
    } // try
    catch (const ParserError & error ) {
        if (!var_nodes.empty())
            for (auto p : var_nodes)
                if (p != nullptr) {
                    delete p;
                    p = nullptr;
                }
        throw error;
    }

    vector<AST *> param_decl;

    try {
        for (auto p_var_node : var_nodes) {
            AST * tmp_p_type_node = new Type(p_type_node -> getToken());
            param_decl.push_back(new Param(p_var_node, tmp_p_type_node));
        }

        delete p_type_node;
        p_type_node = nullptr;

        return param_decl;
    }// try
    catch (const ParserError & error) {
        if (p_type_node != nullptr) {
            delete p_type_node;
            p_type_node = nullptr;
        }
        if (!param_decl.empty())
            for (auto p : param_decl)
                if (p != nullptr) {
                    delete p;
                    p = nullptr;
                }
        throw error;
    }
}


// procedure_call_statement :
//     ID LPAREN (relational_expr(COMMA relational_expr)*)? RPAREN
AST * Parser::procedureCallStatement() {
    // This token will put into ProcedureCall node.
    // It's the token of id of procedure name.
    Token token = m_current_token;
    string proceudure_name = m_current_token.getVal();

    eat(TokenType::ID);
    eat(TokenType::LPAREN);

    vector<AST *> actual_parameters;

    try {
        if (m_current_token.getType() != TokenType::RPAREN) {
            AST * tmp_actual_param = relationalExpr();
            actual_parameters.push_back(tmp_actual_param);
        }

        while (m_current_token.getType() == TokenType::COMMA) {
            eat(TokenType::COMMA);
            AST * tmp_actual_param = relationalExpr();
            actual_parameters.push_back(tmp_actual_param);
        }

        eat(TokenType::RPAREN);

        return new ProcedureCall(
            proceudure_name,
            actual_parameters,
            token);
    }
    catch (ParserError & error) {
        for (AST * p : actual_parameters) {
            if (p != nullptr) {
                delete p;
                p = nullptr;
            }
        }

        throw error;
    }
}


// function_declaration :
//     FUNCTION ID (LPAREN formal_parameter_list RPAREN)?
//     COLON type_spec SEMI block SEMI
AST * Parser::functionDeclaration() {
    AST *  function_decl_node = nullptr;

    // Function daclarations will use them.
    AST * p_block = nullptr;
    AST * p_type_node = nullptr;

    // Function daclarations will use it.
    // Empty vector by default.
    vector<AST *> params;
    params.clear();

    try {
        eat(TokenType::FUNCTION);
        string name = Any::anyCast<string>(m_current_token.getVal());
        eat(TokenType::ID);

        if (m_current_token.getType() == TokenType::LPAREN) {
            eat(TokenType::LPAREN);
            params = formalParameterList();
            eat(TokenType::RPAREN);
        }

        eat(TokenType::COLON);

        p_type_node = typeSpec();

        eat(TokenType::SEMI);

        p_block = block();
        eat(TokenType::SEMI);
        function_decl_node = new FunctionDecl(
            name, params, p_type_node,  p_block);

        // If not, will cause a sigment fault of duplicate deleting.
        // (when error is met).
        p_type_node = nullptr;
        p_block = nullptr;

    } // try
    catch (const ParserError & error) {
        if (p_type_node != nullptr) {
            delete p_type_node;
            p_type_node = nullptr;
        }

        if (p_block != nullptr) {
            delete p_block;
            p_block = nullptr;
        }

        if (!params.empty())
            for (auto p : params)
                if (p != nullptr) {
                    delete p;
                    p = nullptr;
                }

        if (function_decl_node != nullptr) {
            delete function_decl_node;
            function_decl_node = nullptr;
        }

        throw error;
    }

    return function_decl_node;

}

// function_call :
//     ID LPAREN (relational_expr(COMMA relatinal_expr)*)? RPAREN
AST * Parser::functionCall() {
    // This token will put into FunctionCall node.
    // It's the token of id of function name.
    Token token = m_current_token;
    string function_name = m_current_token.getVal();

    eat(TokenType::ID);
    eat(TokenType::LPAREN);

    vector<AST *> actual_parameters;

    try {
        if (m_current_token.getType() != TokenType::RPAREN) {
            AST * tmp_actual_param = relationalExpr();
            actual_parameters.push_back(tmp_actual_param);
        }

        while (m_current_token.getType() == TokenType::COMMA) {
            eat(TokenType::COMMA);
            AST * tmp_actual_param = relationalExpr();
            actual_parameters.push_back(tmp_actual_param);
        }

        eat(TokenType::RPAREN);

        return new FunctionCall(
            function_name,
            actual_parameters,
            token);
    }
    catch (ParserError & error) {
        for (AST * p : actual_parameters) {
            if (p != nullptr) {
                delete p;
                p = nullptr;
            }
        }

        throw error;
    }
}

// read_statement :
//     READ LPAREN ID (COMMA ID)* RPAREN
AST * Parser::readStatement() {
    eat(TokenType::READ);
    eat(TokenType::LPAREN);

    vector<Var *> read_vars;
    Token id_token = m_current_token;
    eat(TokenType::ID);

    try {
        read_vars.push_back(new Var(id_token));

        while (m_current_token.getType() == TokenType::COMMA) {
            eat(TokenType::COMMA);
            Token id_token = m_current_token;
            eat(TokenType::ID);
            read_vars.push_back(new Var(id_token));
        }

        eat(TokenType::RPAREN);

        return new Read(read_vars);
    }
    catch (ParserError & error) {
        for (Var * p : read_vars) {
            if (p != nullptr) {
                delete p;
                p = nullptr;
            }
        } // for

        throw error;
    } // catch

}

// write_statement :
//     (WRITE | WRITELN) LPAREN relational_expr RPAREN
AST * Parser::writeStatement() {
    bool is_writeln = false;
    if (m_current_token.getType() == TokenType::WRITE) {
        eat(TokenType::WRITE);
    }
    else {
        eat(TokenType::WRITELN);
        is_writeln = true;
    }

    eat(TokenType::LPAREN);

    AST * p_expr = nullptr;

    try {
        p_expr = relationalExpr();
        eat(TokenType::RPAREN);

        return new Write(p_expr, is_writeln);
    }
    catch (ParserError & error) {
        if (p_expr != nullptr) {
            delete p_expr;
            p_expr = nullptr;
        }

        throw error;
    }
}

// relational_expr : expr ((EQUAL | NOT_EQUAL
//                     | LESS_THAN | LESS_THAN_OR_EQUAL_TO
//                     | GREATER_THAN | GREATER_THAN_OR_EQUAL_TO) expr)*
AST * Parser::relationalExpr() {
    AST * p_node = expr();

    Token token = m_current_token;

    try {
        // while is relational operator
        if (m_current_token.getType() == TokenType::EQUAL
            || m_current_token.getType() == TokenType::NOT_EQUAL
            || m_current_token.getType() == TokenType::LESS_THAN
            || m_current_token.getType()
                == TokenType::LESS_THAN_OR_EQUAL_TO
            || m_current_token.getType() == TokenType::GREATER_THAN
            || m_current_token.getType()
                == TokenType::GREATER_THAN_OR_EQUAL_TO) {

                    eat(m_current_token.getType());

                    p_node = new BinOp(p_node, token, expr());
                }

        return p_node;
    }
    catch (LexerError & error) {
        if (p_node != nullptr) {
            delete p_node;
            p_node = nullptr;
        }

        throw error;
    }
}

// ===== =====
// ===== ===== Public
// ===== =====

AST *Parser::parse() {
    using std::cout;
    using std::endl;

    try {
        // Start parsing.
        // May throw exception when parsing.
        mp_ast_root = program();

        // TODO: exam the necessity.
        if (m_current_token.getType() != TokenType::eEOF) {
            error("Parsing error : no EOF token met.");
        }

        return mp_ast_root;

    }
    catch (const ParserError &error) {

        cout << "When building AST :" << endl;
        cout << "\t" << error.what() << endl;
        // std::cout << m_parser.getAstRoot() << std::endl;

        if (mp_ast_root == nullptr) {
            cout << "ast root is empty." << endl;
        }

        return nullptr;
    }
}

AST * Parser::getAstRoot() const {
    return mp_ast_root;
}


// ===== =====
// ===== ===== ParserError
// ===== =====

ParserError::ParserError(
        const string & message,
        ErrorCode error_code,
        Token token) :
        Exception(message, error_code, token) {}

ParserError::~ParserError() {}

const string ParserError::what() const {
    return "ParserError met: <<" + m_msg + ">>";
}

} // namespace ESI
