#/usr/bin/make

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g

vpath %.hpp ../inc
vpath %.cpp ../src

test : test.o token.o any.o lexer.o
	$(CXX) $(CXXFLAGS) -o test test.o token.o any.o lexer.o

lexer.o : lexer.cpp lexer.hpp token.hpp any.hpp
	$(CXX) $(CXXFLAGS) -c $<

test.o : test.cpp token.hpp any.hpp
	$(CXX) $(CXXFLAGS) -c $<

token.o : token.cpp token.hpp any.hpp
	$(CXX) $(CXXFLAGS) -c $<

any.o : any.cpp any.hpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY:clean
clean :
	rm -rf test.o token.o any.o