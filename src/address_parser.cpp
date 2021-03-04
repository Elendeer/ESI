/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-12-30 15:50:09
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-04 17:36:45
 * @Description  :
*********************************************/

#include "../inc/address_parser.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(NT)

// Using different address breaking character in different platform.
#define ADDRESS_BREAK '\\'

// For getcwd(...)
#include <direct.h>

#include "win/isAbsPath.cpp"

#elif __linux__

// Using different address breaking character in different platform.
#define ADDRESS_BREAK '/'

// For readlink(...) & getcwd(...)
#include <unistd.h>

#include "GNU/isAbsPath.cpp"

#endif


using std::string;

namespace ESI {

AddressParser::AddressParser() {
	using namespace std;

	char cwd[256];
	if (getcwd(cwd, 256) == NULL) {
		throw (string)"getcwd error";
	}
	m_current_working_directory = cwd;
}

AddressParser::~AddressParser() {}

string AddressParser::getCwd() const {
	return m_current_working_directory;
}


string AddressParser::parseRelativePath(string path) {
	if (isAbsPath(path)) return path;

	// Count num of ../
	int up = 0;
	// Record the index of string for cutting.
	int idx = 0;

	for (int i = 0; i < (int)path.size(); ++ i ) {

		// Find the relative path prefix.
		if (i + 1 < (int)path.size()
			&& path[i] == '.') {

			// Found ./
			if (path[i + 1] == ADDRESS_BREAK) {
				idx = i + 1;

				// Skip next char
				++ i;
				continue;
			}
			// Found ../
			else if (i + 2 < (int)path.size()
					&& path[i + 1] == '.'
					&& path[i + 2] == ADDRESS_BREAK) {
				idx = i + 2;
				++ up;

				// Skip next two char
				i += 2;
				continue;
			}
			else {
				continue;
			}

		}
		else {
			break;
		}
	}

	string sub_rela_string = path.substr(idx);

	idx = m_current_working_directory.size();
	// Throw some suffixal path of current working directory away.
	for (int i = (int)m_current_working_directory.size() - 1; i >= 0 && up; -- i) {
		if (m_current_working_directory[i] == ADDRESS_BREAK) {
			idx = i + 1;
			-- up;
		}
	}

	// Abandon repetive ADDRESS_BREAK if exist.
	if (m_current_working_directory[idx - 1] == ADDRESS_BREAK) -- idx;

	string sub_cwd_string = m_current_working_directory.substr(0, idx);


	// std::cout << sub_cwd_string << std::endl;

	return sub_cwd_string + sub_rela_string;
}

} // namespace ESI
