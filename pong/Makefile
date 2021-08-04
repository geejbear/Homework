TARGET = $(shell basename $(CURDIR))
LIBS = -lm -lSDL2 -ldos
INCL = -I../play -I../utility
#INCL += -I/usr/include #delete if not needed
SRC = *.c ../play/play.c ../utility/utility.c

all:
	cc $(SRC) $(INCL) $(LIBS) -o $(TARGET)
