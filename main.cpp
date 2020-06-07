/*
 * @Author: Elendeer
 * @Date: 2020-06-05 16:37:36
 * @LastEditors: Elendeer
 * @LastEditTime: 2020-06-06 18:02:24
 * @Description: main function
 */

#include"inc/interpreter.hpp"

#include<iostream>


int main() {
    using namespace ESI;

    while (true) {
        string text;

        std::cout << "espi> " ;
        std::getline(std::cin, text);

        if (text.length() == 0) {
            continue;
        }
        if (text == "exit") {
            break;
        }

        Lexer lexer(text);
        int result;

        try {
            Parser parser(lexer);
            Interpreter interpreter(parser);
            result = interpreter.interpret();
        }
        catch (std::runtime_error& error) {
            // break;
            std::cout << error.what() << std::endl;
            continue;
        }

        std::cout << result << std::endl;
    }

    return 0;
}