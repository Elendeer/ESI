/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 16:37:36
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-11 14:37:34
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

            // There are try-catch blocks inside parse()
            // to solve problems itself.
            AST * ast_root = parser.parse();

            if (ast_root == nullptr) {
                cout << "Parsing error is met, stop." << endl;
                return 1;
            }

            Interpreter interpreter(ast_root);

            // There are try-catch blocks inside interpret()
            // to solve problems itself.
            interpreter.interpret();

            if (ast_root != nullptr) delete ast_root;
        }
        catch (std::runtime_error &error) {
            cout << "when parser initing :" << endl;
            cout  << "\t" << error.what() << endl;

            return 1;
        }
    }


    return 0;
}