/*
 * UtilidadesTests.cpp
 *
 *  Created on: 14/10/2011
 *      Author: martin
 */

#include "UtilidadesTests.h"

UtilidadesTests::UtilidadesTests() {}

UtilidadesTests::~UtilidadesTests() {}


void UtilidadesTests::cargarDistritos(vector<Distrito> &vecDistritos) {
	if (!vecDistritos.empty()) vecDistritos.clear();
	Distrito distrito1("Lanus");
    Distrito distrito2("Cordoba");
    Distrito distrito3("Santa Fe");
    Distrito distrito4("Pehuajo");
    Distrito distrito5("Olivos");
    Distrito distrito6("Springfield");
    vecDistritos.push_back(distrito1);
    vecDistritos.push_back(distrito2);
    vecDistritos.push_back(distrito3);
    vecDistritos.push_back(distrito4);
    vecDistritos.push_back(distrito5);
    vecDistritos.push_back(distrito6);
    return;
}


void UtilidadesTests::cargarCargos(vector<Cargo> &vecCargos) {
	if (!vecCargos.empty()) vecCargos.clear();
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
	vecCargos.push_back(cargo1);
	vecCargos.push_back(cargo2);
	vecCargos.push_back(cargo3);
	vecCargos.push_back(cargo4);
	vecCargos.push_back(cargo5);
	vecCargos.push_back(cargo6);
	return;
}


void UtilidadesTests::cargarElecciones(vector<Eleccion> &vecElecciones, vector<Cargo> &vecCargos, vector<Distrito> &vecDistritos) {
	if (!vecElecciones.empty()) vecElecciones.clear();
	Eleccion eleccion1("01/01/2001",vecCargos[0],vecDistritos[0]);
	Eleccion eleccion2("02/02/2002",vecCargos[1],vecDistritos[1]);
	Eleccion eleccion3("03/03/2003",vecCargos[2],vecDistritos[2]);
	Eleccion eleccion4("04/04/2004",vecCargos[3],vecDistritos[3]);
	Eleccion eleccion5("05/05/2005",vecCargos[4],vecDistritos[4]);
	Eleccion eleccion6("06/06/2006",vecCargos[5],vecDistritos[5]);
	eleccion2.agregarDistrito(vecDistritos[0]);
	eleccion3.agregarDistrito(vecDistritos[1]);
	eleccion3.agregarDistrito(vecDistritos[0]);
	eleccion4.agregarDistrito(vecDistritos[2]);
	eleccion4.agregarDistrito(vecDistritos[1]);
	eleccion4.agregarDistrito(vecDistritos[0]);
	eleccion5.agregarDistrito(vecDistritos[3]);
	eleccion5.agregarDistrito(vecDistritos[2]);
	eleccion5.agregarDistrito(vecDistritos[1]);
	eleccion5.agregarDistrito(vecDistritos[0]);
	eleccion6.agregarDistrito(vecDistritos[4]);
	eleccion6.agregarDistrito(vecDistritos[3]);
	eleccion6.agregarDistrito(vecDistritos[2]);
	eleccion6.agregarDistrito(vecDistritos[1]);
	eleccion6.agregarDistrito(vecDistritos[0]);
	vecElecciones.push_back(eleccion1);
	vecElecciones.push_back(eleccion2);
	vecElecciones.push_back(eleccion3);
	vecElecciones.push_back(eleccion4);
	vecElecciones.push_back(eleccion5);
	vecElecciones.push_back(eleccion6);
	return;
}


void UtilidadesTests::cargarListas(vector<Lista> &vecListas, vector<Eleccion> &vecElecciones) {
    if (!vecListas.empty()) vecListas.clear();
    Lista lista1("FPV 2011",vecElecciones[0]);
    Lista lista2("UDESO 2011",vecElecciones[0]);
    Lista lista3("FAP 2011",vecElecciones[0]);
    Lista lista4("PRO 2009",vecElecciones[1]);
    Lista lista5("Coalicion Civica 2009",vecElecciones[1]);
    Lista lista6("Frente de Izquierda 2007", vecElecciones[2]);

    vecListas.push_back(lista1);
    vecListas.push_back(lista2);
    vecListas.push_back(lista3);
    vecListas.push_back(lista4);
    vecListas.push_back(lista5);
    vecListas.push_back(lista6);

    return;
}


void UtilidadesTests::cargarVotantes(vector<Votante> &vecVotantes) {

}


void UtilidadesTests::cargarCandidatos(vector<Candidato> &vecCandidatos) {

}

void UtilidadesTests::cargarConteos(vector<Conteo> &vecConteos, vector<Lista> &vecListas, vector<Distrito> &vecDistritos, vector<Eleccion> &vecElecciones){

        if (!vecConteos.empty()) vecConteos.clear();
	Conteo conteo1(vecListas[0], vecDistritos[0]);
	Conteo conteo2(vecListas[1], vecDistritos[1]);
	Conteo conteo3(vecListas[2], vecDistritos[2]);
	Conteo conteo4(vecListas[3], vecDistritos[3]);
	Conteo conteo5(vecListas[4], vecDistritos[4]);
	Conteo conteo6(vecListas[5], vecDistritos[5]);

	vecConteos.push_back(conteo1);
	vecConteos.push_back(conteo2);
        vecConteos.push_back(conteo3);
        vecConteos.push_back(conteo4);
        vecConteos.push_back(conteo5);
        vecConteos.push_back(conteo6);

	return;
}
