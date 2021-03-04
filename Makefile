CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g

# path
DIR_INC	:= ./inc
DIR_SRC	:= ./src
DIR_OBJ	:= ./build

# Important files.
SRC		:= $(wildcard $(DIR_SRC)/*.cpp)
OBJ		:= $(SRC:$(DIR_SRC)%.cpp=$(DIR_OBJ)%.o)
EXEC	:= ESI

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LBLIBS)

$(OBJ) : $(DIR_OBJ)/%.o : $(DIR_SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(DIR_OBJ)/%.d : $(DIR_SRC)/%.cpp
	@set -e; rm -f $@; \
	$(CXX) $(CXXFLAGS) -MM $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(DIR_OBJ)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -rf $@.$$$$

include $(OBJ:.o=.d)

.PHONY : clean
clean:
	rm -rf $(OBJ) $(EXEC)