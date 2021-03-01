/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 16:37:36
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-01 20:55:14
* @Description  : main function
*********************************************/

#include "../inc/interpreter.hpp"

#include <iostream>
#include <cstring>


int main() {
    using namespace std;
    using namespace ESI;
    cout << "starting ... " << endl;


    while (true) {
        string text;

        cout << "esi> ";
        getline(std::cin, text);

        if (text.length() == 0) {
            continue;
        }
        if (text == "exit") {
            break;
        }

        Lexer lexer(text);

        try {
            Parser parser(lexer);
            // cout << "parsed" << endl;

            Interpreter interpreter(parser);

            // There are try-catch blocks inside interpret()
            // to solve problems itself.
            interpreter.interpret();

        } catch (std::runtime_error &error) {
            cout << "when parser initing :" << endl;
            cout  << "\t" << error.what() << endl;
            continue;
        }
    }



    return 0;
}