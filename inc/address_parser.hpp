/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-12-30 15:50:09
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-04 17:34:16
 * @Description  :
*********************************************/

#ifndef __ADDRESS_PARSER_HPP__
#define __ADDRESS_PARSER_HPP__

#include <iostream>
#include <string>
#include <vector>

namespace ESI {

class AddressParser {
	using string = std::string;

private:
	string m_current_working_directory;

	bool isAbsPath(string path);

public:
	AddressParser();
	~AddressParser();

	// Get current working directory.
	string getCwd() const;

	// Parse a relative path to a absolute path.
	string parseRelativePath(string path);

};

} // namespace ESI

#endif
