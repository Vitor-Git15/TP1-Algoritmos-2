#---------------------------------------------------------------------
# File      		: Makefile
# Content       : Compile the compression program
# Author        : Vitor Emanuel Ferreira Vital (vitorvital@dcc.ufmg.br)
# History	      : 2023-04-20 - file created
#---------------------------------------------------------------------
# Options       : make all - Compiles all and generates the executable
#               : make clean - Removes object files and executable
#---------------------------------------------------------------------

CXX = g++
SRC = src
OBJ = obj
INC = include
TEST = test

OBJS = $(OBJ)/LZ78.o $(OBJ)/Trie.o $(OBJ)/main.o
HDRS = $(INC)/LZ78.hpp $(INC)/Trie.hpp
CFLAGS = -std=c++11 -Wall -c -I$(INC)

EXE = main

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS)
$(OBJ)/LZ78.o: $(HDRS) $(SRC)/LZ78.cpp
	$(CXX) $(CFLAGS) -o  $(OBJ)/LZ78.o $(SRC)/LZ78.cpp 
$(OBJ)/Trie.o: $(HDRS) $(SRC)/Trie.cpp
	$(CXX) $(CFLAGS) -o  $(OBJ)/Trie.o $(SRC)/Trie.cpp 
$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CXX) $(CFLAGS) -o  $(OBJ)/main.o $(SRC)/main.cpp 

clean:
	rm -f $(OBJ)/*.o $(EXE)