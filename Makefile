CC = g++
CFLAGS = --std=c++17 -Wall 
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system 
# Your .hpp files
DEPS = game.hpp
# Your compiled .o files
OBJECTS = game.o
# The name of your program
PROGRAM = game

.PHONY: all clean lint

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

test: test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
game: main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
game: game.a $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
	
game.a: $(OBJECTS)
	ar rcs $@ $^
pname.a: $(OBJECTS)
	ar rcs $@ $^
clean:
	rm *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp