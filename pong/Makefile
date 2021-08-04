TARGET = $(shell basename $(CURDIR))
LIBS = -lm -lSDL2 -ldos
<<<<<<< HEAD
INCL = -I/usr/include -I../play -I../utility
=======
INCL = -I../play -I../utility
#INCL += -I/usr/include #delete if not needed
>>>>>>> 438bc6004d9daa86e3d0f88e73c856d7d859d3a1
SRC = *.c ../play/play.c ../utility/utility.c

all:
	cc $(SRC) $(INCL) $(LIBS) -o $(TARGET)
