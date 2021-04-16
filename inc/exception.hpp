#ifndef INC_EXCEPTION_HPP_
#define INC_EXCEPTION_HPP_

#include "token.hpp"

#include <iostream>

namespace ESI {

enum class ErrorCode {
    NONE,

    UNEXPECTED_TOKEN,
    ID_NOT_FOUND,
    DUPLICATE_ID
};

// Base class for exceptions used by this project.
class Exception {
protected :
    // error message.
    std::string m_msg;

    Token m_token;

    ErrorCode m_error_code;


public :
    Exception(
        const std::string & message,
        ErrorCode error_code = ErrorCode::NONE,
        Token token = Token());

    virtual ~Exception();

    virtual const std::string what() const;
};

} // namespace ESI

#endif
