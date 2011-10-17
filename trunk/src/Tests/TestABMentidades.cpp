/*
 * TestABMentidades.cpp
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */



#include "TestABMentidades.h"

TestABMentidades::TestABMentidades() {

	this->clase_en_testeo="ABMentidades";

}

void TestABMentidades::comenzar(){

	this->tituloTest();

	this->testAltaCandidato();
	this->testAltaCargo();
	this->testAltaDistrito();
	this->testAltaEleccion();
	this->testAltaLista();
	this->testAltaVotante();

}


TestABMentidades::~TestABMentidades() {}

/* Se crean 6 Distritos, se guardan en archivo y hash y se recuperan en forma opuesta */
void TestABMentidades::testAltaDistrito() {
	cout << endl << "********************************************************" << endl;
	cout << "            Comienzo Alta Test Distritos" << endl;
	cout << "********************************************************" << endl << endl;

	vector<Distrito> vecDistritos;

	UtilidadesTests::cargarDistritos(vecDistritos);

	for(int i=0;i<6;i++)	vecDistritos[i].Imprimir();

    for(int i=0;i<6;i++) {
        if (ABMtest.altaDistrito(vecDistritos[i])) cout << "Alta "<<vecDistritos[i].getNombre()<<" correcta" << endl;
        else cout << "Alta "<<vecDistritos[i].getNombre()<<" incorrecta (ya existia)" << endl;
    }
    cout << endl;


    /* Pido que se impriman archivos de texto del hash para control */
    string regs((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_regs>"));
    string bloq_lib((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_bloq_lib>"));
    string tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_tabla>"));

    hash_extensible hash_distrito(regs,bloq_lib,tabla);
    hash_distrito.imprimir("./archivos/Tests/testABM_hash_distrito");

    regs = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_iddistrito_regs>"));
    bloq_lib = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_iddistrito_bloq_lib>"));
    tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_iddistrito_tabla>"));

    hash_extensible hash_iddistrito(regs,bloq_lib,tabla);
    hash_iddistrito.imprimir("./archivos/Tests/testABM_hash_iddistrito");

    /* Recupero los valores de distritos */
    // Debo guardar las claves para que no se cambien al cargar los registros
	string clave[6];
	for(int i=0;i<6;i++)	clave[i] = vecDistritos[i].getNombre();

    for(int i=0;i<6;i++)	this->ConsultaEntidadesTest.ObtenerRegistro(clave[5-i],vecDistritos[i]);

	for(int i=0;i<6;i++)	vecDistritos[i].Imprimir();


	cout << endl << "********************************************************" << endl;
	cout << "                Fin Test Alta Distritos" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 6 Cargos principales, con "i" cargos secundarios (i es indice de cargo).
 * Se guardan en archivo y hash y se recuperan en forma opuesta */
void TestABMentidades::testAltaCargo() {
	cout << endl << "********************************************************" << endl;
	cout << "            Comienzo Alta Test Cargos" << endl;
	cout << "********************************************************" << endl << endl;

	vector<Cargo> vecCargos;

	UtilidadesTests::cargarCargos(vecCargos);

	for(int i=0;i<6;i++)	vecCargos[i].Imprimir();

    for(int i=0;i<6;i++) {
        if (ABMtest.altaCargo(vecCargos[i])) cout << "Alta " << vecCargos[i].getCargoPrincipal() << " correcta" << endl;
        else cout << "Alta " << vecCargos[i].getCargoPrincipal() << " incorrecta (ya existia)" << endl;
    }
    cout << endl;


    /* Pido que se impriman archivos de texto del hash para control */
    string regs((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_cargo_regs>"));
    string bloq_lib((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_cargo_bloq_lib>"));
    string tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_cargo_tabla>"));

    hash_extensible hash_distrito(regs,bloq_lib,tabla);
    hash_distrito.imprimir("./archivos/Tests/testABM_hash_cargo");

    regs = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcargo_regs>"));
    bloq_lib = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcargo_bloq_lib>"));
    tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcargo_tabla>"));

    hash_extensible hash_iddistrito(regs,bloq_lib,tabla);
    hash_iddistrito.imprimir("./archivos/Tests/testABM_hash_idcargo");

    /* Recupero los valores de cargos */
    // Debo guardar las claves para que no se cambien al cargar los registros
    string clave[6];
	for(int i=0;i<6;i++)	clave[i] = vecCargos[i].getCargoPrincipal();

	for(int i=0;i<6;i++) this->ConsultaEntidadesTest.ObtenerRegistro(clave[5-i],vecCargos[i]);

	for(int i=0;i<6;i++)	vecCargos[i].Imprimir();


	cout << endl << "********************************************************" << endl;
	cout << "                Fin Test Alta Cargos" << endl;
	cout << "********************************************************" << endl << endl;
}


void TestABMentidades::testAltaEleccion() {

}


void TestABMentidades::testAltaVotante() {

}


void TestABMentidades::testAltaCandidato() {

}


void TestABMentidades::testAltaLista() {

}
