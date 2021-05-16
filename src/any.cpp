/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-02-25 12:08:08
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-05-16 12:24:57
 * @Description  :
*********************************************/
#include "../inc/any.hpp"
#include <exception>

using std::map;
using std::string;

namespace ESI {

// ===== Class TypeInfo =====

const map<DataType, string> TypeInfo::typeMap {
        {DataType::Empty, "empty"},
        {DataType::Bool, "bool"},
        {DataType::Char, "char"},
        {DataType::Integer, "int"},
        {DataType::Float, "float"},
        {DataType::String, "string"},
};

// type = DataType::Empty by default.
TypeInfo::TypeInfo(DataType type) {
    m_type_id = type;

    if (typeMap.find(type) != typeMap.end()) {
        m_type_name = typeMap.at(type);
    }
}

string TypeInfo::getTypeName() const {
    return m_type_name;
}

DataType TypeInfo::getTypeId() const {
    return m_type_id;
}

bool TypeInfo::checkOperand(DataType left, DataType right, string op) {
    if (left == DataType::Empty || right == DataType::Empty) {
        string msg = "unsupported operand type(s) for " +
            op + ": '" + typeMap.at(left) + "' and '" +
            typeMap.at(right) + "'";

        throw std::runtime_error(msg);
    }
    return true;
}


// ===== Opreator Over loading of class TypeInfo =====

bool TypeInfo::operator == (const TypeInfo type) const {
    return m_type_id == type.getTypeId();
}

bool TypeInfo::operator <= (const TypeInfo type) const {
    return m_type_id <= type.getTypeId();
}

bool TypeInfo::operator >= (const TypeInfo type) const {
    return m_type_id >= type.getTypeId();
}

// ===== Class Any =====

// ===== Constructor & Destructor =====

Any::Any() : m_type_info(typeEmpty) {}

Any::Any(bool var)
    : m_bool_value(var), m_type_info(typeBool) {

    if (var) {
        m_char_value = m_float_value = m_int_value = 1;
    }
    else {
        m_char_value = m_float_value = m_int_value = 0;
    }
}
Any::Any(char var)
    : m_char_value(var), m_type_info(typeChar) {

    m_float_value = m_int_value = var;
    m_bool_value = (bool)var;
}
Any::Any(int var)
    : m_int_value(var), m_type_info(typeInt) {

    m_float_value = var;
    m_bool_value = (bool)var;
}
Any::Any(double var)
    : m_float_value(var), m_type_info(typeFloat) {

    m_bool_value = (bool)var;
}
Any::Any(string var)
    : m_string_value(var), m_type_info(typeString) {}


Any::~Any() {}

// ===== Get functions =====

DataType Any::getType() const {
    return m_type_info.getTypeId();
}

// ===== =====

bool Any::empty() const {
    if (m_type_info.getTypeId() == DataType::Empty) return true;
    else return false;
}

// ===== Overloading =====

// ===== Assign =====

Any Any::operator = (bool var) {
    m_type_info = typeBool;
    m_bool_value = var;

    m_char_value = m_float_value = m_int_value = var;

    return var;
}

Any Any::operator = (char var) {
    m_type_info = typeChar;
    m_char_value = var;

    m_bool_value = (bool)var;
    m_int_value = m_float_value = var;

    return var;
}

Any Any::operator = (int var) {
    m_type_info = typeInt;
    m_int_value = var;

    m_bool_value = (bool)var;
    m_float_value = var;

    return var;
}

Any Any::operator = (double var) {
    m_type_info = typeFloat;
    m_float_value = var;

    m_bool_value = (bool)var;

    return var;
}

Any Any::operator = (string var) {
    m_type_info = typeString;
    m_string_value = var;

    return var;
}

// ===== Operating =====

Any Any::operator + (Any var) {
    TypeInfo::checkOperand(this->getType(), var.getType(), "+");

    if (m_type_info == typeString) {
        return Any(m_string_value + (string)var);
    }
    if (var.m_type_info == typeString) {
        return Any((string)(*this) + var.m_string_value);
    }

    if (this->getType() >= var.getType()) {
        if (m_type_info == typeBool) {
            return Any(this->anyCast<bool>() + var.anyCast<bool>());
        }
        else if (m_type_info == typeChar) {
            return Any(this->anyCast<char>() + var.anyCast<char>());
        }
        else if (m_type_info == typeInt) {
            return Any(this->anyCast<int>() + var.anyCast<int>());
        }
        else if (m_type_info == typeFloat) {
            return Any(this->anyCast<double>() + var.anyCast<double>());
        }
    }
    else {
        if (var.m_type_info == typeBool) {
            return Any(this->anyCast<bool>() + var.anyCast<bool>());
        }
        else if (var.m_type_info == typeChar) {
            return Any(this->anyCast<char>() + var.anyCast<char>());
        }
        else if (var.m_type_info == typeInt) {
            return Any(this->anyCast<int>() + var.anyCast<int>());
        }
        else if (var.m_type_info == typeFloat) {
            return Any(this->anyCast<double>() + var.anyCast<double>());
        }
    }

    return Any();
}

Any Any::operator - (Any var) {
    TypeInfo::checkOperand(this->getType(), var.getType(), "-");

    if (this->getType() >= var.getType()) {
        if (m_type_info == typeBool) {
            return Any(this->anyCast<bool>() - var.anyCast<bool>());
        }
        else if (m_type_info == typeChar) {
            return Any(this->anyCast<char>() - var.anyCast<char>());
        }
        else if (m_type_info == typeInt) {
            return Any(this->anyCast<int>() - var.anyCast<int>());
        }
        else if (m_type_info == typeFloat) {
            return Any(this->anyCast<double>() - var.anyCast<double>());
        }
    }
    else {
        if (var.m_type_info == typeBool) {
            return Any(this->anyCast<bool>() - var.anyCast<bool>());
        }
        else if (var.m_type_info == typeChar) {
            return Any(this->anyCast<char>() - var.anyCast<char>());
        }
        else if (var.m_type_info == typeInt) {
            return Any(this->anyCast<int>() - var.anyCast<int>());
        }
        else if (var.m_type_info == typeFloat) {
            return Any(this->anyCast<double>() - var.anyCast<double>());
        }
    }

    return Any();
}

Any Any::operator * (Any var) {
    TypeInfo::checkOperand(this->getType(), var.getType(), "*");

    if (this->getType() >= var.getType()) {
        if (m_type_info == typeBool) {
            return Any(this->anyCast<bool>() * var.anyCast<bool>());
        }
        else if (m_type_info == typeChar) {
            return Any(this->anyCast<char>() * var.anyCast<char>());
        }
        else if (m_type_info == typeInt) {
            return Any(this->anyCast<int>() * var.anyCast<int>());
        }
        else if (m_type_info == typeFloat) {
            return Any(this->anyCast<double>() * var.anyCast<double>());
        }
    }
    else {
        if (var.m_type_info == typeBool) {
            return Any(this->anyCast<bool>() * var.anyCast<bool>());
        }
        else if (var.m_type_info == typeChar) {
            return Any(this->anyCast<char>() * var.anyCast<char>());
        }
        else if (var.m_type_info == typeInt) {
            return Any(this->anyCast<int>() * var.anyCast<int>());
        }
        else if (var.m_type_info == typeFloat) {
            return Any(this->anyCast<double>() * var.anyCast<double>());
        }
    }

    return Any();
}

Any Any::operator / (Any var) {
    TypeInfo::checkOperand(this->getType(), var.getType(), "/");

    if (this->getType() >= var.getType()) {
        if (m_type_info == typeBool) {
            return Any(this->anyCast<bool>() / var.anyCast<bool>());
        }
        else if (m_type_info == typeChar) {
            return Any(this->anyCast<char>() / var.anyCast<char>());
        }
        else if (m_type_info == typeInt) {
            return Any(this->anyCast<int>() / var.anyCast<int>());
        }
        else if (m_type_info == typeFloat) {
            return Any(this->anyCast<double>() / var.anyCast<double>());
        }
    }
    else {
        if (var.m_type_info == typeBool) {
            return Any(this->anyCast<bool>() / var.anyCast<bool>());
        }
        else if (var.m_type_info == typeChar) {
            return Any(this->anyCast<char>() / var.anyCast<char>());
        }
        else if (var.m_type_info == typeInt) {
            return Any(this->anyCast<int>() / var.anyCast<int>());
        }
        else if (var.m_type_info == typeFloat) {
            return Any(this->anyCast<double>() / var.anyCast<double>());
        }
    }

    return Any();
}

// ===== =====

bool Any::operator == (bool var) const {
    return m_bool_value == var;
}
bool Any::operator == (char var) const {
    return m_char_value == var;
}
bool Any::operator == (int var) const {
    return m_int_value == var;
}
bool Any::operator == (double var) const {
    return m_float_value == var;
}
bool Any::operator == (string var) const {
    return m_string_value == var;
}

bool Any::operator > (Any var) const {
    return m_float_value > var.m_float_value;
}
bool Any::operator < (Any var) const {
    return m_float_value < var.m_float_value;
}
bool Any::operator >= (Any var) const {
    return m_float_value >= var.m_float_value;
}
bool Any::operator <= (Any var) const {
    return m_float_value <= var.m_float_value;
}

bool Any::operator == (Any var) const {
    if (m_type_info == var.m_type_info) {
        DataType type = m_type_info.getTypeId();
        if (type == DataType::Empty) {
            return true;
        }
        else if (type == DataType::Bool) {
            return m_bool_value == var.m_bool_value;
        }
        else if (type == DataType::Char) {
            return m_char_value == var.m_char_value;
        }
        else if (type == DataType::Integer) {
            return m_int_value == var.m_int_value;
        }
        else if (type == DataType::Float) {
            return m_float_value == var.m_float_value;
        }
        else if (type == DataType::String) {
            return m_string_value == var.m_string_value;
        }

    }

    return false;
}

bool Any::operator != (Any var) const {
    return !operator ==(var);
}

bool Any::operator && (Any var) const {
    return m_bool_value && var.m_bool_value;
}

bool Any::operator || (Any var) const {
    return m_bool_value || var.m_bool_value;
}

bool Any::operator ! () const {
    return !m_bool_value;
}

// ===== =====

Any::operator bool() {
    return m_bool_value;
}

Any::operator string() {
    using std::to_string;

    if (m_type_info == typeBool) {
        return string(m_bool_value ? "true" : "false");
    }
    else if (m_type_info == typeChar) {
        return to_string(m_char_value);
    }
    else if (m_type_info == typeInt) {
        return to_string(m_int_value);
    }
    else if (m_type_info == typeFloat) {
        return to_string(m_float_value);
    }
    else if (m_type_info == typeString) {
        return m_string_value;
    }
    else {
        return string();
    }
}

// ===== Overloading of << & >> =====

std::ostream & operator << (std::ostream & output, Any & d) {
    if (d.m_type_info == typeEmpty) {
        output << "None";
    }
    else if (d.m_type_info == typeBool) {
        output << (d.m_bool_value ? "true" : "false");
    }
    else if (d.m_type_info == typeChar) {
        output << d.anyCast<char>();
    }
    else if (d.m_type_info == typeInt) {
        output << d.anyCast<int>();
    }
    else if (d.m_type_info == typeFloat) {
        output << d.anyCast<double>();
    }
    else if (d.m_type_info == typeString) {
        output << d.m_string_value;
    }

    return output;
}

std::istream & operator >> (std::istream & input, Any & d) {
    string str;
    input >> str;
    int len = str.length();
    if (std::regex_match(str, numPattern)) {
        int index = 0;
        double num = 0, scale = 0;
        int subscale = 0, signsubscale = 1;

        if (str[index] == '0') ++ index; // zero

        if (index < len && str[index] >= '1' && str[index] <= '9') {
            do {
                num = num * 10.0 + (str[index] - '0');
                ++ index;
            } while (index < len
                && str[index] >= '0' && str[index] <= '9');
        }

        if (index < len && str[index] == '.'
            && str[index + 1] >= '0' && str[index + 1] <= '9') {

            ++ index;
            do {
                num = num * 10.0 + (str[index] - '0');
                -- scale;
                ++ index;
            } while (index < len &&
                str[index] >= '0' && str[index] <= '9');
        } // fractional handling

        if ((index < len) && (str[index] == 'e' || str[index] == 'E')) {
            ++ index;
            if (str[index] == '+') {
                ++ index;
            }
            else if (str[index] == '-') {
                signsubscale = -1;
                ++ index;
            }

            while (index < len && str[index] >= '0' && str[index] <= '9') {
                subscale = subscale * 10 + (str[index] - '0');
                ++ index;
            }
        } // exponent handling

        num = num * pow(10.0, (scale + subscale * signsubscale));
        if (scale == 0 && signsubscale == 1) {
            d = (int) num;
        }
        else {
            d = num;
        }
    }
    else {
        // TODO: string input
    }

    return input;
}

} // namespace ESI
