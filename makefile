PROG = fastype
CC = g++
CPPFLAGS = -O2 -std=c++11 -Wall
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
OBJS = main.o game.o state.o MainMenuState.o GameState.o button.o player.o wave.o enemy.o gameover.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(SFMLFLAGS)

main.o :
	$(CC) -c $(CPPFLAGS) main.cpp
game.o:
	$(CC) -c $(CPPFLAGS) game.cpp
state.o:
	$(CC) -c $(CPPFLAGS) state.cpp
MainMenuState.o:
	$(CC) -c $(CPPFLAGS) MainMenuState.cpp
GameState.o:
	$(CC) -c $(CPPFLAGS) GameState.cpp
button.o:
	$(CC) -c $(CPPFLAGS) button.cpp
player.o:
	$(CC) -c $(CPPFLAGS) player.cpp
wave.o:
	$(CC) -c $(CPPFLAGS) wave.cpp
enemy.o:
	$(CC) -c $(CPPFLAGS) enemy.cpp
gameover.o:
	$(CC) -c $(CPPFLAGS) gameover.cpp

clean :
	rm -f core $(PROG) $(OBJS)