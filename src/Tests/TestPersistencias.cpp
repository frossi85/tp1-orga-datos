/*
 * TestPersistencias.cpp
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */

/*
 * Ya Agregue Este Test para que se ejecute con Tester
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

/* Se crean 6 Distritos, se guardan en archivo y se recuperan en forma opuesta*/
void TestPersistencias::TestDistrito() {
	cout << endl << "********************************************************" << endl;
	cout << "              Comienzo Test Distritos" << endl;
	cout << "********************************************************" << endl << endl;
	Distrito distrito1("Lanus");
    Distrito distrito2("Cordoba");
    Distrito distrito3("Santa Fe");
    Distrito distrito4("Pehuajo");
    Distrito distrito5("Olivos");
    Distrito distrito6("Springfield");

    distrito1.Imprimir();
    distrito2.Imprimir();
    distrito3.Imprimir();
    distrito4.Imprimir();
    distrito5.Imprimir();
    distrito6.Imprimir();

    unsigned long int offset1, offset2, offset3, offset4, offset5, offset6;

    offset1 = dataAccess.Guardar(distrito1);
    cout << "Offset de Lanus: " << offset1 << endl;
    offset2 = dataAccess.Guardar(distrito2);
    cout << "Offset de Cordoba: " << offset2 << endl;
    offset3 = dataAccess.Guardar(distrito3);
    cout << "Offset de Santa Fe: " << offset3 << endl;
    offset4 = dataAccess.Guardar(distrito4);
    cout << "Offset de Pehuajo: " << offset4 << endl;
    offset5 = dataAccess.Guardar(distrito5);
    cout << "Offset de Olivos: " << offset5 << endl;
    offset6 = dataAccess.Guardar(distrito6);
    cout << "Offset de Springfield: " << offset6 << endl << endl;

    dataAccess.Leer(distrito1,offset6);
    dataAccess.Leer(distrito2,offset5);
    dataAccess.Leer(distrito3,offset4);
    dataAccess.Leer(distrito4,offset3);
    dataAccess.Leer(distrito5,offset2);
    dataAccess.Leer(distrito6,offset1);

    distrito1.Imprimir();
    distrito2.Imprimir();
    distrito3.Imprimir();
    distrito4.Imprimir();
    distrito5.Imprimir();
    distrito6.Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test Distritos" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 6 Cargos principales, con "i" cargos secundarios (i es indice de cargo).
 * Se guardan en archivo y se recuperan en forma opuesta*/
void TestPersistencias::TestCargo() {

	cout << endl << "********************************************************" << endl;
	cout << "                Comienzo Test Cargos" << endl;
	cout << "********************************************************" << endl << endl;
	Cargo cargo1 ("Intendente Lanus");
	Cargo cargo2("Gobernador Cordoba");
	Cargo cargo3("Diputado Santa Fe");
	Cargo cargo4("Senador Pehuajo");
	Cargo cargo5("Ministro de Olivos");
	Cargo cargo6("Presidente de Springfield");

	cargo1.agregarCargoSecundario("Secretario Lanus");
	cargo2.agregarCargoSecundario("Vicegobernador Cordoba");
	cargo2.agregarCargoSecundario("Secretario Cordoba");
	cargo3.agregarCargoSecundario("Diputado segundo");
	cargo3.agregarCargoSecundario("Diputado tercero");
	cargo3.agregarCargoSecundario("Diputado cuarto");
	cargo4.agregarCargoSecundario("Senador segundo");
	cargo4.agregarCargoSecundario("Senador tercero");
	cargo4.agregarCargoSecundario("Senador cuarto");
	cargo4.agregarCargoSecundario("Senador quinto");
	cargo5.agregarCargoSecundario("Ministro segundo");
	cargo5.agregarCargoSecundario("Ministro tercero");
	cargo5.agregarCargoSecundario("Ministro cuarto");
	cargo5.agregarCargoSecundario("Ministro quinto");
	cargo5.agregarCargoSecundario("Ministro sexto");
	cargo6.agregarCargoSecundario("Vicepresidente Springfield");
	cargo6.agregarCargoSecundario("Ministro Springfield");
	cargo6.agregarCargoSecundario("Senador Springfield");
	cargo6.agregarCargoSecundario("Diputado Springfield");
	cargo6.agregarCargoSecundario("Gobernador Springfield");
	cargo6.agregarCargoSecundario("Intendente Springfield");

	cargo1.Imprimir();
	cargo2.Imprimir();
	cargo3.Imprimir();
	cargo4.Imprimir();
	cargo5.Imprimir();
	cargo6.Imprimir();

    unsigned long int offset1, offset2, offset3, offset4, offset5, offset6;

    offset1 = dataAccess.Guardar(cargo1);
    cout << "Offset de Lanus: " << offset1 << endl;
    offset2 = dataAccess.Guardar(cargo2);
    cout << "Offset de Cordoba: " << offset2 << endl;
    offset3 = dataAccess.Guardar(cargo3);
    cout << "Offset de Santa Fe: " << offset3 << endl;
    offset4 = dataAccess.Guardar(cargo4);
    cout << "Offset de Pehuajo: " << offset4 << endl;
    offset5 = dataAccess.Guardar(cargo5);
    cout << "Offset de Olivos: " << offset5 << endl;
    offset6 = dataAccess.Guardar(cargo6);
    cout << "Offset de Springfield: " << offset6 << endl << endl;

    dataAccess.Leer(cargo1,offset6);
    dataAccess.Leer(cargo2,offset5);
    dataAccess.Leer(cargo3,offset4);
    dataAccess.Leer(cargo4,offset3);
    dataAccess.Leer(cargo5,offset2);
    dataAccess.Leer(cargo6,offset1);

    cargo1.Imprimir();
    cargo2.Imprimir();
    cargo3.Imprimir();
    cargo4.Imprimir();
    cargo5.Imprimir();
    cargo6.Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                    Fin Test Cargos" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 6 Cargos principales, con "i" cargos secundarios (i es indice de cargo).
 * Se guardan en archivo y se recuperan en forma opuesta*/
void TestPersistencias::TestEleccion() {
/*
	cout << endl << "********************************************************" << endl;
	cout << "                Comienzo Test Eleccion" << endl;
	cout << "********************************************************" << endl << endl;

	unsigned long int offset1, offset2, offset3, offset4, offset5, offset6;

	Distrito distrito1("Lanus");
    Distrito distrito2("Cordoba");
    Distrito distrito3("Santa Fe");
    Distrito distrito4("Pehuajo");
    Distrito distrito5("Olivos");
    Distrito distrito6("Springfield");

    /* Guardo los distritos y los agrego al hash
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_tabla>"));
	hash_extensible hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregar(distrito.getNombre(),0);
	RegistroIndice *returnReg = hash->buscar(&aAgregar);
	if (returnReg != NULL) return false;					// Ya existia en el hash, no se agrega
	distrito.setId(ManejoIDs::obtenerIDnuevo("Distrito"));
	this->dataAccess.Guardar(distrito);




	delete this->hash;
    hash_extensible *hash = new hash_extensible()
    offset1 = dataAccess.Guardar(distrito1);
    offset2 = dataAccess.Guardar(distrito2);
    offset3 = dataAccess.Guardar(distrito3);
    offset4 = dataAccess.Guardar(distrito4);
    offset5 = dataAccess.Guardar(distrito5);
    offset6 = dataAccess.Guardar(distrito6);;

	Cargo cargo1 ("Intendente Lanus");
	Cargo cargo2("Gobernador Cordoba");
	Cargo cargo3("Diputado Santa Fe");
	Cargo cargo4("Senador Pehuajo");
	Cargo cargo5("Ministro de Olivos");
	Cargo cargo6("Presidente de Springfield");

	cargo1.agregarCargoSecundario("Secretario Lanus");
	cargo2.agregarCargoSecundario("Vicegobernador Cordoba");
	cargo2.agregarCargoSecundario("Secretario Cordoba");
	cargo3.agregarCargoSecundario("Diputado segundo");
	cargo3.agregarCargoSecundario("Diputado tercero");
	cargo3.agregarCargoSecundario("Diputado cuarto");
	cargo4.agregarCargoSecundario("Senador segundo");
	cargo4.agregarCargoSecundario("Senador tercero");
	cargo4.agregarCargoSecundario("Senador cuarto");
	cargo4.agregarCargoSecundario("Senador quinto");
	cargo5.agregarCargoSecundario("Ministro segundo");
	cargo5.agregarCargoSecundario("Ministro tercero");
	cargo5.agregarCargoSecundario("Ministro cuarto");
	cargo5.agregarCargoSecundario("Ministro quinto");
	cargo5.agregarCargoSecundario("Ministro sexto");
	cargo6.agregarCargoSecundario("Vicepresidente Springfield");
	cargo6.agregarCargoSecundario("Ministro Springfield");
	cargo6.agregarCargoSecundario("Senador Springfield");
	cargo6.agregarCargoSecundario("Diputado Springfield");
	cargo6.agregarCargoSecundario("Gobernador Springfield");
	cargo6.agregarCargoSecundario("Intendente Springfield");

	Eleccion eleccion1("01/01/2001",cargo1,distrito1);
	Eleccion eleccion2("02/02/2002",cargo2,distrito2);
	Eleccion eleccion3("03/03/2003",cargo3,distrito3);
	Eleccion eleccion4("04/04/2004",cargo4,distrito4);
	Eleccion eleccion5("05/05/2005",cargo5,distrito5);
	Eleccion eleccion6("06/06/2006",cargo6,distrito6);

	eleccion2.agregarDistrito(distrito1);
	eleccion3.agregarDistrito(distrito2);
	eleccion3.agregarDistrito(distrito1);
	eleccion4.agregarDistrito(distrito3);
	eleccion4.agregarDistrito(distrito2);
	eleccion4.agregarDistrito(distrito1);
	eleccion5.agregarDistrito(distrito4);
	eleccion5.agregarDistrito(distrito3);
	eleccion5.agregarDistrito(distrito2);
	eleccion5.agregarDistrito(distrito1);
	eleccion6.agregarDistrito(distrito5);
	eleccion6.agregarDistrito(distrito4);
	eleccion6.agregarDistrito(distrito3);
	eleccion6.agregarDistrito(distrito2);
	eleccion6.agregarDistrito(distrito1);



    offset1 = dataAccess.Guardar(eleccion1);
    cout << "Offset de Lanus: " << offset1 << endl;
    offset2 = dataAccess.Guardar(eleccion2);
    cout << "Offset de Cordoba: " << offset2 << endl;
    offset3 = dataAccess.Guardar(eleccion3);
    cout << "Offset de Santa Fe: " << offset3 << endl;
    offset4 = dataAccess.Guardar(eleccion4);
    cout << "Offset de Pehuajo: " << offset4 << endl;
    offset5 = dataAccess.Guardar(eleccion5);
    cout << "Offset de Olivos: " << offset5 << endl;
    offset6 = dataAccess.Guardar(eleccion6);
    cout << "Offset de Springfield: " << offset6 << endl << endl;

    dataAccess.Leer(cargo1,offset6);
    dataAccess.Leer(cargo2,offset5);
    dataAccess.Leer(cargo3,offset4);
    dataAccess.Leer(cargo4,offset3);
    dataAccess.Leer(cargo5,offset2);
    dataAccess.Leer(cargo6,offset1);

    cargo1.Imprimir();
    cargo2.Imprimir();
    cargo3.Imprimir();
    cargo4.Imprimir();
    cargo5.Imprimir();
    cargo6.Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                    Fin Test Eleccion" << endl;
	cout << "********************************************************" << endl << endl; */
}
