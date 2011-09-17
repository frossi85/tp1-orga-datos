OBJS = main.o Cargo.o Distrito.o Eleccion.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic -c $(DEBUG)
LFLAGS = -Wall -pedantic $(DEBUG)

Voto Electronico: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o Voto_Electronico

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Cargo.o: Cargo.cpp Cargo.h
	$(CC) $(CFLAGS) Cargo.cpp

Distrito.o: Distrito.cpp Distrito.h
	$(CC) $(CFLAGS) Distrito.cpp

Eleccion.o: Eleccion.cpp Eleccion.h
	$(CC) $(CFLAGS) Eleccion.cpp

Eleccion.h: Cargo.h Distrito.h
