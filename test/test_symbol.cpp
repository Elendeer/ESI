/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 08:47:26
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-08 10:05:05
 * @Description  :
*********************************************/

#include <iostream>

#include "../inc/symbol.hpp"

using namespace std;
using namespace ESI;

int main() {
    Symbol s((string)"test");
    s.printStrRepr();
    return 0;
}