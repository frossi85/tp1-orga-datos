/*
 * TestABMentidades.cpp
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */

#include "TestABMentidades.h"

TestABMentidades::TestABMentidades() {}


TestABMentidades::~TestABMentidades() {}


void TestABMentidades::testAltaDistrito() {
	cout << endl << "********************************************************" << endl;
	cout << "            Comienzo Alta Test Distritos" << endl;
	cout << "********************************************************" << endl << endl;

	string clave1 = "Lanus";
	string clave2 = "Cordoba";
	string clave3 = "Santa Fe";
	string clave4 = "Pehuajo";
	string clave5 = "Olivos";
	string clave6 = "Springfield";

	Distrito distrito1(clave1);
    Distrito distrito2(clave2);
    Distrito distrito3(clave3);
    Distrito distrito4(clave4);
    Distrito distrito5(clave5);
    Distrito distrito6(clave6);

    distrito1.Imprimir();
    distrito2.Imprimir();
    distrito3.Imprimir();
    distrito4.Imprimir();
    distrito5.Imprimir();
    distrito6.Imprimir();

    if (ABMtest.altaDistrito(distrito1)) cout << "\nAlta "<<clave1<<" correcta" << endl;
    else cout << "\nAlta "<<clave1<<" incorrecta" << endl;

    if (ABMtest.altaDistrito(distrito2)) cout << "\nAlta "<<clave2<<" correcta" << endl;
    else cout << "\nAlta "<<clave2<<" incorrecta" << endl;

    if (ABMtest.altaDistrito(distrito3)) cout << "\nAlta "<<clave3<<" correcta" << endl;
    else cout << "\nAlta "<<clave3<<" incorrecta" << endl;

    if (ABMtest.altaDistrito(distrito4)) cout << "\nAlta "<<clave4<<" correcta" << endl;
    else cout << "\nAlta "<<clave4<<" incorrecta" << endl;

    if (ABMtest.altaDistrito(distrito5)) cout << "\nAlta "<<clave5<<" correcta" << endl;
    else cout << "\nAlta "<<clave5<<" incorrecta" << endl;

    if (ABMtest.altaDistrito(distrito6)) cout << "\nAlta "<<clave6<<" correcta" << endl;
    else cout << "\nAlta "<<clave6<<" incorrecta" << endl;

    this->ConsultaEntidadesTest.ObtenerRegistro(clave6,distrito1);
    this->ConsultaEntidadesTest.ObtenerRegistro(clave5,distrito2);
    this->ConsultaEntidadesTest.ObtenerRegistro(clave4,distrito3);
    this->ConsultaEntidadesTest.ObtenerRegistro(clave3,distrito4);
    this->ConsultaEntidadesTest.ObtenerRegistro(clave2,distrito5);
    this->ConsultaEntidadesTest.ObtenerRegistro(clave1,distrito6);

    distrito1.Imprimir();
    distrito2.Imprimir();
    distrito3.Imprimir();
    distrito4.Imprimir();
    distrito5.Imprimir();
    distrito6.Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                Fin Test Alta Distritos" << endl;
	cout << "********************************************************" << endl << endl;
}


void TestABMentidades::testAltaCargo() {

}


void TestABMentidades::testAltaEleccion() {

}


void TestABMentidades::testAltaVotante() {

}


void TestABMentidades::testAltaCandidato() {

}


void TestABMentidades::testAltaLista() {

}
