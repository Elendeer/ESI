CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g #-fsanitize=address
# LDFLAGS =  -fsanitize=address

vpath %.cpp src
SRC = main.cpp \
interpreter.cpp \
parser.cpp \
lexer.cpp \
AST.cpp \
token.cpp \
any.cpp

OBJ = $(SRC:.cpp=.o)
EXEC = ESI

all: $(EXEC)

$(EXEC): $(OBJ)
	# $(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)
	$(CXX) -o $@ $(OBJ) # $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)