CC=g++.exe
CFLAGS=
LDFLAGS=-fdiagnostics-color=always -g -static-libgcc
INCLUDEPATH=-I./SFML-2.5.1/include
LIBSPATH=-L./SFML-2.5.1/lib
LIBS=-lmingw32 -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lsfml-main -mwindows
SOURCES=Calcs.cpp GameScene.cpp SplashScreen.cpp GamePlay.cpp Actor.cpp Cursor.cpp Enemy.cpp Game.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main.exe

all:
	$(CC) $(LDFLAGS) $(SOURCES) $(INCLUDEPATH) -o $(EXECUTABLE) $(LIBSPATH) $(LIBS)
