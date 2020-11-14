/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 16:37:36
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-11-14 11:38:33
* @Description  : main function
*********************************************/

#include "../inc/interpreter.hpp"

#include <iostream>

int main() {
    using namespace ESI;

    while (true) {
        string text;

        std::cout << "esi> ";
        std::getline(std::cin, text);

        if (text.length() == 0) {
            continue;
        }
        if (text == "exit") {
            break;
        }

        Lexer lexer(text);

        try {
            Parser parser(lexer);

            Interpreter interpreter(parser);

            // There are try-catch blocks inside interpret()
            // to solve problems itself.
            interpreter.interpret();

        } catch (std::runtime_error &error) {
            std::cout << "when parser initing :" << std::endl;
            std::cout  << "\t" << error.what() << std::endl;
            continue;
        }
    }



    return 0;
}