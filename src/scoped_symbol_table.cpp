/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 10:18:07
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-05-08 16:24:30
 * @Description  :
*********************************************/
#include <iostream>

#include "../inc/scoped_symbol_table.hpp"

using std::string;

namespace ESI {

// ===== SymbolTable class =====

ScopedSymbolTable::ScopedSymbolTable(
    string scope_name,
    int scope_level,
    ScopedSymbolTable * enclosing_scope) :
	m_scope_name(scope_name),
    m_scope_level(scope_level),
    m_p_enclosing_scope(enclosing_scope) {

    m_map.clear();
}

// Copy constructor
ScopedSymbolTable::ScopedSymbolTable(const ScopedSymbolTable & obj) {
    if (obj.m_map.empty()) return ;

    m_scope_name = obj.getScopeName();
    m_scope_level = obj.getScopeLevel();

    // i is an iterator pointing a pair<string, Symbol * >.
    for (auto i : obj.m_map) {
        if (i.second != nullptr) {
            define(*i.second);
        }
    }
}

ScopedSymbolTable::~ScopedSymbolTable() {
    if (m_map.empty()) return ;

    for (auto i : m_map) {
        if (i.second != nullptr) {
            delete i.second;
            i.second = nullptr;
        }
    }
}

string ScopedSymbolTable::getScopeName() const {
    return m_scope_name;
}

int ScopedSymbolTable::getScopeLevel() const {
    return m_scope_level;
}

ScopedSymbolTable * ScopedSymbolTable::getEnclosingScope() const {
    return m_p_enclosing_scope;
}


void ScopedSymbolTable::print() const {
    using std::cout;
    using std::endl;

    cout << "scope name: " << m_scope_name
        << "\nlevel: " << m_scope_level
        << "\nenclosing scope: ";

    // Some scope like global scope do not have enclosing scope.
    if (m_p_enclosing_scope != nullptr) {
        cout << m_p_enclosing_scope->getScopeName() << endl;
    }
    else {
        cout << "NONE" << endl;
    }

    cout << "===== ===== ===== =====" << endl;

    if (m_map.empty()) return ;

    for (auto i : m_map) {
        if (i.second != nullptr) {
            cout <<  "["<< i.first
            << "] : " << i.second->strRepr() << endl;
        }
    }

    cout << "----- ----- ----- -----" << endl;
}

void ScopedSymbolTable::define(const Symbol & symbol) {
    SymbolCategory category = symbol.getCategory();
    string name = symbol.getName();
    int level = symbol.getLevel();
    SymbolType type = symbol.getType();

    if (category == SymbolCategory::SYMBOL) {
        m_map[name] = new Symbol(name, level, type);
    }
    else if (category == SymbolCategory::BUILD_IN_TYPE_SYMBOL) {
        m_map[name] = new BuildInTypeSymbol(name, level);
    }
    else if (category == SymbolCategory::VAR_SYMBOL) {
        m_map[name] = new VarSymbol(name, level, type);
    }
    else if (category == SymbolCategory::PROCEDURE_SYMBOL) {
        void * p_procedure_block =
            dynamic_cast<const ProcedureSymbol&>(symbol).getProcedureBlock();

        m_map[name] = new ProcedureSymbol(name, level, p_procedure_block);
    }
    else if (category == SymbolCategory::FUNCTION_SYMBOL) {
        const FunctionSymbol& function_symbol =
            dynamic_cast<const FunctionSymbol&>(symbol);

        void * p_function_block = function_symbol.getFunctionBlock();
        SymbolType function_type = function_symbol.getType();

        m_map[name] = new FunctionSymbol(
            name,
            level,
            function_type,
            p_function_block);
    }
    else {
        std::cout << "category not found" << std::endl;
        // Nothing else.
    }
}

Symbol * ScopedSymbolTable::lookup(
    string name,
    bool current_scope_only) const {
    if (m_map.find(name) == m_map.end()) {
        if (current_scope_only) {
            return nullptr;
        }
        else if (m_p_enclosing_scope == nullptr) {
            return nullptr;
        }
        else {
            return m_p_enclosing_scope->lookup(name);
        }
    }
    else {
        return m_map.at(name);
    }
}


} // namespace ESI
