/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 11:49:40
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-08 15:40:18
 * @Description  :
*********************************************/
#include <iostream>

#include "../inc/symbol_table.hpp"

using namespace std;
using namespace ESI;

int main() {
    SymbolTable test;
    test.print();
    cout << endl;

    test.define(new VarSymbol("a", SymbolType::INTEGER));
    test.print();
    cout << endl;

    cout << test.lookup("a")->strRepr() << endl;
    cout << test.lookup("REAL")->strRepr() << endl;


    return 0;
}