#/usr/bin/make

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g

vpath %.hpp ../../inc
vpath %.cpp ../../src

ast_test : ast_test.o any.o token.o AST.o symbol.o
	$(CXX) $(CXXFLAGS) -o ast_test ast_test.o any.o token.o AST.o symbol.o

ast_test.o : ast_test.cpp
	$(CXX) $(CXXFLAGS) -c $<

symbol.o : symbol.cpp symbol.hpp
	$(CXX) $(CXXFLAGS) -c $<

AST.o : AST.cpp AST.hpp
	$(CXX) $(CXXFLAGS) -c $<

token.o : token.cpp token.hpp
	$(CXX) $(CXXFLAGS) -c $<

any.o : any.cpp any.hpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY:clean
clean :
	rm -rf ast_test.o any.o token.o AST.o
