#/usr/bin/make

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g

vpath %.hpp ../inc
vpath %.cpp ../src

.PHONY : none
none :
	@echo saw no argument, build nothing.

obj_symbol := symbol.o
obj_symbol_table := $(obj_symbol) symbol_table.o

exes := test_symbol test_symbol_table

.PHONY : all
all : $(exes)

test_symbol : $(ObjSymbol)
	$(CXX) $(CXXFLAGS) -o symbol $(ObjSymbol)

$(obj_symbol) : %.o : %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $<

test_symbol.o : test_symbol.cpp
	$(CXX) $(CXXFLAGS) -c $<


test_symbol_table : $(obj_symbol_table) test_symbol_table.o
	$(CXX) $(CXXFLAGS) -o symbol_table $(obj_symbol_table) test_symbol_table.o

$(obj_symbol_table) : %.o : %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $<


test_symbol_table.o : test_symbol_table.cpp
	$(CXX) $(CXXFLAGS) -c $<