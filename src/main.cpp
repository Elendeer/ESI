/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 16:37:36
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-11-20 11:24:32
* @Description  : main function
*********************************************/

#include "../inc/interpreter.hpp"

#include <iostream>
#include <cstring>

int main(int args, char * argv[]) {

    using namespace ESI;
    using namespace std;

    switch (args) {
        case 1:
            break;
        case 2:
            if (strcmp(argv[1], "-t\n")) {
                // TODO: Open testing_mode.
            }
            else {
                cout << "wrong variables" << endl;
                return 0;
            }
            break;

        default:
            exit(1);
            break;
    }


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