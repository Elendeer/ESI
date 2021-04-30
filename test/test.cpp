/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-20 21:47:51
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-20 22:15:34
 * @Description  :
*********************************************/

#include <iostream>

#include "../inc/call_stack.hpp"

using namespace std;
using namespace ESI;

int main() {
    Any a = false;

    cout << to_string(Any::anyCast<bool>(a)) << endl;

    return 0;
}
