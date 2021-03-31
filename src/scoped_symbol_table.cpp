/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 10:18:07
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-17 16:34:31
 * @Description  :
*********************************************/
#include <iostream>

#include "../inc/scoped_symbol_table.hpp"

using std::string;

namespace ESI {

// ===== SymbolTable class =====

ScopedSymbolTable::ScopedSymbolTable(string scope_name, int scope_level) 
	: m_scope_name(scope_name), m_scope_level(scope_level) {

    m_map.clear();
}
ScopedSymbolTable::~ScopedSymbolTable() {
    if (m_map.empty()) return ;

    for (auto i : m_map) {
        if (i.second != nullptr) {
            delete i.second;
        }
    }
}

// Copy constructor
ScopedSymbolTable::ScopedSymbolTable(const ScopedSymbolTable & obj) {
    if (obj.m_map.empty()) return ;

    m_scope_name = obj.getScopeName();
    m_scope_level = obj.getScopeLevel();

    // i is an iterator pointing a pair<string, Symbol * >.
    for (auto i : obj.m_map) {
        if (i.second != nullptr) {
            SymbolCategory category = i.second->getCategory();
            string name = i.first; // the same with i.second->getName()
            SymbolType type = i.second->getType();

            if (category == SymbolCategory::SYMBOL) {
                m_map[name] = new Symbol(name, type);
            }
            else if (category == SymbolCategory::BUILD_IN_TYPE_SYMBOL) {
                m_map[name] = new BuildInTypeSymbol(name);
            }
            else if (category == SymbolCategory::VAR_SYMBOL) {
                m_map[name] = new VarSymbol(name, type);
            }
            else {
                // Nothing else.
                continue;
            }
        }
    }

}

string ScopedSymbolTable::getScopeName() const {
    return m_scope_name;
}

int ScopedSymbolTable::getScopeLevel() const {
    return m_scope_level;
}


void ScopedSymbolTable::print() const {
    using std::cout;
    using std::endl;

    cout << "scope: " << m_scope_name << "; level: " << m_scope_level << endl;
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

void ScopedSymbolTable::define(Symbol * symbol) {
    SymbolCategory category = symbol->getCategory();
    string name = symbol->getName();
    SymbolType type = symbol->getType();

    if (category == SymbolCategory::SYMBOL) {
        m_map[name] = new Symbol(name, type);
    }
    else if (category == SymbolCategory::BUILD_IN_TYPE_SYMBOL) {
        m_map[name] = new BuildInTypeSymbol(name);
    }
    else if (category == SymbolCategory::VAR_SYMBOL) {
        m_map[name] = new VarSymbol(name, type);
    }
    else {
        // Nothing else.
    }
}

Symbol * ScopedSymbolTable::lookup(string name) const {
    if (m_map.find(name) == m_map.end()) return nullptr;

    return m_map.at(name);
}


} // namespace ESI
