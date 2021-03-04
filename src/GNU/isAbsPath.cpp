/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-12-30 20:51:19
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-04 17:37:21
 * @Description  :
*********************************************/

#ifdef __linux__

#include "../../inc/address_parser.hpp"

namespace ESI {

bool AddressParser::isAbsPath(string path) {
    if (path.at(0) == '/') {
            return true;
    }
    return false;
}

} // namespace ESI

#endif
