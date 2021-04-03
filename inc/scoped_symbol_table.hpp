/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 10:12:51
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-04-03 10:17:52
 * @Description  :
 * Symbol table is a map from string(name of the symble)
 * to Symbol. The reason that these is a need to build a
 * SymbolTable class is that Symbol class have some derived
 * classes, the map need to contain pointers to support the
 * containment of different derived classes.
*********************************************/
#ifndef INC_SYMBOL_TABLE_HPP_
#define INC_SYMBOL_TABLE_HPP_

#include <unordered_map>

#include "symbol.hpp"

namespace ESI {

// A symbol table is an abstract data type (ADT)
// for tracking various symbols in source code.
class ScopedSymbolTable {
private:
    std::string m_scope_name;
    int m_scope_level;
    ScopedSymbolTable *m_p_enclosing_scope;

    std::unordered_map<std::string, Symbol *> m_map;

public:
    ScopedSymbolTable(std::string scope_name = "none",
                      int scope_level = -1,
                      ScopedSymbolTable *enclosing_scope = nullptr);
    ~ScopedSymbolTable();
    ScopedSymbolTable(const ScopedSymbolTable &obj);

    std::string getScopeName() const;
    int getScopeLevel() const;

    // Return a pointer pointing the enclosing scope of
    // this scope.
    ScopedSymbolTable * getEnclosingScope() const;

    // Print the string representation to std::ostream.
    // formated like:
    // key : <key> ; symbol : <symbol str representation>
    void print() const;

    // Define a symbol in symbol table.
    void define(Symbol *symbol);

    // Cheack if the name's corresponding symbol exist in symbol table.
    // It will recursively go up to check the scope tree by using
    // m_p_enclosing_scope pointer by default(current_scope_only = false).
    // Return nullptr if corresponding symbol no found.
    Symbol *lookup(std::string name, bool current_scope_only = false) const;
};

} // namespace ESI

#endif
