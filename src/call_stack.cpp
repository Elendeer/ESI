#include "../inc/call_stack.hpp"


#include <iostream>

using std::string;
// using std::unordered_map;

using std::cout;
using std::endl;

namespace ESI {

ActivationRecord::ActivationRecord(
    string name, ARType type, int nesting_level):
    m_name(name), m_type(type), m_nesting_level(nesting_level) {}

ActivationRecord::~ActivationRecord() {}

void ActivationRecord::print() const {
    string AR_type_str;
    if (m_type == ARType::PROGRAM) {
        AR_type_str = "PROGRAM";
    }
    else if (m_type == ARType::PROCEDURE) {
        AR_type_str = "PROCECURE";
    }
    else {
        AR_type_str = "NOT FOUND";
    }

    cout << m_nesting_level << ": "<< AR_type_str << " " << m_name << endl;

    for (auto p : m_members_map) {
        cout << " " << p.first << "\t: " << p.second << endl;
    }
}

Any ActivationRecord::at(string key) const {
    return m_members_map.at(key);
}

// ===== over load =====

Any & ActivationRecord::operator[] (string key) {
    return m_members_map[key];
}

// ===== =====
// ===== ===== CallStack class
// ===== =====

CallStack::CallStack() {
    m_records.clear();
}
CallStack::~CallStack() {}

void CallStack::push(ActivationRecord record) {
    m_records.push_back(record);
}

void CallStack::pop() {
    m_records.pop_back();
}

ActivationRecord & CallStack::peek() {
    return m_records.back();
}

void CallStack::print() const {
    cout << "CALL STACK" << endl;
    for (auto i = m_records.rbegin(); i != m_records.rend(); ++ i ) {
        i->print();
    }
    cout << endl;
}

} // namespace ESI


