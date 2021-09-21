SRCDIR=../Game/Game
INCLUDE=-I/opt/homebrew/include/

#Compilation Flags
CFLAGS=-std=c++11 $(INCLUDE)
#Linking Flags
LFLAGS=-L/opt/homebrew/lib -lsfml-graphics -lisfml-system -lsfml-window

CC=g++

.PHONY : all
.main : all

#List of all object files to link together.
OBJS=main.o

Ball.o : $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) -c $<


