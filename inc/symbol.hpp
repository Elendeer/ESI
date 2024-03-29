/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-07 11:16:08
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2023-04-14 21:49:14
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
    REAL,

    STRING,
    BOOLEAN,
};

// Used in category judging.
enum class SymbolCategory {
    SYMBOL,
    BUILD_IN_TYPE_SYMBOL,
    VAR_SYMBOL,

	PROCEDURE_SYMBOL,
	FUNCTION_SYMBOL,

    ARRAY_SYMBOL
};

// As a base class.
// name : name of the symbol;
// level : nested level of the symbol;
// type : if this symbol is a variable or a function,
//        it will have a type.
class Symbol {
protected :
    std::string m_name;
    int m_level;
    SymbolType m_type;

public:
    Symbol(std::string name,
            int level = 0, SymbolType type = SymbolType::NONE);
    Symbol(const Symbol & obj) = default;
    virtual ~Symbol();

    std::string getName() const;
    int getLevel() const;
    SymbolType getType() const;
    virtual SymbolCategory getCategory() const;

    std::string strRepr();
};

// Build-in types means those types you can use derectly.
// e.g. INTEGER, REAL, etc.
class BuildInTypeSymbol : public Symbol {

public :
    BuildInTypeSymbol(std::string name, int level);
    BuildInTypeSymbol(const BuildInTypeSymbol & obj) = default;
    virtual ~BuildInTypeSymbol();

    virtual SymbolCategory getCategory() const;
};

// Variable symbol.
class VarSymbol : public Symbol {

public :
    VarSymbol(std::string name, int level, SymbolType type);
    VarSymbol(const VarSymbol & obj) = default ;
    virtual ~VarSymbol();

    virtual SymbolCategory getCategory() const;
};

// Procedure symbol.
class ProcedureSymbol : public Symbol {
private:
    std::vector<VarSymbol> m_parameters;

    // Store a 'Block *' pointer pointing to the
    // block AST node of the procedure.
    // Here 'void *' is used for aviod the mutual inclusion
    // of the header files.
    void * m_p_procedure_block;

public :
    ProcedureSymbol(std::string name,
            int level, void * p_procedure_block = nullptr);

    ProcedureSymbol(const ProcedureSymbol & obj);
	virtual ~ProcedureSymbol();

    virtual SymbolCategory getCategory() const;

    void pushParameter(const VarSymbol & param_symbol);

    void * getProcedureBlock() const;
    std::vector<VarSymbol> getParams();

    const ProcedureSymbol & operator= (const ProcedureSymbol & obj);
};

// Function symbol
class FunctionSymbol : public Symbol {
private:
    std::vector<VarSymbol> m_parameters;

    // Store a 'Block *' pointer pointing to the
    // block AST node of the function.
    // Here 'void *' is used for aviod the mutual inclusion
    // of the header files.
    void * m_p_function_block;

public :
    FunctionSymbol(std::string name,
            int level,
            SymbolType type,
            void * p_procedure_block = nullptr);

    FunctionSymbol(const FunctionSymbol & obj);

    virtual ~FunctionSymbol();

    virtual SymbolCategory getCategory() const;

    void pushParameter(const VarSymbol & param_symbol);

    void * getFunctionBlock() const;
    std::vector<VarSymbol> getParams();

    const FunctionSymbol & operator= (const FunctionSymbol & obj);
};

class ArraySymbol : public Symbol {
private:
    int m_start_idx;
    int m_end_idx;

public:
    ArraySymbol(std::string name,
            int level,
            SymbolType type,
            int start_idx,
            int end_idx);
    ArraySymbol(const ArraySymbol & obj) = default;
    virtual ~ArraySymbol();

    virtual SymbolCategory getCategory() const;
    int getStartIdx() const;
    int getEndIdx() const;
};

} // namespace ESI

#endif
