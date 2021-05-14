/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-02-25 11:51:26
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-05-14 21:44:07
 * @Description  :
*********************************************/

#ifndef ESI_INC_ANY_HPP_
#define ESI_INC_ANY_HPP_

#include <cmath>
#include <iostream>
#include <map>
#include <regex>
#include <string>

namespace ESI {

// ===== Class TypeInfo =====

// Their order affects type casting.
enum class DataType {
    Empty,
    Bool,
    Char,
    Integer,
    Float,
    String
};

class TypeInfo {
private:
    DataType m_type_id;
    std::string m_type_name;

    // TODO: To find out why unordered_map can not be used here.
    // Map from DataType to corresponding string.
    static const std::map<DataType, std::string> typeMap;

public:
    TypeInfo(DataType type = DataType::Empty);

    std::string getTypeName() const;
    DataType getTypeId() const;

    static bool checkOperand(DataType left, DataType right, std::string op);

    bool operator == (const TypeInfo type) const;
    bool operator >= (const TypeInfo type) const;
    bool operator <= (const TypeInfo type) const;
};

// ===== Class Any =====

// DataType == DataType::Empty by default.
// Please explicit use string cast if you want to store
// a string inside. Or it will recognize it as a bool value.
class Any {
private:
    bool m_bool_value;
    int m_int_value;
    double m_float_value;
    char m_char_value;
    std::string m_string_value;

    TypeInfo m_type_info;

public:
    Any();
    Any(bool var);
    Any(int var);
    Any(double var);
    Any(char var);
    Any(std::string var);

    ~Any();

    DataType getType() const;
    bool empty() const;

    template<typename T>
    T anyCast();
    template<typename T>
    static T anyCast(Any var);

    Any operator = (const bool var);
    Any operator = (const int var);
    Any operator = (const double var);
    Any operator = (const char var);
    Any operator = (const std::string var);

    Any operator + (Any var);
    Any operator - (Any var);
    Any operator * (Any var);
    Any operator / (Any var);

    bool operator == (const bool var) const ;
    bool operator == (const int var) const ;
    bool operator == (const double var) const ;
    bool operator == (const char var) const ;
    bool operator == (const std::string var) const ;

    bool operator > (Any var) const ;
    bool operator < (Any var) const ;
    bool operator >= (Any var) const ;
    bool operator <= (Any var) const ;

    bool operator == (Any var) const ;
    bool operator != (Any var) const ;

    operator bool();
    operator std::string();

    friend std::ostream & operator << (std::ostream & output, Any & d);
    friend std::istream & operator >> (std::istream & output, Any & d);

    friend bool checkOperand(DataType left, DataType right, std::string op);
};

// for number matching
static const std::regex numPattern (
    "^(\\+|-)?(0|[1-9][0-9]*)(\\.[1-9]+)?((e|E)(\\+|-)?(0|[1-9][0-9]*))?$"
);

static TypeInfo typeEmpty = TypeInfo(DataType::Empty);
static TypeInfo typeBool = TypeInfo(DataType::Bool);
static TypeInfo typeInt = TypeInfo(DataType::Integer);
static TypeInfo typeFloat = TypeInfo(DataType::Float);
static TypeInfo typeChar = TypeInfo(DataType::Char);
static TypeInfo typeString = TypeInfo(DataType::String);

// I don't really understand what this one for.
template<typename T>
T (*cast)();

template<typename T>
T Any::anyCast() {
    void * ret = &m_char_value;
    if (typeid(T) == typeid(bool) && m_type_info <= typeBool) {
        ret = & m_bool_value;
    }
    else if (typeid(T) == typeid(char) && m_type_info <= typeChar) {
        ret = & m_char_value;
    }
    else if (typeid(T) == typeid(int) && m_type_info <= typeInt) {
        ret = & m_int_value;
    }
    else if (typeid(T) == typeid(double) && m_type_info <= typeFloat) {
        ret = & m_float_value;
    }
    else if (typeid(T) == typeid(std::string)) {
        ret = & m_string_value;
    }

    T Tval = *((T *)ret);
    return Tval;
}

template<typename T>
T Any::anyCast(Any var) {
    return var.anyCast<T>();
}

} // namespace ESI

#endif

