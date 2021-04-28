/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-07 11:34:16
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-04-27 20:18:36
 * @Description  :
*********************************************/

#include <iostream>
#include "../inc/symbol.hpp"

using std::string;
using std::vector;

namespace ESI {

// ===== Symbol Class =====

Symbol::Symbol(string name, SymbolType type) :
    m_name(name), m_type(type) {}

Symbol::~Symbol() {}

string Symbol::getName() const {
    return m_name;
}
SymbolType Symbol::getType() const {
    return m_type;
}

string Symbol::strRepr() {
    SymbolCategory category = getCategory();
    string category_str;
    if (category == SymbolCategory::SYMBOL) {
        category_str = "Symbol<";
    }
    else if (category == SymbolCategory::BUILD_IN_TYPE_SYMBOL) {
        category_str = "Build-in-type-symbol<";
    }
    else if (category == SymbolCategory::VAR_SYMBOL) {
        category_str = "variable-symbol<";
    }
    else if (category == SymbolCategory::PROCEDURE_SYMBOL) {
        category_str = "procedure-symbol<";
    }

    // ===== =====
    if (m_type == SymbolType::NONE) {
        return (string)(category_str +
            "type : NONE, name : " + m_name + ">");
    }
    else if (m_type == SymbolType::INTEGER) {
        return (string)(category_str +
            "type : INTEGER, name : " + m_name + ">");
    }
    else if (m_type == SymbolType::REAL) {
        return (string)(category_str +
        "type : REAL, name : " + m_name + ">");
    }
    else {
        // Nothing else.
        return (string)"none";
    }
}

SymbolCategory Symbol::getCategory() const {
    return SymbolCategory::SYMBOL;
}

// ===== BuildInTypeSymbol Class =====

BuildInTypeSymbol::BuildInTypeSymbol(string name) :
    Symbol(name) {}

BuildInTypeSymbol::~BuildInTypeSymbol() {}

SymbolCategory BuildInTypeSymbol::getCategory() const {
    return SymbolCategory::BUILD_IN_TYPE_SYMBOL;
}

// ===== VarSymbol Class =====

VarSymbol::VarSymbol(string name, SymbolType type) :
    Symbol(name, type) {}

VarSymbol::~VarSymbol() {}

SymbolCategory VarSymbol::getCategory() const {
    return SymbolCategory::VAR_SYMBOL;
}

// ===== ProcedureSymbol Class =====

ProcedureSymbol::ProcedureSymbol(string name, void * p_procedure_symbol):
    Symbol(name), m_p_procedure_block(p_procedure_symbol) {
        m_parameters.clear();
    }

ProcedureSymbol::ProcedureSymbol(const ProcedureSymbol & obj) :
    Symbol(obj.m_name) {
        for (VarSymbol * p : obj.m_parameters) {
            m_parameters.push_back(new VarSymbol(*p));
        }

        m_p_procedure_block = obj.m_p_procedure_block;
    }

ProcedureSymbol::~ProcedureSymbol() {
    for (Symbol * p : m_parameters) {
        if (p != nullptr) {
            delete p;
            p = nullptr;
        }
    }
}

SymbolCategory ProcedureSymbol::getCategory() const {
    return SymbolCategory::PROCEDURE_SYMBOL;
}

void ProcedureSymbol::pushParameter(VarSymbol * param_node) {
    m_parameters.push_back(param_node);
}

void * ProcedureSymbol::getProcedureBlock() const {
    return m_p_procedure_block;
}

vector<VarSymbol *> ProcedureSymbol::getParams() {
    return m_parameters;
}

ProcedureSymbol & ProcedureSymbol::operator= (const ProcedureSymbol obj) {
    for (Symbol * p : m_parameters) {
        if (p != nullptr) {
            delete p;
            p = nullptr;
        }
    }
    m_parameters.clear();

    m_name = obj.m_name;

    for (VarSymbol * p : obj.m_parameters) {
        m_parameters.push_back(new VarSymbol(*p));
    }

    return *this;
}

} // namespace ESI
