CC = gcc
CFLAGS = -Wall
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: flybird

flybird: main.o tela_menu.o tela_jogo.o
	$(CC) main.o tela_menu.o tela_jogo.o -o flybird $(LIBS)

main.o: main.c tela_menu.h tela_jogo.h
	$(CC) $(CFLAGS) -c main.c

tela_menu.o: tela_menu.c tela_menu.h
	$(CC) $(CFLAGS) -c tela_menu.c

tela_jogo.o: tela_jogo.c tela_jogo.h
	$(CC) $(CFLAGS) -c tela_jogo.c

clean:
	rm -f *.o flybird
