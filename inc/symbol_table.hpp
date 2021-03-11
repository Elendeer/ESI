/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 10:12:51
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-08 15:16:26
 * @Description  :
*********************************************/
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