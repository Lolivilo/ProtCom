# Makefile
# Compilation des primitives UDP
#
# Travaux Pratiques réseau Info3
#

CFLAGS = -Wall -std=c99 -g

CC	 = gcc
EXEC = tp

all: $(EXEC)

tp: tp.o traitement.o notreClient.o ihm.o
	$(CC) -o tp tp.o traitement.o notreClient.o ihm.o $(CFLAGS)

traitement.o: traitement.c
	$(CC) -o traitement.o -c traitement.c $(CFLAGS)


notreClient.o: notreClient.c
	$(CC) -o notreClient.o -c notreClient.c $(CFLAGS)

ihm.o: ihm.c
	$(CC) -o ihm.o -c ihm.c $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)

