/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-12-30 15:50:09
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-04 16:58:09
 * @Description  :
*********************************************/
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(NT)

// Using different address breaking character in different platform.
#define ADDRESS_BREAK '\\'


#elif __linux__

// Using different address breaking character in different platform.
#define ADDRESS_BREAK '/'


#endif

#include "../inc/file_reader.hpp"
#include <iostream>


using std::string;

namespace ESI {

FileReader::FileReader() {}
FileReader::~FileReader() {}

string FileReader::readFile(string path) {
    std::ifstream reader;
	string txt;

	string abs_path = m_address_parser.parseRelativePath(path);

	reader.open(abs_path, std::ios::in);

    if (!reader.good()) {

		throw (string)"opening error";
    }

	while (!reader.eof()) {
		// For reading bug in linux file.
		if (reader.peek() != (char)-1) {
			txt += reader.get();
		}
		else {
			reader.ignore();
		}
	}
	reader.close();

    return txt;
}

} // namespace ESI
