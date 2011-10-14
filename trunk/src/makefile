OBJS = main.o Cargo.o Conteo.o Distrito.o Eleccion.o Grabable.o Candidato.o Configuracion.o Informe.o Lista.o Logger.o Logueable.o \
Votante.o Utilidades.o VotoElectronicoExcepcion.o BloqueHash.o RegistroIndice.o menu.o DataAccess.o hash_extensible.o Menu_votante.o \
RegistroArbol.o Nodo.o ArbolBMas.o ManejoIDs.o ABMentidades.o Tester.o Test.o TestCargo.o TestDataAccess.o TestDistrito.o TestEleccion.o TestVotante.o \
TestCandidato.o TestLista.o TestABMentidades.o TestPersistencias.o DataGetter.o ConsultaEntidades.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

VotoElectronico: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o VotoElectronico

main.o: main.cpp menu.h Distrito.h Cargo.h DataAcces.h Tests/Tester.h RegistroArbol.h Nodo.h ArbolBMas.h
	$(CC) $(CFLAGS) main.cpp

Cargo.o: Cargo.cpp Cargo.h ManejoIDs.h
	$(CC) $(CFLAGS) Cargo.cpp

Cargo.h: Grabable.h Logueable.h Utilidades.h Configuracion.h

Distrito.o: Distrito.cpp Distrito.h
	$(CC) $(CFLAGS) Distrito.cpp

Distrito.h: Grabable.h Logueable.h ManejoIDs.h Utilidades.h VotoElectronicoExcepcion.h Configuracion.h

Eleccion.o: Eleccion.cpp Eleccion.h ManejoIDs.h 
	$(CC) $(CFLAGS) Eleccion.cpp

Eleccion.h: Cargo.h Distrito.h RegistroIndice.h hash_extensible.h Configuracion.h

Grabable.o: Grabable.cpp Grabable.h
	$(CC) $(CFLAGS) Grabable.cpp
	
Candidato.o: Candidato.cpp Candidato.h ManejoIDs.h
	$(CC) $(CFLAGS) Candidato.cpp

Candidato.h: Grabable.h Logueable.h Votante.h Cargo.h

Configuracion.o: Configuracion.cpp Configuracion.h
	$(CC) $(CFLAGS) Configuracion.cpp
	
Informe.o: Informe.cpp Informe.h DataAccess.h
	$(CC) $(CFLAGS) Informe.cpp

Informe.h: Eleccion.h Distrito.h Lista.h Conteo.h
	
Lista.o: Lista.cpp Lista.h ManejoIDs.h
	$(CC) $(CFLAGS) Lista.cpp

Lista.h: Grabable.h Logueable.h Eleccion.h
	
Logger.o: Logger.cpp Logger.h
	$(CC) $(CFLAGS) Logger.cpp
	
Logger.h: Logueable.h Utilidades.h VotoElectronicoExcepcion.h
	
Logueable.o: Logueable.cpp Logueable.h
	$(CC) $(CFLAGS) Logueable.cpp
	
Votante.o: Votante.cpp Votante.h ManejoIDs.h
	$(CC) $(CFLAGS) Votante.cpp

Votante.h: Grabable.h Logueable.h Distrito.h Eleccion.h Lista.h

Conteo.o: Conteo.cpp Conteo.h
	$(CC) $(CFLAGS) Conteo.cpp

Conteo.h: Grabable.h Lista.h Logueable.h Distrito.h Eleccion.h Configuracion.h hash_extensible.h DataAccess.h
	
Utilidades.o: Utilidades.cpp Utilidades.h
	$(CC) $(CFLAGS) Utilidades.cpp
	
VotoElectronicoExcepcion.o: VotoElectronicoExcepcion.cpp VotoElectronicoExcepcion.h
	$(CC) $(CFLAGS) VotoElectronicoExcepcion.cpp

RegistroIndice.o: RegistroIndice.cpp RegistroIndice.h
	$(CC) $(CFLAGS) RegistroIndice.cpp
	
BloqueHash.o: BloqueHash.cpp BloqueHash.h
	$(CC) $(CFLAGS) BloqueHash.cpp
	
BloqueHash.h: Bloque.h RegistroIndice.h

menu.o: menu.cpp menu.h DataAccess.h
	$(CC) $(CFLAGS) menu.cpp

menu.h: Menu_votante.h

Menu_votante.o: Menu_votante.cpp Menu_votante.h
	$(CC) $(CFLAGS) Menu_votante.cpp
	
Menu_votante.h: Votante.h Eleccion.h Lista.h

DataAccess.o: DataAccess.cpp DataAccess.h
	$(CC) $(CFLAGS) DataAccess.cpp
	
DataAcces.h: Grabable.h Logueable.h Logger.h Utilidades.h VotoElectronicoExcepcion.h Configuracion.h Conteo.h

DataGetter.o: DataGetter.cpp DataGetter.h
	$(CC) $(CFLAGS) DataGetter.cpp

DataGetter.h: Distrito.h Conteo.h Votante.h Eleccion.h Lista.h

