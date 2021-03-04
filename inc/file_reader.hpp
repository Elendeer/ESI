/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-12-30 15:50:09
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-04 16:53:58
 * @Description  :
*********************************************/

#ifndef __FILE_READER_HPP__
#define __FILE_READER_HPP__

#include <fstream>
#include <iostream>

#include "address_parser.hpp"

namespace ESI {


class FileReader {
private :
    AddressParser m_address_parser;

public :
    FileReader();
    ~FileReader();

    // Return a string containing contents of input file.
    // path sould point to file.
	// Throw a exception if opening error is met.
    std::string readFile(std::string path);
};

} // namespace ESI

#endif
