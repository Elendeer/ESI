#include "../inc/exception.hpp"

using std::string;

namespace ESI {

Exception::Exception(
    const std::string & message,
    ErrorCode error_code,
    Token token) :

    m_token(token),
    m_error_code(error_code) {
        if (error_code == ErrorCode::NONE) {
            m_msg = "ErrorCode: None; \t" + message;
        }
        else if (error_code == ErrorCode::UNEXPECTED_TOKEN) {
            m_msg = "ErrorCode: Unexpected token; \t" + message;
        }
        else if (error_code == ErrorCode::ID_NOT_FOUND) {
            m_msg = "ErrorCode: ID not found; \t" + message;
        }
        else if (error_code == ErrorCode::DUPLICATE_ID) {
            m_msg = "ErrorCode: Duplicat ID; \t" + message;
        }
    }

Exception::~Exception() {}

const string Exception::what() const {
    return m_msg;
}

} // namespace ESI

