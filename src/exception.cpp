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
            m_msg = message + "\tErrorCode: None; ";
        }
        else if (error_code == ErrorCode::UNEXPECTED_TOKEN) {
            m_msg = message + "\tErrorCode: Unexpected token; ";
        }
        else if (error_code == ErrorCode::ID_NOT_FOUND) {
            m_msg = message + "\tErrorCode: ID not found; ";
        }
        else if (error_code == ErrorCode::DUPLICATE_ID) {
            m_msg = message + "\tErrorCode: Duplicat ID; ";
        }
        else if (error_code == ErrorCode::WRONG_PARAMS_NUM) {
            m_msg = message + "\tErrorCode: Wrong parameter number; ";
        }
        else if (error_code == ErrorCode::UNKNOW_TYPE) {
            m_msg = message + "\tErrorCode: Unknow type; ";
        }
        else {
            m_msg = message + "\tError code not found;";
        }

        m_msg = m_msg + "When scanning token: " + token.getStringRepr();
    }

Exception::~Exception() {}

const string Exception::what() const {
    return m_msg;
}

} // namespace ESI

