/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-07 11:16:08
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-08 15:02:29
 * @Description  :
*********************************************/
#include <string>

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
    VAR_SYMBOL
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

} // namespace ESI