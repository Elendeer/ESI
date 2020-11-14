/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 16:33:54
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-11-14 11:38:22
 * @Description  :
 *********************************************/

#include "../inc/interpreter.hpp"

#include <iostream>
#include <stdexcept>

namespace ESI {

Interpreter::Interpreter(Parser parser) : m_parser(parser) {}

/**
 * @description: It will transfer a funtion
 * to visit a node depends on type of the node.
 */
int Interpreter::visit(AST *node) {
    // THIS FUNCTION MUST BE CHANGED!!
    if (node->getType() == NodeType::NUM) {
        return visit_Num(node);

    } else if (node->getType() == NodeType::BINOP) {
        return visit_BinOp(node);

    } else if (node->getType() == NodeType::UNARYOP) {
        return visit_UnaryOp(node);
    }
    else if (node -> getType() == NodeType::ASSIGN) {
        visit_Assign(node);
    }
    else if (node -> getType() == NodeType::VAR) {
        return visit_Var(node);
    }
    else if (node -> getType() == NodeType::COMPOUND) {
        visit_Compound(node);
    }
    else if (node -> getType() == NodeType::NOOP) {
        visit_NoOp();
    }

    // nothing else
    return 0;
}

void Interpreter::generic_visit(AST *node) {
    throw std::runtime_error(
        (string) "No " + NodeTypeString[(int)node->getType()] + " type method");
}

int Interpreter::visit_UnaryOp(AST *node) {
    TokenType type = node->getToken().getType();
    if (type == TokenType::PLUS) {
        return +visit(node->getRight());

    } else if (type == TokenType::MINUS) {
        return -visit(node->getRight());

    } else { // nothing else
        return 0;
    }
}

int Interpreter::visit_BinOp(AST *node) {
    TokenType type = node->getToken().getType();
    if (type == TokenType::PLUS) {
        return visit(node->getLeft()) + visit(node->getRight());

    } else if (type == TokenType::MINUS) {
        return visit(node->getLeft()) - visit(node->getRight());

    } else if (type == TokenType::MUL) {
        return visit(node->getLeft()) * visit(node->getRight());

    } else if (type == TokenType::DIV) {
        return visit(node->getLeft()) / visit(node->getRight());

    } else { // nothing else
        return 0;
    }
}

int Interpreter::visit_Num(AST *node) {
    return node->getToken().getVal();
}

/*********************************************
 * Program about
 *********************************************/

void Interpreter::visit_Compound(AST *node) {
    for (AST *child : node->getChildren()) {
        visit(child);
    }
    return;
}

void Interpreter::visit_NoOp() {
    return;
}

void Interpreter::visit_Assign(AST *node) {
    using std::string;

    string var_name = dynamic_cast<Var *>(node->getLeft())->getVal();

    m_GLOBAL_SCOPE[var_name] = visit(node->getRight());
}

int Interpreter::visit_Var(AST *node) {
    std::string var_name = dynamic_cast<Var *>(node)->getVal();

    std::map<std::string, int>::iterator iter = m_GLOBAL_SCOPE.find(var_name);

    if (iter == m_GLOBAL_SCOPE.end()) {
        throw(std::runtime_error(
            "interpreter: Undefined Symble: " + var_name
            ));
    }

    return iter->second;
}

void Interpreter::interpret() {
    AST *tree = nullptr;
    try {
        tree = m_parser.parse();
    }
    catch (const std::runtime_error & error) {

        std::cout << "When building AST :" << std::endl;
        std::cout << "\t" << error.what() << std::endl;
        // std::cout << m_parser.getTmpRoot() << std::endl;

        if (m_parser.getTmpRoot() != nullptr) {
            delete m_parser.getTmpRoot();
            // std::cout << "tree deleted" << std::endl;
        }
        // else {
        //     std::cout << "tmp root is nullptr" << std::endl;
        // }

    }

    if (tree == nullptr) {
        return;
    }

    int result = -1;
    try {
        result = visit(tree);

        // 'result' is useless in fact.
        if (!result) {
            this -> printScope();
        }

        delete tree;
    }
    catch (const std::runtime_error & error) {

        std::cout << "When visiting AST :" << std::endl;
        std::cout  << "\t" << error.what() << std::endl;

        delete tree;
    }
}

void Interpreter::printScope() {
    std::cout << "----- Globle Scope -----" << std::endl;
    std::cout << "Var\tVal" << std::endl;
    if (!m_GLOBAL_SCOPE.empty()) {
        for (auto i = m_GLOBAL_SCOPE.begin(); i != m_GLOBAL_SCOPE.end(); ++ i) {
            std::cout << i->first << "\t" << i->second << std::endl;
        }
    }
}

} // namespace ESI
