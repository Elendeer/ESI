/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 10:18:07
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-08 15:37:32
 * @Description  :
*********************************************/
#include <iostream>

#include "../inc/symbol_table.hpp"

using std::string;

namespace ESI {

// ===== SymbolTable class =====

SymbolTable::SymbolTable() {
    m_map[(string)"INTEGER"] = new BuildInTypeSymbol("INTEGER");
    m_map[(string)"REAL"] = new BuildInTypeSymbol("REAL");
}
SymbolTable::~SymbolTable() {
    if (m_map.empty()) return ;

    for (auto i : m_map) {
        if (i.second != nullptr) {
            delete i.second;
        }
    }
}

// Copy constructor
SymbolTable::SymbolTable(const SymbolTable & obj) {
    if (obj.m_map.empty()) return ;

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

void SymbolTable::print() const {
    using std::cout;
    using std::endl;

    if (m_map.empty()) return ;

    for (auto i : m_map) {
        if (i.second != nullptr) {
            cout <<  "key : "<< i.first
            << "; symbol : " << i.second->strRepr() << endl;
        }
    }
}

void SymbolTable::define(Symbol * symbol) {
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

Symbol * SymbolTable::lookup(string name) const {
    if (m_map.find(name) == m_map.end()) return nullptr;

    return m_map.at(name);
}


} // namespace ESI