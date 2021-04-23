#include "../inc/call_stack.hpp"

using std::string;
using std::unordered_map;

using std::cout;
using std::endl;

namespace ESI {

ActivationRecord::ActivationRecord(
    string name, ARType type, int nesting_level):
    m_name(name), m_type(type), m_nesting_level(nesting_level) {}

void ActivationRecord::setItem(string key, Any value) {
    m_members_map[key] = value;
}

Any ActivationRecord::getItem(string key) const {
    return m_members_map.at(key);
}

void ActivationRecord::print() const {
    string AR_type_str;
    if (m_type == ARType::PROGRAM) {
        AR_type_str == "program";
    }
    else {
        AR_type_str == "not found";
    }

    cout << m_nesting_level << ": "<< AR_type_str << " " << m_name << endl;

    for (auto p : m_members_map) {
        cout << p.first << ": " << p.second << endl;
    }
}

// ===== =====
// ===== ===== CallStack class
// ===== =====

CallStack::CallStack() {}
CallStack::~CallStack() {}

void CallStack::push(ActivationRecord record) {
    m_records.push_back(record);
}

void CallStack::pop() {
    m_records.pop_back();
}

ActivationRecord CallStack::peek() const {
    return m_records.back();
}

void CallStack::print() const {
    cout << endl;

    for (auto i = m_records.end(); i >= m_records.begin(); -- i ) {
        i->print();
    }
}

} // namespace ESI


