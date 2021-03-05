/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 16:37:36
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-05 12:25:45
* @Description  : main function
*********************************************/

#include <iostream>
#include <cstring>

#include "../inc/interpreter.hpp"
#include "../inc/file_reader.hpp"


int main(int num_command_arguments, char * pointer_array_command[]) {
    using namespace std;
    using namespace ESI;
    // cout << "starting ... " << endl;

    if (num_command_arguments != 2) {
        cout << "Invailid command line arguments" << endl;
    }
    else {
        string file_path = pointer_array_command[1];

        FileReader file_reader;
        string text = file_reader.readFile(file_path);

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
        }
    }


    return 0;
}