SRCDIR=../game
INCLUDE=-I/opt/homebrew/include/
# Compilation Flags
CFLAGS=-std=c++11 $(INCLUDE)
# Linking Flags
LFLAGS=-L/opt/homebrew/lib -lsfml-graphics -lsfml-system -lsfml-window
CC=g++
.PHONY : all
all : game
OBJS=main.o Bullet.o Enemy.o EnemyBullet.o Explosion.o Player.o Screen.o
main.o : $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) -c $<
Bullet.o : $(SRCDIR)/Bullet.cpp
	$(CC) $(CFLAGS) -c $<
Enemy.o : $(SRCDIR)/Enemy.cpp
	$(CC) $(CFLAGS) -c $<
EnemyBullet.o : $(SRCDIR)/EnemyBullet.cpp
	$(CC) $(CFLAGS) -c $<
Explosion.o : $(SRCDIR)/Explosion.cpp
	$(CC) $(CFLAGS) -c $<
Player.o : $(SRCDIR)/Player.cpp
	$(CC) $(CFLAGS) -c $<
Screen.o : $(SRCDIR)/Screen.cpp
	$(CC) $(CFLAGS) -c $<
game : $(OBJS)
	$(CC) $(LFLAGS) -o game $(OBJS)
