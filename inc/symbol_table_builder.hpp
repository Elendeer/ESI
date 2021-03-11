/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 20:27:27
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-08 20:33:37
 * @Description  :
*********************************************/

#include "node_visitor.hpp"
#include "symbol_table.hpp"

namespace ESI {

class SymbolTableBuilder : public NodeVisitor {
private :
    SymbolTable m_table;
    virtual void generic_visit(AST *node);

public :
    SymbolTableBuilder();
    ~SymbolTableBuilder();
};

} // namespace ESI