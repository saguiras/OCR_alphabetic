CC=gcc -rdynamic

CPPFLAGS =  `pkg-config gtk+-3.0 --cflags sdl` -MMD
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS =
LDLIBS= `pkg-config gtk+-3.0 --libs sdl` -lSDL_image -lm

SRC = main.c  
OBJ= $(SRC:.c=.o)
DEP= $(SRC:.c=.d)

all: main

main: $(OBJ)

clean:
