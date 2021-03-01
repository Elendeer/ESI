/*
 * @Author: Elendeer
 * @Date: 2020-06-05 16:09:33
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-05 20:52:53
 * @Description: file content
 */

#include "../inc/parser.hpp"

#include <iostream>
#include <stdexcept>

namespace ESI {

Parser::Parser(const Lexer &lexer) :
    m_lexer(lexer), mp_ast_root(nullptr) {

    m_current_token = m_lexer.get_next_token();
}
Parser::~Parser() {
}

void Parser::error() {
    throw std::runtime_error("Invalid Syntax");
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
        m_current_token = m_lexer.get_next_token();
    } else {
        error();
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
//          | LPAREN expr RPAREN
//          | variable
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
    else if (token.getType() == TokenType::LPAREN) {
        eat(TokenType::LPAREN);
        AST *node = expr();
        eat(TokenType::RPAREN);

        return node;
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

    while (m_current_token.getType() == TokenType::MUL
        || m_current_token.getType() == TokenType::INTEGER_DIV
        || m_current_token.getType() == TokenType::FLOAT_DIV) {

        if (m_current_token.getType() == TokenType::MUL) {
            eat(TokenType::MUL);
        }
        else if (m_current_token.getType() == TokenType::INTEGER_DIV) {
            eat(TokenType::INTEGER_DIV);
        }
        else {
            eat(TokenType::FLOAT_DIV);
        }

        node = new BinOp(node, token, factor());
    }

    return node;
}

// expr : term ((PLUS | MINUS) term)*
AST *Parser::expr() {
    AST *node = term();

    // For keeping current token.
    // m_current_token will change after function eat() is called.
    Token token = m_current_token;

    while (m_current_token.getType() == TokenType::PLUS
        || m_current_token.getType() == TokenType::MINUS) {

        if (m_current_token.getType() == TokenType::PLUS) {
            eat(TokenType::PLUS);
        }
        else {
            eat(TokenType::MINUS);
        }

        node = new BinOp(node, token, term());
    }

    return node;
}

/*********************************************
 * Programs about
*********************************************/

// program : PROGRAM variable SEMI block DOT
AST *Parser::program() {
    eat(TokenType::PROGRAM);
    AST * var_node = variable();
    // TODO: change the way of type changing.
    std::string program_name = ((Var *)var_node) -> getVal();
    eat(TokenType::SEMI);

    AST * block_node = block();
    eat(TokenType::DOT);

    return new Program(program_name, block_node);
}

// block : declarations compound_statement
AST * Parser::block() {
    std::vector<AST *> declaration_nodes = declarations();
    return new Block(declaration_nodes, compoundStatement());
}

// declarations : VAR (variable_declaration SEMI)+ | empty
std::vector<AST *> Parser::declarations() {
    std::vector<AST *> declarations;

    if (m_current_token.getType() == TokenType::VAR) {
        eat(TokenType::VAR);
        while (m_current_token.getType() == TokenType::ID) {
            // Pointors pointing to variable nodes(Var).
            std::vector<AST *> var_decl = variableDeclaration();

            for (auto variable_node : var_decl) {
                declarations.push_back(variable_node);
            }

            eat(TokenType::SEMI);
        }
    }

    return declarations;
}

// variable_declaration : ID (COMMA ID)* COLON type_spec
std::vector<AST *> Parser::variableDeclaration() {
    std::vector<AST *> var_nodes;

    // For m_current_token will change after function eat() is called.
    Token tmp_token = m_current_token;

    eat(TokenType::ID);
    var_nodes.push_back(new Var(tmp_token));

    while (m_current_token.getType() == TokenType::COMMA) {
        eat(TokenType::COMMA);
        tmp_token = m_current_token;
        eat(TokenType::ID);

        var_nodes.push_back(new Var(tmp_token));
    }
    eat(TokenType::COLON);

    // There is a memory allocation of a node inside function typeSpec(),
    // and it will return a pointer poiting to that.
    // Type node may be used more than one time (e.g. a, b : INTEGER),
    // so this node will be used as a template.
    // Delete this pointer on time is necessary.
    AST* p_type_node = typeSpec();

    std::vector<AST *> var_decl;
    for (auto p_var_node : var_nodes) {
        AST * tmp_p_type_node = new Type(p_type_node -> getToken());
        var_decl.push_back(new VarDecl(p_var_node, tmp_p_type_node));
    }

    delete p_type_node;

    return var_decl;
}

// type_spec : INTERGER | REAL
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
    else {
        error();
    }

    // useless.
    return nullptr;
}



// compound_statement : BEGIN statement_list END
AST *Parser::compoundStatement() {
    eat(TokenType::BEGIN);
    std::vector<AST *> nodes = statementList();
    eat(TokenType::END);

    AST *root = new Compound();

    for (AST *node : nodes) {
        root->pushChild(node);
    }

    return root;
}

// statement_list : statement
//                | statement SEMI statement_list
std::vector<AST *> Parser::statementList() {
    AST *node = statement();

    using std::vector;
    vector<AST *> result;
    result.push_back(node);

    // std::cout << TokenTypeString[(int)m_current_token.getType()] << std::endl;
    while (m_current_token.getType() == TokenType::SEMI) {
        eat(TokenType::SEMI);
        // std::cout << "Eat!" << std::endl;
        result.push_back(statement());
    }

    if (m_current_token.getType() == TokenType::ID) {
        error();
        // return result;
    }

    return result;
}

// statement : compound_statement
//          | assignment_statement
//          | empty
AST *Parser::statement() {
    AST *node = nullptr;
    if (m_current_token.getType() == TokenType::BEGIN) {
        node = compoundStatement();

    } else if (m_current_token.getType() == TokenType::ID) {
        node = assignmentStatement();

    } else {
        node = empty();
    }

    return node;
}

// assignment_statement : variable ASSIGN expr
AST *Parser::assignmentStatement() {
    AST *left = variable();
    Token token = m_current_token;

    eat(TokenType::ASSIGN);

    AST *right = expr();

    AST *node = new Assign(left, token, right);
    return node;
}

// variable : ID
AST *Parser::variable() {
    AST *node = new Var(m_current_token);

    // TODO: mark for the first new
    mp_ast_root = node;

    eat(TokenType::ID);
    return node;
}

// An empty production.
AST *Parser::empty() {
    return new NoOp();
}

AST *Parser::parse() {
    mp_ast_root = program();

    // TODO: exam the necessity.
    if (m_current_token.getType() != TokenType::eEOF) {
        error();
    }

    return mp_ast_root;
}

AST * Parser::getAstRoot() const {
    return mp_ast_root;
}

} // namespace ESI
