/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-07 11:16:08
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-12 17:09:45
 * @Description  :
*********************************************/
#ifndef INC_SYMBOL_HPP_
#define INC_SYMBOL_HPP_

#include <string>
#include <vector>

#include "AST.hpp"

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
    virtual ~VarSymbol();

    virtual SymbolCategory getCategory() const;
};

// Procedure symbol.
// If there are no parameters for a procedure node, please enter a 
// empty vector as 'parameters'.
class ProcedureSymbol : public Symbol {
private:
    std::vector<AST *> m_parameters;

public :
	ProcedureSymbol(std::string name, std::vector<AST *> & parameters);
	virtual ~ProcedureSymbol();

    virtual SymbolCategory getCategory() const;
};

} // namespace ESI

#endif
