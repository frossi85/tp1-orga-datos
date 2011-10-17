/*
 * TestPersistencias.cpp
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */


#include "TestPersistencias.h"

TestPersistencias::TestPersistencias() {
	this->clase_en_testeo="Persistencias";
}

void TestPersistencias::comenzar(){

	this->tituloTest();

	this->TestCargo();

	this->TestDistrito();

	this->TestEleccion();

}

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

	 unsigned long int offset0, offset1, offset2, offset3, offset4, offset5;

	 vector<Distrito> vecDistritos;
	 vector<Cargo> vecCargos;

	 UtilidadesTests::cargarDistritos(vecDistritos);
	 UtilidadesTests::cargarCargos(vecCargos);


    /* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() */
    ABMentidades ABMaux;
    bool exito = ABMaux.altaDistrito(vecDistritos[0]);
    if (exito) exito = ABMaux.altaDistrito(vecDistritos[1]);
    if (exito) exito = ABMaux.altaDistrito(vecDistritos[2]);
    if (exito) exito = ABMaux.altaDistrito(vecDistritos[3]);
    if (exito) exito = ABMaux.altaDistrito(vecDistritos[4]);
    if (exito) exito = ABMaux.altaDistrito(vecDistritos[5]);
    if (!exito) {
    	cout << "Fallo la carga de Distritos" << endl << endl;
    	return;
    }

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() */
	exito = ABMaux.altaCargo(vecCargos[0]);
    if (exito) exito = ABMaux.altaCargo(vecCargos[1]);
    if (exito) exito = ABMaux.altaCargo(vecCargos[2]);
    if (exito) exito = ABMaux.altaCargo(vecCargos[3]);
    if (exito) exito = ABMaux.altaCargo(vecCargos[4]);
    if (exito) exito = ABMaux.altaCargo(vecCargos[5]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos" << endl << endl;
    	return;
    }

	vector<Eleccion> vecElecciones;

	UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);

	vecElecciones[0].Imprimir();
	vecElecciones[1].Imprimir();
	vecElecciones[2].Imprimir();
	vecElecciones[3].Imprimir();
	vecElecciones[4].Imprimir();
	vecElecciones[5].Imprimir();

    offset0 = dataAccess.Guardar(vecElecciones[0]);
    cout << "Offset de 01/01/2001: " << offset0 << endl;
    offset1 = dataAccess.Guardar(vecElecciones[1]);
    cout << "Offset de 02/02/2002: " << offset1 << endl;
    offset2 = dataAccess.Guardar(vecElecciones[2]);
    cout << "Offset de 03/03/2003: " << offset2 << endl;
    offset3 = dataAccess.Guardar(vecElecciones[3]);
    cout << "Offset de 04/04/2004: " << offset3 << endl;
    offset4 = dataAccess.Guardar(vecElecciones[4]);
    cout << "Offset de 05/05/2005: " << offset4 << endl;
    offset5 = dataAccess.Guardar(vecElecciones[5]);
    cout << "Offset de 06/06/2006: " << offset5 << endl << endl;

    dataAccess.Leer(vecElecciones[0],offset5);
    dataAccess.Leer(vecElecciones[1],offset4);
    dataAccess.Leer(vecElecciones[2],offset3);
    dataAccess.Leer(vecElecciones[3],offset2);
    dataAccess.Leer(vecElecciones[4],offset1);
    dataAccess.Leer(vecElecciones[5],offset0);

	vecElecciones[0].Imprimir();
	vecElecciones[1].Imprimir();
	vecElecciones[2].Imprimir();
	vecElecciones[3].Imprimir();
	vecElecciones[4].Imprimir();
	vecElecciones[5].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                    Fin Test Eleccion" << endl;
	cout << "********************************************************" << endl << endl;
}
