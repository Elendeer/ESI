#include "../inc/exception.hpp"

using std::string;

namespace ESI {

Exception::Exception(const string & str) :
    m_msg(str) {}

Exception::~Exception() {}

const string Exception::what() const {
    return m_msg;
}

} // namespace ESI

