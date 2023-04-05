#/usr/bin/make

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g

vpath %.hpp ../../inc
vpath %.cpp ../../src

semantic_analyzer_test : semantic_analyzer_test.o semantic_analyzer.o  node_visitor.o scoped_symbol_table.o symbol.o parser.o AST.o lexer.o token.o any.o exception.o
	$(CXX) $(CXXFLAGS) -o $@ $?

semantic_analyzer_test.o : semantic_analyzer_test.cpp
	$(CXX) $(CXXFLAGS) -c $<

semantic_analyzer.o : semantic_analyzer.cpp semantic_analyzer.hpp
	$(CXX) $(CXXFLAGS) -c $<

node_visitor.o : node_visitor.cpp node_visitor.hpp
	$(CXX) $(CXXFLAGS) -c $<

scoped_symbol_table.o : scoped_symbol_table.cpp scoped_symbol_table.hpp
	$(CXX) $(CXXFLAGS) -c $<

symbol.o : symbol.cpp symbol.hpp
	$(CXX) $(CXXFLAGS) -c $<

parser.o : parser.cpp parser.hpp
	$(CXX) $(CXXFLAGS) -c $<

AST.o : AST.cpp AST.hpp
	$(CXX) $(CXXFLAGS) -c $<

lexer.o : lexer.cpp lexer.hpp
	$(CXX) $(CXXFLAGS) -c $<

token.o : token.cpp token.hpp
	$(CXX) $(CXXFLAGS) -c $<

any.o : any.cpp any.hpp
	$(CXX) $(CXXFLAGS) -c $<

exception.o : exception.cpp exception.hpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY:clean
clean :
	rm -rf lexer_test.o lexer.o token.o
