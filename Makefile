CC=gcc -rdynamic

CPPFLAGS =  `pkg-config --cflags sdl` -MMD
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS =
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

SRC = main.c treatment/treatment.c tools/tools.c tools/display_tools.c	CharDetection/CharDetection.c neural_network/neural_network_XOR.c neural_network/neural_Tools.c neural_network/neural_network.c  neural_network/neural_network_char.c

OBJ= $(SRC:.c=.o)
DEP= $(SRC:.c=.d)

all: main

main: $(OBJ)

run: all
	./main

clean:
	${RM} *.o */*.o *.d */*.d 

# END           
