OBJS = main.o Cargo.o Conteo.o Distrito.o Eleccion.o Grabable.o Candidato.o Configuracion.o Informe.o Lista.o Logger.o Logueable.o \
Votante.o Utilidades.o VotoElectronicoExcepcion.o BloqueHash.o RegistroIndice.o menu.o DataAccess.o hash_extensible.o Menu_votante.o \
Tester.o Test.o TestCargo.o TestDataAccess.o TestDistrito.o TestEleccion.o TestLista.o \
TestVotante.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

VotoElectronico: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o VotoElectronico

main.o: main.cpp menu.h Distrito.h Cargo.h DataAcces.h
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
	
Candidato.o: Candidato.cpp Candidato.h Votante.h
	$(CC) $(CFLAGS) Candidato.cpp

Candidato.h: Grabable.h Logueable.h Votante.h Cargo.h

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

Conteo.o: Conteo.cpp Conteo.h Grabable.h Logueable.h Lista.h Distrito.h Eleccion.h
	$(CC) $(CFLAGS) Conteo.cpp
	
Utilidades.o: Utilidades.cpp Utilidades.h
	$(CC) $(CFLAGS) Utilidades.cpp
	
VotoElectronicoExcepcion.o: VotoElectronicoExcepcion.cpp VotoElectronicoExcepcion.h
	$(CC) $(CFLAGS) VotoElectronicoExcepcion.cpp

RegistroIndice.o: RegistroIndice.cpp RegistroIndice.h
	$(CC) $(CFLAGS) RegistroIndice.cpp
	
BloqueHash.o: BloqueHash.cpp BloqueHash.h
	$(CC) $(CFLAGS) BloqueHash.cpp
	
BloqueHash.h: Bloque.h RegistroIndice.h

menu.o: menu.cpp menu.h
	$(CC) $(CFLAGS) menu.cpp

menu.h: Menu_votante.h

Menu_votante.o: Menu_votante.cpp Menu_votante.h
	$(CC) $(CFLAGS) Menu_votante.cpp
	
Menu_votante.h: Votante.h Eleccion.h Lista.h

DataAccess.o: DataAccess.cpp DataAccess.h
	$(CC) $(CFLAGS) DataAccess.cpp
	
DataAcces.h: Grabable.h Logueable.h Logger.h Utilidades.h VotoElectronicoExcepcion.h Configuracion.h Distrito.h
	
hash_extensible.o: hash_extensible.cpp hash_extensible.h
	$(CC) $(CFLAGS) hash_extensible.cpp

hash_extensible.h: BloqueHash.h RegistroIndice.h

Tester.o: Tests/Tester.cpp Tests/Tester.h Tests/Test.h Tests/TestCargo.h Tests/TestDataAccess.h Tests/TestDistrito.h \
Tests/TestEleccion.h Tests/TestLista.h Tests/TestVotante.h
	$(CC) $(CFLAGS) Tests/Tester.cpp
	
Test.o: Tests/Test.cpp Tests/Test.h
	$(CC) $(CFLAGS) Tests/Test.cpp

TestCargo.o: Tests/TestCargo.cpp Tests/TestCargo.h
	$(CC) $(CFLAGS) Tests/TestCargo.cpp
	
TestCargo.h: Tests/Test.h Cargo.h

TestDataAccess.o: Tests/TestDataAccess.cpp Tests/TestDataAccess.h
	$(CC) $(CFLAGS) Tests/TestDataAccess.cpp
	
TestDataAccess.h: Tests/Test.h DataAccess.h

TestDistrito.o: Tests/TestDistrito.cpp Tests/TestDistrito.h
	$(CC) $(CFLAGS) Tests/TestDistrito.cpp
	
TestDistrito.h: Tests/Test.h Distrito.h

TestEleccion.o: Tests/TestEleccion.cpp Tests/TestEleccion.h
	$(CC) $(CFLAGS) Tests/TestEleccion.cpp
	
TestEleccion.h: Tests/Test.h Eleccion.h

TestLista.o: Tests/TestLista.cpp Tests/TestLista.h
	$(CC) $(CFLAGS) Tests/TestLista.cpp
	
TestLista.h: Tests/Test.h Lista.h

TestVotante.o: Tests/TestVotante.cpp Tests/TestVotante.h
	$(CC) $(CFLAGS) Tests/TestVotante.cpp
	
TestVotante.h: Tests/Test.h Votante.h