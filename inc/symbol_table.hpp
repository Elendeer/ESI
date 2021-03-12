/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 10:12:51
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-12 17:09:28
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
class SymbolTable {
private :
    std::unordered_map<std::string, Symbol *> m_map;

public :
    SymbolTable();
    ~SymbolTable();
    SymbolTable(const SymbolTable & obj);


    // Print the string representation to std::ostream.
    // formated like:
    // key : <key> ; symbol : <symbol str representation>
    void print() const ;

    // Define a symbol in symbol table.
    void define(Symbol * symbol);

    // Cheack if the name's corresponding symbol exist in symbol table.
    // Return nullptr if it is not.
    Symbol * lookup(std::string name) const;

};

} // namespace ESI

#endif