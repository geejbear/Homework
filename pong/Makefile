TARGET = $(shell basename $(CURDIR))
LIBS = -lm -lSDL2 -ldos
INCL = -I/usr/include -I../play -I../utility
#SRC = *.c ../play/play.c ../utility/utility.c

all:
	cc pong.c play.c $(SRC) $(INCL) $(LIBS) -o $(TARGET)
