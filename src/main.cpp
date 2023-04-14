/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-05 16:37:36
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2023-04-05 19:51:42
* @Description  : main function
*********************************************/

#include <iostream>
#include <cstring>

#include "../inc/interpreter.hpp"
#include "../inc/semantic_analyzer.hpp"
#include "../inc/file_reader.hpp"


int main(int num_command_arguments, char * pointer_array_command[]) {
    using namespace std;
    using namespace ESI;

    if (num_command_arguments < 2 || num_command_arguments > 4) {
        cout << "Invailid command line arguments. " << endl;
        cout << "Usage : ESI <file path> [--scope] [--stack] " << endl;
        return 1;
    }

    string file_path = pointer_array_command[1];

    FileReader file_reader;
    string text;
    try {
        text = file_reader.readFile(file_path);
    }
    catch (string & error) {
        cout << error << endl;
        return 1;
    }

    bool print_scope = false;
    bool print_stack = false;

    for (int i = 2; i < num_command_arguments; ++ i) {
        if (strcmp(pointer_array_command[i], "--scope") == 0) {
            print_scope = true;
        }
        else if (strcmp(pointer_array_command[i], "--stack") == 0) {
            print_stack = true;
        }
        else {
            cout << "Unknow command line argument: "
            + (string)pointer_array_command[i] << endl;
            cout << "Usage : ESI <file path> [--scope] [--stack] " << endl;
            return 1;
        }
    }

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

        SemanticAnalyzer semantic_analyzer(ast_root, print_scope);

        try {
            cout << "Semantic analyzing ..." << endl;
            semantic_analyzer.analyze();
			// semantic_analyzer.printBuildInTypeSymbolTable();
            cout << "Semantic analysis finished.\n" << endl;
        }
        catch (const SemanticError & error) {
            cout << "When building symbol table from AST :" << endl;
            cout << error.what() << endl;
            cout << "error met when semantic analyzing, stop." << endl;

            if (ast_root != nullptr) {
                delete ast_root;
                ast_root = nullptr;
            }

            return 1;
        }

        Interpreter interpreter(ast_root, print_stack);

        try {
            cout << "Interpreting ...\n" << endl;
            interpreter.interpret();
        }
        catch (const Exception & error) {
            cout << error.what() << endl;

            if (ast_root != nullptr) delete ast_root;

            return 1;
        }


        if (ast_root != nullptr) delete ast_root;
    }
    catch (const Exception & error) {
        cout << "when parser initing :" << endl;
        cout  << "\t" << error.what() << endl;

        return 1;
    }


    return 0;
}
