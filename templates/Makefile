TARGET = $(shell basename $(CURDIR))
LIBS = -lm -lSDL2 -ldos
INCL = -I../include
SRC = *.c ../shared/*.c

all:
	cc $(SRC) $(INCL) $(LIBS) -o $(TARGET)
