TARGET = $(shell basename $(CURDIR))
LIBS = -lm -lSDL2 -ltextmode
INCL = -I../include
SRC = *.c ../shared/utility.c

all:
	cc $(SRC) $(INCL) $(LIBS) -o $(TARGET)
