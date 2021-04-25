#/usr/bin/make

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g

vpath %.hpp ../inc
vpath %.cpp ../src

test : test.o call_stack.o any.o
	$(CXX) $(CXXFLAGS) -o test test.o call_stack.o any.o

test.o : test.cpp
	$(CXX) $(CXXFLAGS) -c $<

call_stack.o : call_stack.cpp call_stack.hpp
	$(CXX) $(CXXFLAGS) -c $<

any.o : any.cpp any.hpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY:clean
clean :
	rm -rf test.o call_stack.o any.o
