CC = gcc
CFLAGS = -Wall
OBJ = mainn.o tela_menu.o jogo.o

flybird: $(OBJ)
	$(CC) $(OBJ) -o flybird

mainn.o: mainn.c tela_menu.h jogo.h
	$(CC) $(CFLAGS) -c mainn.c

tela_menu.o: tela_menu.c tela_menu.h
	$(CC) $(CFLAGS) -c tela_menu.c

jogo.o: jogo.c jogo.h
	$(CC) $(CFLAGS) -c jogo.c

clean:
	rm -f *.o flybird
