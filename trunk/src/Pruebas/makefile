OBJS = main.o hash_extensible.o BloqueHash.o RegistroIndice.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

Pruebas: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o Pruebas

main.o: main.cpp PruebasHash.h PruebasRegistroIndice.h
	$(CC) $(CFLAGS) main.cpp

PruebasHash.h: ../hash_extensible.h

PruebasRegistroIndice.h: ../RegistroIndice.h

hash_extensible.o: ../hash_extensible.cpp ../hash_extensible.h
	$(CC) $(CFLAGS) ../hash_extensible.cpp

../hash_extensible.h: ../BloqueHash.h ../RegistroIndice.h

BloqueHash.o: ../BloqueHash.cpp ../BloqueHash.h
	$(CC) $(CFLAGS) ../BloqueHash.cpp
	
../BloqueHash.h: ../Bloque.h ../RegistroIndice.h

RegistroIndice.o: ../RegistroIndice.cpp ../RegistroIndice.h
	$(CC) $(CFLAGS) ../RegistroIndice.cpp