.PHONY: all clean

CC = g++
CPPFLAGS = -g -Wall -std=c++11
INCLUDE = -Iinc

FLAGS = $(CPPFLAGS) $(INCLUDE)
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

all: pirate_game

pirate_game: $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@

$(OBJ): src/%.o : src/%.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf src/*.o pirate_game
