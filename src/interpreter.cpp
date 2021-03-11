/*********************************************
 * @Author       : Elendeer
 * @Date         : 2020-06-05 16:33:54
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-08 21:31:14
 * @Description  :
 *********************************************/

#include "../inc/interpreter.hpp"

#include <iostream>
#include <stdexcept>

using std::string;

namespace ESI {

Interpreter::Interpreter(AST * root)
    : NodeVisitor(root) {}

Interpreter::~Interpreter() {}

Any Interpreter::visit(AST *node) {

    if (node == nullptr) {
        return 0;
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
    else {
        // nothing else
        // TODO: exception
        return -1;
    }
    return -1;
}

// void Interpreter::generic_visit(AST *node) {
//     throw std::runtime_error(
//         (string) "No " + node->getTypeString() + " type method");
// }

Any Interpreter::visit_UnaryOp(AST *node) {
    TokenType type = node->getToken().getType();
    if (type == TokenType::PLUS) {
        return +visit(node->getRight());

    } else if (type == TokenType::MINUS) {
        return -visit(node->getRight());

    } else {
        // nothing else
        // TODO: exception
        return Any();
    }
}

Any Interpreter::visit_BinOp(AST *node) {
    TokenType type = node->getToken().getType();
    if (type == TokenType::PLUS) {
        return visit(node->getLeft()) + visit(node->getRight());
    } else if (type == TokenType::MINUS) {
        return visit(node->getLeft()) - visit(node->getRight());
    } else if (type == TokenType::MUL) {
        return visit(node->getLeft()) * visit(node->getRight());
    } else if (type == TokenType::INTEGER_DIV) {
        return visit(node->getLeft()) / visit(node->getRight());
    } else if (type == TokenType::FLOAT_DIV) {
        return visit(node->getLeft()) / visit(node->getRight());
    } else {
        // nothing else
        // TODO: exception
        return Any();
    }
}

Any Interpreter::visit_Num(AST *node) {
    if (node->getToken().getType() == TokenType::INTEGER_CONST) {
        return node->getToken().getVal();
    } else if (node->getToken().getType() == TokenType::REAL_CONST) {
        return node->getToken().getVal();
    } else {
        // nothing else
        // TODO: exception
        return Any();
    }
}

/*********************************************
 * Program about
 *********************************************/

Any Interpreter::visit_Compound(AST *node) {
    for (AST *child : node->getChildren()) {
        visit(child);
    }
    return Any();
}

Any Interpreter::visit_NoOp() {
    return Any();
}

Any Interpreter::visit_Assign(AST *node) {
    using std::string;

    string var_name = dynamic_cast<Var *>(node->getLeft())->getVal();

    m_GLOBAL_SCOPE[var_name] = visit(node->getRight());

    return Any();
}

Any Interpreter::visit_Var(AST *node) {
    std::string var_name = dynamic_cast<Var *>(node)->getVal();

    std::map<std::string, Any>::iterator iter = m_GLOBAL_SCOPE.find(var_name);

    if (iter == m_GLOBAL_SCOPE.end()) {
        throw(std::runtime_error(
            "interpreter: Undefined Symble: " + var_name));
    }

    return iter->second;
}

Any Interpreter::visitProgram(AST *node) {
    return visit(node->getChildren().front());
}

Any Interpreter::visitBlock(AST *node) {
    for (auto p : node->getChildren()) {
        visit(p);
    }

    return Any();
}

Any Interpreter::visitVarDecl(AST *node) {
    // Do nothing.
    if (node != nullptr) {
        return Any();
    }
    return Any();
}

Any Interpreter::visitType(AST *node) {
    // Do nothing.
    if (node != nullptr) {
        return Any();
    }

    return Any();
}

void Interpreter::interpret() {
    if (m_root == nullptr) {
        return ;
    }

    try {
        Any result = visit(m_root);

        // std::cout << "result: " << result << std::endl;
        // 'result' is useless in fact.
        this->printScope();

    } catch (const std::runtime_error &error) {

        std::cout << "When visiting AST :" << std::endl;
        std::cout << "\t" << error.what() << std::endl;
    }
}

void Interpreter::printScope() {
    using std::cout;
    using std::endl;

    cout << "----- Globle Scope -----" << endl;
    cout << "Var\tVal" << endl;
    if (!m_GLOBAL_SCOPE.empty()) {
        for (auto i = m_GLOBAL_SCOPE.begin(); i != m_GLOBAL_SCOPE.end(); ++i) {
            cout << i -> first << "\t" << i -> second << endl;
        }
    }
}

} // namespace ESI
