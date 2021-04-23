#ifndef INC_CALL_STACK_HPP_
#define INC_CALL_STACK_HPP_

#include "any.hpp"

#include <string>
#include <unordered_map>

namespace ESI {

// Type of activation record.
enum class ARType {
    PROGRAM
};

// An activation record is a dictionary-like object
// for maintaining information about the currently executing invocation
// of a procedure or function, and also the program itself.
// AKA stack frames.
class ActivationRecord {
private:
    std::string m_name;
    ARType m_type;
    int m_nesting_level;
    std::unordered_map<std::string, Any> m_members_map;

public:
    ActivationRecord(
            std::string name,
            ARType type,
            int nesting_level);

    ~ActivationRecord();

};

} // namespace ESI

#endif
