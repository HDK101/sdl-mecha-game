CC=gcc
CFLAGS=-w -Wall
LIBS=-lm -lSDL2 -lSDL2_image
SOURCES=$(wildcard src/*.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))
EXE=bin/main

all: $(EXE)

$(EXE): $(OBJECTS)
	@rsync -r assets bin
	$(CC) $(OBJECTS) -g -o  $(EXE) $(CFLAGS) $(LIBS)

%.o: %.c
	$(CC) -g -c $< -o $@ $(CFLAGS) $(LIBS)

clean:
	@rm src/*.o
	@rm -Rf bin/*
