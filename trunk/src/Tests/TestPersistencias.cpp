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

	for(int i=0;i<6;i++)	vecDistritos[i].Imprimir();

    unsigned long int offset[6];

    for(int i=0;i<6;i++) {
        offset[i] = dataAccess.Guardar(vecDistritos[i]);
        cout << "Offset de "<< vecDistritos[i].getNombre() << ": " << offset[i] << endl;
    }
    cout << endl;

    for(int i=0;i<6;i++)     dataAccess.Leer(vecDistritos[i],offset[5-i]);

	for(int i=0;i<6;i++)	vecDistritos[i].Imprimir();

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

	for(int i=0;i<6;i++)	vecCargos[i].Imprimir();

    unsigned long int offset[6];

    for(int i=0;i<6;i++) {
        offset[i] = dataAccess.Guardar(vecCargos[i]);
        cout << "Offset de "<< vecCargos[i].getCargoPrincipal() << ": " << offset[i] << endl;
    }
    cout << endl;

    for(int i=0;i<6;i++)     dataAccess.Leer(vecCargos[i],offset[5-i]);

	for(int i=0;i<6;i++)	vecCargos[i].Imprimir();

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


    /* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
    ABMentidades ABMaux;
    bool exito = true;
    for (int i=0;i<6;i++)	if (exito) exito = ABMaux.altaDistrito(vecDistritos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Distritos (verificar que no exitan los hash de distrito)" << endl << endl;
    	return;
    }

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = ABMaux.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no exitan los hash de cargo)" << endl << endl;
    	return;
    }

	vector<Eleccion> vecElecciones;

	UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);

	for(int i=0;i<6;i++) {
		vecElecciones[i].Imprimir();
		vecElecciones[i].ImprimirDistritos();
	}

	for(int i=0;i<6;i++) {
		offset[i] = dataAccess.Guardar(vecElecciones[i]);
		cout << "Offset de " << vecElecciones[i].getFecha() << ": " << offset[i] << endl;
	}
	cout << endl;

    for(int i=0;i<6;i++)	dataAccess.Leer(vecElecciones[i],offset[5-i]);

	for(int i=0;i<6;i++) {
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

	vector<Cargo> vecCargos;
	UtilidadesTests::cargarCargos(vecCargos);

	/* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
	ABMentidades ABMaux;
	bool exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = ABMaux.altaDistrito(vecDistritos[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Distritos (verificar que no exitan los hash de distrito)" << endl << endl;
	  	return;
	}

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = ABMaux.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no exitan los hash de cargo)" << endl << endl;
    	return;
    }

    vector<Eleccion> vecElecciones;
    UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);

	/* Guardo las elecciones. Verificar que ande antes el ABMentidades::altaEleccion() */
	/* Para que tenga exito, no deben existir los archivos de hash de eleccion */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = ABMaux.altaEleccion(vecElecciones[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Elecciones (verificar que no exitan los hash de eleccion)" << endl << endl;
	  	return;
	}

    vector<Votante> vecVotantes;
    UtilidadesTests::cargarVotantes(vecVotantes,vecDistritos,vecElecciones);

	for(int i=0;i<9;i++)	vecVotantes[i].Imprimir();

	unsigned long int offset[9];

	for(int i=0;i<9;i++) {
        offset[i] = dataAccess.Guardar(vecVotantes[i]);
        cout << "Offset de "<< vecVotantes[i].getDNI() << ": " << offset[i] << endl;
    }
    cout << endl;

    for(int i=0;i<9;i++)     dataAccess.Leer(vecVotantes[i],offset[8-i]);

	for(int i=0;i<9;i++)	vecVotantes[i].Imprimir();

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

	vector<Cargo> vecCargos;
	UtilidadesTests::cargarCargos(vecCargos);

	/* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
	ABMentidades ABMaux;
	bool exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = ABMaux.altaDistrito(vecDistritos[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Distritos (verificar que no exitan los hash de distrito)" << endl << endl;
	  	return;
	}

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = ABMaux.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no exitan los hash de cargo)" << endl << endl;
    	return;
    }

    vector<Eleccion> vecElecciones;
    UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);

	/* Guardo las elecciones. Verificar que ande antes el ABMentidades::altaEleccion() */
	/* Para que tenga exito, no deben existir los archivos de hash de eleccion */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = ABMaux.altaEleccion(vecElecciones[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Elecciones (verificar que no exitan los hash de eleccion)" << endl << endl;
	  	return;
	}

    vector<Lista> vecListas;
    UtilidadesTests::cargarListas(vecListas,vecElecciones);

	for(int i=0;i<21;i++)	vecListas[i].Imprimir();

	unsigned long int offset[21];

	for(int i=0;i<21;i++) {
        offset[i] = dataAccess.Guardar(vecListas[i]);
        cout << "Offset de "<< vecListas[i].getNombre() << "$" << vecListas[i].getEleccion().getFecha() << ": " << offset[i] << endl;
    }
    cout << endl;

    for(int i=0;i<21;i++)     dataAccess.Leer(vecListas[i],offset[20-i]);

	for(int i=0;i<21;i++)	vecListas[i].Imprimir();

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

	vector<Cargo> vecCargos;
	UtilidadesTests::cargarCargos(vecCargos);

	/* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
	ABMentidades ABMaux;
	bool exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = ABMaux.altaDistrito(vecDistritos[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Distritos (verificar que no exitan los hash de distrito)" << endl << endl;
	  	return;
	}

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = ABMaux.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no exitan los hash de cargo)" << endl << endl;
    	return;
    }

    vector<Eleccion> vecElecciones;
    UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);

	/* Guardo las elecciones. Verificar que ande antes el ABMentidades::altaEleccion() */
	/* Para que tenga exito, no deben existir los archivos de hash de eleccion */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = ABMaux.altaEleccion(vecElecciones[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Elecciones (verificar que no exitan los hash de eleccion)" << endl << endl;
	  	return;
	}

    vector<Lista> vecListas;
    UtilidadesTests::cargarListas(vecListas,vecElecciones);

	/* Guardo las listas. Verificar que ande antes el ABMentidades::altaLista() */
	/* Para que tenga exito, no deben existir los archivos de hash de lista */
	exito = true;
	for (int i=0;i<21;i++)	if (exito) exito = ABMaux.altaLista(vecListas[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Listas (verificar que no exitan los hash de lista)" << endl << endl;
	  	return;
	}

    vector<Votante> vecVotantes;
    UtilidadesTests::cargarVotantes(vecVotantes,vecDistritos,vecElecciones);

	/* Guardo los votantes. Verificar que ande antes el ABMentidades::altaVotante() */
	/* Para que tenga exito, no deben existir los archivos de hash de votante */
	exito = true;
	for (int i=0;i<9;i++)	if (exito) exito = ABMaux.altaVotante(vecVotantes[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Votantes (verificar que no exitan los hash de votante)" << endl << endl;
	  	return;
	}

	vector<Candidato> vecCandidatos;
	UtilidadesTests::cargarCandidatos(vecCandidatos,vecListas,vecVotantes);

	for(int i=0;i<6;i++)	vecCandidatos[i].Imprimir();

	unsigned long int offset[6];

	for(int i=0;i<6;i++) {
		offset[i] = dataAccess.Guardar(vecCandidatos[i]);
		cout << "Offset de "<< vecCandidatos[i].getLista().getNombre() << "$" << vecCandidatos[i].getDNI() << ": " << offset[i] << endl;
	}
	cout << endl;

	for(int i=0;i<6;i++)     dataAccess.Leer(vecCandidatos[i],offset[5-i]);

	for(int i=0;i<6;i++)	vecCandidatos[i].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test Candidatos" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 6 Conteos, se guardan en archivo y se recuperan en forma opuesta */
void TestPersistencias::TestConteo() {

	cout << endl << "********************************************************" << endl;
	cout << "              Comienzo Test Conteo" << endl;
	cout << "********************************************************" << endl << endl;

        vector<Cargo> vecCargos;
        UtilidadesTests::cargarCargos(vecCargos);

        vector<Distrito> vecDistritos;
        UtilidadesTests::cargarDistritos(vecDistritos);

        vector<Eleccion> vecElecciones;
        UtilidadesTests::cargarElecciones(vecElecciones, vecCargos, vecDistritos);

        vector<Lista> vecListas;
        UtilidadesTests::cargarListas(vecListas, vecElecciones);


	vector<Conteo> vecConteos;
	UtilidadesTests::cargarConteos(vecConteos, vecListas, vecDistritos, vecElecciones);

	for(int i = 0; i < 6; i++)  vecConteos[i].Imprimir();

        unsigned long int offset[6];

        for(int i = 0; i < 6; i++){
            offset[i] = dataAccess.Guardar(vecConteos[i]);
            cout << "Offset de conteo nro. " << i << ": " << offset[i] << endl;
        }
        cout << endl;

        for(int i = 0; i < 6; i++) dataAccess.Leer(vecConteos[i],offset[5-i]);

	for(int i = 0; i < 6; i++) vecConteos[i].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test Conteo" << endl;
	cout << "********************************************************" << endl << endl;
}
