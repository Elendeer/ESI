/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-07 11:34:16
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-08 15:05:19
 * @Description  :
*********************************************/

#include <iostream>
#include "../inc/symbol.hpp"

using std::string;
using std::cout;

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
        category_str = "<Symbol>";
    }
    else if (category == SymbolCategory::BUILD_IN_TYPE_SYMBOL) {
        category_str = "<Build-in-type-symbol>";
    }
    else if (category == SymbolCategory::VAR_SYMBOL) {
        category_str = "<variable-symbol>";
    }
    // ===== =====
    if (m_type == SymbolType::NONE) {
        return (string)(category_str + "type : NONE, name : " + m_name);
    }
    else if (m_type == SymbolType::INTEGER) {
        return (string)(category_str + "type : INTEGER, name : " + m_name);
    }
    else if (m_type == SymbolType::REAL) {
        return (string)(category_str + "type : REAL, name : " + m_name);
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

} // namespace ESI