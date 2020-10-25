/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 16:37:36
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-10-25 15:18:38
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
            interpreter.interpret();

        } catch (std::runtime_error &error) {
            // break;
            std::cout << error.what() << std::endl;
            continue;
        }
    }



    return 0;
}