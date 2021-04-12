#ifndef INC_EXCEPTION_HPP_
#define INC_EXCEPTION_HPP_

#include <iostream>

namespace ESI {

// Base class for exceptions used by this project.
class Exception {
protected :
    // error message.
    std::string m_msg;

public :
    Exception(const std::string & str);
    virtual ~Exception();

    virtual const std::string what() const;
};

} // namespace ESI

#endif
