#/usr/bin/make

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g

vpath %.hpp ../../inc
vpath %.cpp ../../src

any_test : any_test.o any.o
	$(CXX) $(CXXFLAGS) -o any_test any_test.o any.o

any_test.o : any_test.cpp
	$(CXX) $(CXXFLAGS) -c $<

any.o : any.cpp any.hpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY:clean
clean :
	rm -rf any_test.o any.o
