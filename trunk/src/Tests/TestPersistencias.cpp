/*
 * TestPersistencias.cpp
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */


#include "TestPersistencias.h"

TestPersistencias::TestPersistencias() {}

TestPersistencias::~TestPersistencias() {}


/* Se crean 6 Distritos, se guardan en archivo y se recuperan en forma opuesta */
void TestPersistencias::TestDistrito() {

	cout << endl << "********************************************************" << endl;
	cout << "              Comienzo Test Distritos" << endl;
	cout << "********************************************************" << endl << endl;

	vector<Distrito> vecDistritos;

	UtilidadesTests::cargarDistritos(vecDistritos);
	int cantidadDistritos = vecDistritos.size();

	for(int i=0;i<cantidadDistritos;i++)	vecDistritos[i].Imprimir();

    unsigned long int offset[cantidadDistritos];

    for(int i=0;i<cantidadDistritos;i++) {
        offset[i] = dataAccess.Guardar(vecDistritos[i]);
        cout << "Offset de "<< vecDistritos[i].getNombre() << ": " << offset[i] << endl;
    }
    cout << endl;

    for(int i=0;i<cantidadDistritos;i++)     dataAccess.Leer(vecDistritos[i],offset[cantidadDistritos-1-i]);

	for(int i=0;i<cantidadDistritos;i++)	vecDistritos[i].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test Distritos" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 6 Cargos principales, con "i" cargos secundarios (i es indice de cargo).
 * Se guardan en archivo y se recuperan en forma opuesta */
void TestPersistencias::TestCargo() {

	cout << endl << "********************************************************" << endl;
	cout << "                Comienzo Test Cargos" << endl;
	cout << "********************************************************" << endl << endl;

	vector<Cargo> vecCargos;

	UtilidadesTests::cargarCargos(vecCargos);
	int cantidadCargos = vecCargos.size();

	for(int i=0;i<cantidadCargos;i++)	vecCargos[i].Imprimir();

    unsigned long int offset[cantidadCargos];

    for(int i=0;i<cantidadCargos;i++) {
        offset[i] = dataAccess.Guardar(vecCargos[i]);
        cout << "Offset de "<< vecCargos[i].getCargoPrincipal() << ": " << offset[i] << endl;
    }
    cout << endl;

    for(int i=0;i<cantidadCargos;i++)     dataAccess.Leer(vecCargos[i],offset[cantidadCargos-1-i]);

	for(int i=0;i<cantidadCargos;i++)	vecCargos[i].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                    Fin Test Cargos" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 6 Elecciones. Se guardan en archivo y se recuperan en forma opuesta*/
void TestPersistencias::TestEleccion() {

	cout << endl << "********************************************************" << endl;
	cout << "                Comienzo Test Eleccion" << endl;
	cout << "********************************************************" << endl << endl;

	 unsigned long int offset[6];

	 vector<Distrito> vecDistritos;
	 vector<Cargo> vecCargos;

	 UtilidadesTests::cargarDistritos(vecDistritos);
	 UtilidadesTests::cargarCargos(vecCargos);
	 int cantidadDistritos = vecDistritos.size();
	 int cantidadCargos = vecCargos.size();


    /* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
    ABMentidades ABMaux;
    bool exito = true;
    for (int i=0;i<cantidadDistritos;i++)	if (exito) exito = ABMaux.altaDistrito(vecDistritos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Distritos (verificar que no existan los hash de distrito)" << endl << endl;
    	return;
    }

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<cantidadCargos;i++)	if (exito) exito = ABMaux.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no existan los hash de cargo)" << endl << endl;
    	return;
    }

	vector<Eleccion> vecElecciones;

	UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);
	int cantidadElecciones = vecElecciones.size();

	for(int i=0;i<cantidadElecciones;i++) {
		vecElecciones[i].Imprimir();
		vecElecciones[i].ImprimirDistritos();
	}

	for(int i=0;i<cantidadElecciones;i++) {
		offset[i] = dataAccess.Guardar(vecElecciones[i]);
		cout << "Offset de " << vecElecciones[i].getFecha() << ": " << offset[i] << endl;
	}
	cout << endl;

    for(int i=0;i<cantidadElecciones;i++)	dataAccess.Leer(vecElecciones[i],offset[cantidadElecciones-1-i]);

	for(int i=0;i<cantidadElecciones;i++) {
		vecElecciones[i].Imprimir();
		vecElecciones[i].ImprimirDistritos();
	}

	cout << endl << "********************************************************" << endl;
	cout << "                    Fin Test Eleccion" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 9 votantes y se le asignan elecciones (una o mas) a cada uno.
 * Se guardan en archivo y luego se recuperan al reves. */
void TestPersistencias::TestVotante() {
	cout << endl << "********************************************************" << endl;
	cout << "              Comienzo Test Votantes" << endl;
	cout << "********************************************************" << endl << endl;

	/* Cargo valores */
	vector<Distrito> vecDistritos;
	UtilidadesTests::cargarDistritos(vecDistritos);
	int cantidadDistritos = vecDistritos.size();

	vector<Cargo> vecCargos;
	UtilidadesTests::cargarCargos(vecCargos);
	int cantidadCargos = vecCargos.size();

	/* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
	ABMentidades ABMaux;
	bool exito = true;
	for (int i=0;i<cantidadDistritos;i++)	if (exito) exito = ABMaux.altaDistrito(vecDistritos[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Distritos (verificar que no existan los hash de distrito)" << endl << endl;
	  	return;
	}

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<cantidadCargos;i++)	if (exito) exito = ABMaux.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no existan los hash de cargo)" << endl << endl;
    	return;
    }

    vector<Eleccion> vecElecciones;
    UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);
    int cantidadElecciones = vecElecciones.size();

	/* Guardo las elecciones. Verificar que ande antes el ABMentidades::altaEleccion() (ṔOR AHORA ANDA)*/
	/* Para que tenga exito, no debe existir el archivos de arbol de eleccion */
	exito = true;
	for (int i=0;i<cantidadElecciones;i++)	if (exito) exito = ABMaux.altaEleccion(vecElecciones[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Elecciones (verificar que no exista el arbol de eleccion)" << endl << endl;
	  	return;
	}

    vector<Votante> vecVotantes;
    UtilidadesTests::cargarVotantes(vecVotantes,vecDistritos,vecElecciones);
    int cantidadVotantes = vecVotantes.size();

	for(int i=0;i<cantidadVotantes;i++)	vecVotantes[i].Imprimir();

	unsigned long int offset[cantidadVotantes];

	for(int i=0;i<cantidadVotantes;i++) {
        offset[i] = dataAccess.Guardar(vecVotantes[i]);
        cout << "Offset de "<< vecVotantes[i].getDNI() << ": " << offset[i] << endl;
    }
    cout << endl;

    for(int i=0;i<cantidadVotantes;i++)     dataAccess.Leer(vecVotantes[i],offset[cantidadVotantes-1-i]);

	for(int i=0;i<cantidadVotantes;i++)	vecVotantes[i].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test Votantes" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 21 listas (6 nombres de listas, que se presentan a varias elecciones).
 * Se guardan en archivo y se recuperan al reves */
void TestPersistencias::TestLista() {
	cout << endl << "********************************************************" << endl;
	cout << "              Comienzo Test Listas" << endl;
	cout << "********************************************************" << endl << endl;

	/* Cargo valores */
	vector<Distrito> vecDistritos;
	UtilidadesTests::cargarDistritos(vecDistritos);
	int cantidadDistritos = vecDistritos.size();

	vector<Cargo> vecCargos;
	UtilidadesTests::cargarCargos(vecCargos);
	int cantidadCargos = vecCargos.size();

	/* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
	ABMentidades ABMaux;
	bool exito = true;
	for (int i=0;i<cantidadDistritos;i++)	if (exito) exito = ABMaux.altaDistrito(vecDistritos[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Distritos (verificar que no existan los hash de distrito)" << endl << endl;
	  	return;
	}

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<cantidadCargos;i++)	if (exito) exito = ABMaux.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no existan los hash de cargo)" << endl << endl;
    	return;
    }

    vector<Eleccion> vecElecciones;
    UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);
    int cantidadElecciones = vecElecciones.size();

	/* Guardo las elecciones. Verificar que ande antes el ABMentidades::altaEleccion() (ṔOR AHORA ANDA)*/
	/* Para que tenga exito, no debe existir el archivos de arbol de eleccion */
	exito = true;
	for (int i=0;i<cantidadElecciones;i++)	if (exito) exito = ABMaux.altaEleccion(vecElecciones[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Elecciones (verificar que no exista el arbol de eleccion)" << endl << endl;
	  	return;
	}

    vector<Lista> vecListas;
    UtilidadesTests::cargarListas(vecListas,vecElecciones);
    int cantidadListas = vecListas.size();

	for(int i=0;i<cantidadListas;i++)	vecListas[i].Imprimir();

	unsigned long int offset[cantidadListas];

	for(int i=0;i<cantidadListas;i++) {
        offset[i] = dataAccess.Guardar(vecListas[i]);
        cout << "Offset de "<< vecListas[i].getNombre() << "$" << vecListas[i].getEleccion().getFecha() << ": " << offset[i] << endl;
    }
    cout << endl;

    for(int i=0;i<cantidadListas;i++)     dataAccess.Leer(vecListas[i],offset[cantidadListas-1-i]);

	for(int i=0;i<cantidadListas;i++)	vecListas[i].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test Listas" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 6 candidatos, se guardan en archivo y se recuperan en forma opuesta */
void TestPersistencias::TestCandidato() {
	cout << endl << "********************************************************" << endl;
	cout << "              Comienzo Test Candidatos" << endl;
	cout << "********************************************************" << endl << endl;

	/* Cargo valores */
	vector<Distrito> vecDistritos;
	UtilidadesTests::cargarDistritos(vecDistritos);
	int cantidadDistritos = vecDistritos.size();

	vector<Cargo> vecCargos;
	UtilidadesTests::cargarCargos(vecCargos);
	int cantidadCargos = vecCargos.size();

	/* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
	ABMentidades ABMaux;
	bool exito = true;
	for (int i=0;i<cantidadDistritos;i++)	if (exito) exito = ABMaux.altaDistrito(vecDistritos[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Distritos (verificar que no existan los hash de distrito)" << endl << endl;
	  	return;
	}

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<cantidadCargos;i++)	if (exito) exito = ABMaux.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no existan los hash de cargo)" << endl << endl;
    	return;
    }

    vector<Eleccion> vecElecciones;
    UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);
    int cantidadElecciones = vecElecciones.size();

	/* Guardo las elecciones. Verificar que ande antes el ABMentidades::altaEleccion() (ṔOR AHORA ANDA)*/
	/* Para que tenga exito, no debe existir el archivos de arbol de eleccion */
	exito = true;
	for (int i=0;i<cantidadElecciones;i++)	if (exito) exito = ABMaux.altaEleccion(vecElecciones[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Elecciones (verificar que no exista el arbol de eleccion)" << endl << endl;
	  	return;
	}

    vector<Lista> vecListas;
    UtilidadesTests::cargarListas(vecListas,vecElecciones);
    int cantidadListas = vecListas.size();

	/* Guardo las listas. Verificar que ande antes el ABMentidades::altaLista() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no debe existir el archivos de arbol de lista */
	exito = true;
	for (int i=0;i<cantidadListas;i++)	if (exito) exito = ABMaux.altaLista(vecListas[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Listas (verificar que no exista el arbol de lista)" << endl << endl;
	  	return;
	}

    vector<Votante> vecVotantes;
    UtilidadesTests::cargarVotantes(vecVotantes,vecDistritos,vecElecciones);
    int cantidadVotantes = vecVotantes.size();

	/* Guardo los votantes. Verificar que ande antes el ABMentidades::altaVotante() (ṔOR AHORA ANDA)*/
	/* Para que tenga exito, no deben existir los archivos de hash de votante */
	exito = true;
	for (int i=0;i<cantidadVotantes;i++)	if (exito) exito = ABMaux.altaVotante(vecVotantes[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Votantes (verificar que no existan los hash de votante)" << endl << endl;
	  	return;
	}

	vector<Candidato> vecCandidatos;
	UtilidadesTests::cargarCandidatos(vecCandidatos,vecListas,vecVotantes);
	int cantidadCandidatos = vecCandidatos.size();

	for(int i=0;i<cantidadCandidatos;i++)	vecCandidatos[i].Imprimir();

	unsigned long int offset[cantidadCandidatos];

	for(int i=0;i<cantidadCandidatos;i++) {
		offset[i] = dataAccess.Guardar(vecCandidatos[i]);
		cout << "Offset de "<< vecCandidatos[i].getLista().getNombre() << "$" << vecCandidatos[i].getDNI() << ": " << offset[i] << endl;
	}
	cout << endl;

	for(int i=0;i<cantidadCandidatos;i++)     dataAccess.Leer(vecCandidatos[i],offset[cantidadCandidatos-1-i]);

	for(int i=0;i<cantidadCandidatos;i++)	vecCandidatos[i].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test Candidatos" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 6 administradores, se guardan en archivo y se recuperan en forma opuesta */
void TestPersistencias::TestAdministrador() {

	cout << endl << "********************************************************" << endl;
		cout << "              Comienzo Test Administradores" << endl;
		cout << "********************************************************" << endl << endl;

		vector<Administrador> vecAdministradores;

		UtilidadesTests::cargarAdministradores(vecAdministradores);
		int cantidadAdministradores = vecAdministradores.size();

		for(int i=0;i<cantidadAdministradores;i++)	vecAdministradores[i].Imprimir();

	    unsigned long int offset[cantidadAdministradores];

	    for(int i=0;i<cantidadAdministradores;i++) {
	        offset[i] = dataAccess.Guardar(vecAdministradores[i]);
	        cout << "Offset de "<< vecAdministradores[i].getUsuario() << ": " << offset[i] << endl;
	    }
	    cout << endl;

	    for(int i=0;i<cantidadAdministradores;i++)     dataAccess.Leer(vecAdministradores[i],offset[cantidadAdministradores-1-i]);

		for(int i=0;i<cantidadAdministradores;i++)	vecAdministradores[i].Imprimir();

		cout << endl << "********************************************************" << endl;
		cout << "                  Fin Test Administradores" << endl;
		cout << "********************************************************" << endl << endl;
}
