CC = g++
CFLAGS = --std=c++17 -Wall
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

DEPS = game.hpp player.hpp

OBJECTS = main.o game.o player.o

PROGRAM = Fight

.PHONY: all clean lint

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm -f *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp
