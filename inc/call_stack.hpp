#ifndef INC_CALL_STACK_HPP_
#define INC_CALL_STACK_HPP_

#include "any.hpp"

#include <string>
#include <unordered_map>

namespace ESI {

// Type of activation record.
enum class ARType {
    PROGRAM,
    PROCEDURE,
    FUNCTION
};

// An activation record is a dictionary-like object
// for maintaining information about the currently executing invocation
// of a procedure or function, and also the program itself.
// AKA stack frames.
// Just like symbol table for interpreter.
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

    ActivationRecord(const ActivationRecord & obj) = default;

    ~ActivationRecord();

    void print() const;

    // Return an empty Any value if no found.
    Any at(std::string key) const;

    // Return m_members_map[key].
    Any & operator[] (std::string key);
};


// ===== =====

// A stack datastructure that
// used to track what procedure/function call is being currently executed.
class CallStack {
private:
    std::vector<ActivationRecord> m_records;

public:
    CallStack();
    ~CallStack();

    void push(ActivationRecord record);
    void pop();

    // Return the reference activation record in the top of the stack.
    ActivationRecord & peek();

    void print() const;
};

} // namespace ESI

#endif