hash_extensible.o: hash_extensible.cpp hash_extensible.h
	$(CC) $(CFLAGS) hash_extensible.cpp

hash_extensible.h: BloqueHash.h RegistroIndice.h

Tester.o: Tests/Tester.cpp Tests/Tester.h Tests/Test.h Tests/TestCargo.h Tests/TestDataAccess.h Tests/TestDistrito.h \
Tests/TestEleccion.h Tests/TestVotante.h Tests/TestCandidato.h Tests/TestLista.h Tests/TestABMentidades.h \
Tests/TestPersistencias.h
	$(CC) $(CFLAGS) Tests/Tester.cpp
	
Test.o: Tests/Test.cpp Tests/Test.h
	$(CC) $(CFLAGS) Tests/Test.cpp

TestCargo.o: Tests/TestCargo.cpp Tests/TestCargo.h DataAccess.h
	$(CC) $(CFLAGS) Tests/TestCargo.cpp
	
Tests/TestCargo.h: Tests/Test.h Cargo.h

TestDataAccess.o: Tests/TestDataAccess.cpp
	$(CC) $(CFLAGS) Tests/TestDataAccess.cpp
	
Tests/TestDataAccess.h: Tests/Test.h DataAccess.h

TestDistrito.o: Tests/TestDistrito.cpp Tests/TestDistrito.h
	$(CC) $(CFLAGS) Tests/TestDistrito.cpp
	
Tests/TestDistrito.h: Tests/Test.h Distrito.h

TestEleccion.o: Tests/TestEleccion.cpp Tests/TestEleccion.h DataAccess.h
	$(CC) $(CFLAGS) Tests/TestEleccion.cpp
	
Tests/TestEleccion.h: Tests/Test.h Eleccion.h Cargo.h Distrito.h

TestLista.o: Tests/TestLista.cpp Tests/TestLista.h
	$(CC) $(CFLAGS) Tests/TestLista.cpp
	
Tests/TestLista.h: Tests/Test.h Lista.h Eleccion.h Cargo.h Distrito.h

TestVotante.o: Tests/TestVotante.cpp Tests/TestVotante.h DataAccess.h
	$(CC) $(CFLAGS) Tests/TestVotante.cpp
	
Tests/TestVotante.h: Tests/Test.h Votante.h Distrito.h

TestCandidato.o: Tests/TestCandidato.cpp Tests/TestCandidato.h Eleccion.h Distrito.h
	$(CC) $(CFLAGS) Tests/TestCandidato.cpp
	
Tests/TestCandidato.h: Tests/Test.h Candidato.h Cargo.h Lista.h

TestABMentidades.o: Tests/TestABMentidades.cpp Tests/TestABMentidades.h ABM\ Entidades/ConsultaEntidades.h
	$(CC) $(CFLAGS) Tests/TestABMentidades.cpp

Tests/TestABMentidades.h: Tests/Test.h ABM\ Entidades/ABMentidades.h ABM\ Entidades/ConsultaEntidades.h

TestPersistencias.o: Tests/TestPersistencias.cpp Tests/TestPersistencias.h
	$(CC) $(CFLAGS) Tests/TestPersistencias.cpp

Tests/TestPersistencias.h: Tests/Test.h Distrito.h Cargo.h Eleccion.h DataAccess.h hash_extensible.h RegistroIndice.h \
Configuracion.h

RegistroArbol.o: RegistroArbol.h RegistroArbol.cpp
	$(CC) $(CFLAGS) RegistroArbol.cpp
	
RegistroArbol.h: Utilidades.h VotoElectronicoExcepcion.h

Nodo.o: Nodo.h Nodo.cpp RegistroArbol.h
	$(CC) $(CFLAGS) Nodo.cpp
	
ArbolBMas.o: ArbolBMas.h ArbolBMas.cpp
	$(CC) $(CFLAGS) ArbolBMas.cpp

ArbolBMas.h: RegistroArbol.h Nodo.h

ManejoIDs.o: ManejoIDs.cpp ManejoIDs.h
	$(CC) $(CFLAGS) ManejoIDs.cpp

ManejoIDs.h: Configuracion.h

ABMentidades.o: ABM\ Entidades/ABMentidades.cpp ABM\ Entidades/ABMentidades.h
	$(CC) $(CFLAGS) ABM\ Entidades/ABMentidades.cpp

ABM\ Entidades/ABMentidades.h: DataAccess.h Configuracion.h hash_extensible.h Eleccion.h Distrito.h Cargo.h Votante.h \
Lista.h Candidato.h RegistroIndice.h ManejoIDs.h

ConsultaEntidades.o: ABM\ Entidades/ConsultaEntidades.cpp ABM\ Entidades/ConsultaEntidades.h
	$(CC) $(CFLAGS) ABM\ Entidades/ConsultaEntidades.cpp
	
ABM\ Entidades/ConsultaEntidades.h: Grabable.h DataAccess.h hash_extensible.h RegistroIndice.h