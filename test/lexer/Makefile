#/usr/bin/make

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g

vpath %.hpp ../../inc
vpath %.cpp ../../src

lexer_test : lexer_test.o lexer.o token.o any.o exception.o
	$(CXX) $(CXXFLAGS) -o lexer_test lexer_test.o lexer.o token.o any.o exception.o

lexer_test.o : lexer_test.cpp
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
	rm -rf lexer_test.o lexer.o token.o any.o exception.o
