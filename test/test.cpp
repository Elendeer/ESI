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
    ActivationRecord ar1("program1", ARType::PROGRAM, 1);
    // ar1.print();

    ar1["y"] = 1;

    CallStack call_stack;
    call_stack.push(ar1);

    call_stack.print();

    return 0;
}
