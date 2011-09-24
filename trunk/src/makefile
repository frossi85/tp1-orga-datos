OBJS = main.o Cargo.o Distrito.o Eleccion.o Grabable.o Candidato.o Configuracion.o Informe.o Lista.o Logger.o Logueable.o \
Votante.o Utilidades.o VotoElectronicoExcepcion.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic -c $(DEBUG)
LFLAGS = -Wall -pedantic $(DEBUG)

VotoElectronico: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o VotoElectronico

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Cargo.o: Cargo.cpp Cargo.h Grabable.h Logueable.h
	$(CC) $(CFLAGS) Cargo.cpp

Distrito.o: Distrito.cpp Distrito.h Grabable.h Logueable.h
	$(CC) $(CFLAGS) Distrito.cpp

Eleccion.o: Eleccion.cpp Eleccion.h
	$(CC) $(CFLAGS) Eleccion.cpp

Eleccion.h: Cargo.h Distrito.h Grabable.h Logueable.h

Grabable.o: Grabable.cpp Grabable.h
	$(CC) $(CFLAGS) Grabable.cpp
	
Candidato.o: Candidato.cpp Candidato.h
	$(CC) $(CFLAGS) Candidato.cpp
	
Configuracion.o: Configuracion.cpp Configuracion.h
	$(CC) $(CFLAGS) Configuracion.cpp
	
Informe.o: Informe.cpp Informe.h
	$(CC) $(CFLAGS) Informe.cpp
	
Lista.o: Lista.cpp Lista.h
	$(CC) $(CFLAGS) Lista.cpp
	
Logger.o: Logger.cpp Logger.h
	$(CC) $(CFLAGS) Logger.cpp
	
Logger.h: Logueable.h Utilidades.h VotoElectronicoExcepcion.h
	
Logueable.o: Logueable.cpp Logueable.h
	$(CC) $(CFLAGS) Logueable.cpp
	
Votante.o: Votante.cpp Votante.h
	$(CC) $(CFLAGS) Votante.cpp
	
Utilidades.o: Utilidades.cpp Utilidades.h
	$(CC) $(CFLAGS) Utilidades.cpp
	
VotoElectronicoExcepcion.o: VotoElectronicoExcepcion.cpp VotoElectronicoExcepcion.h
	$(CC) $(CFLAGS) VotoElectronicoExcepcion.cpp
