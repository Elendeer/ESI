#include <iostream>

#include "../../inc/parser.hpp"
#include "../../inc/semantic_analyzer.hpp"
#include "../../inc/file_reader.hpp"

int main() {
    using namespace std;
    using namespace ESI;

    string input = "\
    program test;{comments}\
    var\
        a : integer;\
    function testfunc : real;\
    begin\
        testfunc := 3.3;\
    end;\
    begin\
        writeln(testfunc);\
        writeln(a);\
    end.";

    Lexer lexer(input);
    Parser parser(lexer);

    AST* root = parser.parse();

    SemanticAnalyzer semantic_analyzer(root, true);
    try {
        cout << "Semantic analyzing ..." << endl;
        semantic_analyzer.analyze();
        // semantic_analyzer.printBuildInTypeSymbolTable();
        cout << "Semantic analysis finished." << endl << endl;
    }
    catch (const SemanticError & error) {
        cout << "When building symbol table from AST :" << endl;
        cout << error.what() << endl;
        cout << "error met when semantic analyzing, stop." << endl;

        if (root != nullptr) {
            delete root;
            root = nullptr;
        }

        return 1;
    }

    if (root != nullptr) delete root;

    return 0;
}