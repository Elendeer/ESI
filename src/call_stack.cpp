#include "../inc/call_stack.hpp"

using std::string;
using std::unordered_map;

namespace ESI {

ActivationRecord::ActivationRecord(
    string name, ARType type, int nesting_level):
    m_name(name), m_type(type), m_nesting_level(nesting_level) {
    }

} // namespace ESI


