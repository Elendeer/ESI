/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-07 11:16:08
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-04-27 19:44:16
 * @Description  :
*********************************************/
#ifndef INC_SYMBOL_HPP_
#define INC_SYMBOL_HPP_

#include <string>
#include <vector>

namespace ESI {

// Type of a symbol will be used in type checking.
enum class SymbolType {
    NONE,
    INTEGER,
    REAL
};

// Used in category judging.
enum class SymbolCategory {
    SYMBOL,
    BUILD_IN_TYPE_SYMBOL,
    VAR_SYMBOL,

	PROCEDURE_SYMBOL
};

// As a base class.
// name : name of the symbol;
// type : if this symbol is a variable, it will have a type.
class Symbol {
protected :
    std::string m_name;
    SymbolType m_type;

public:
    Symbol(std::string name, SymbolType type = SymbolType::NONE);
    virtual ~Symbol();

    std::string getName() const;
    SymbolType getType() const;
    virtual SymbolCategory getCategory() const;

    std::string strRepr();
};

// Build-in types means those types you can use derectly.
// e.g. INTEGER, REAL, etc.
class BuildInTypeSymbol : public Symbol {

public :
    BuildInTypeSymbol(std::string name);
    virtual ~BuildInTypeSymbol();

    virtual SymbolCategory getCategory() const;
};

// Variable symbol.
class VarSymbol : public Symbol {

public :
    VarSymbol(std::string name, SymbolType type);
    VarSymbol(const VarSymbol & obj) = default ;
    virtual ~VarSymbol();

    virtual SymbolCategory getCategory() const;
};

// Procedure symbol.
class ProcedureSymbol : public Symbol {
private:
    std::vector<VarSymbol *> m_parameters;

    // Store a 'Block *' pointer pointing to the
    // block AST node of the procedure.
    // Here 'void *' is used for aviod the mutual inclusion
    // of the header files.
    void * m_p_procedure_block;

public :
    ProcedureSymbol(std::string name, void * p_procedure_symbol = nullptr);

    ProcedureSymbol(const ProcedureSymbol & obj);
	virtual ~ProcedureSymbol();

    virtual SymbolCategory getCategory() const;

    void pushParameter(VarSymbol * param_node);

    void * getProcedureBlock() const;
    std::vector<VarSymbol *> getParams();

    ProcedureSymbol & operator= (const ProcedureSymbol obj);
};

} // namespace ESI

#endif
