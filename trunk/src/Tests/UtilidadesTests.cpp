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
    Lista lista1("FPV",vecElecciones[0]);
    Lista lista2("UDESO",vecElecciones[0]);
    Lista lista3("UDESO",vecElecciones[1]);
    Lista lista4("FAP",vecElecciones[0]);
    Lista lista5("FAP",vecElecciones[1]);
    Lista lista6("FAP",vecElecciones[2]);
    Lista lista7("PRO",vecElecciones[0]);
    Lista lista8("PRO",vecElecciones[1]);
    Lista lista9("PRO",vecElecciones[2]);
    Lista lista10("PRO",vecElecciones[3]);
    Lista lista11("Coalicion Civica",vecElecciones[0]);
    Lista lista12("Coalicion Civica",vecElecciones[1]);
    Lista lista13("Coalicion Civica",vecElecciones[2]);
    Lista lista14("Coalicion Civica",vecElecciones[3]);
    Lista lista15("Coalicion Civica",vecElecciones[4]);
    Lista lista16("Frente de Izquierda", vecElecciones[0]);
    Lista lista17("Frente de Izquierda", vecElecciones[1]);
    Lista lista18("Frente de Izquierda", vecElecciones[2]);
    Lista lista19("Frente de Izquierda", vecElecciones[3]);
    Lista lista20("Frente de Izquierda", vecElecciones[4]);
    Lista lista21("Frente de Izquierda", vecElecciones[5]);

    vecListas.push_back(lista1);
    vecListas.push_back(lista2);
    vecListas.push_back(lista3);
    vecListas.push_back(lista4);
    vecListas.push_back(lista5);
    vecListas.push_back(lista6);
    vecListas.push_back(lista7);
    vecListas.push_back(lista8);
    vecListas.push_back(lista9);
    vecListas.push_back(lista10);
    vecListas.push_back(lista11);
    vecListas.push_back(lista12);
    vecListas.push_back(lista13);
    vecListas.push_back(lista14);
    vecListas.push_back(lista15);
    vecListas.push_back(lista16);
    vecListas.push_back(lista17);
    vecListas.push_back(lista18);
    vecListas.push_back(lista19);
    vecListas.push_back(lista20);
    vecListas.push_back(lista21);

    return;
}


void UtilidadesTests::cargarVotantes(vector<Votante> &vecVotantes, vector<Distrito> &vecDistritos, vector<Eleccion> &vecElecciones) {

	/* Distritos:
	 * i=
	 * 0: Lanus
	 * 1: Cordoba
	 * 2: Santa Fe
	 * 3: Pehuajo
	 * 4: Olivos
	 * 5: Springfield
	 *
	 * Distritos de las Elecciones:
	 * i=
	 * 0: Lanus
	 * 1: Cordoba, Lanus
	 * 2: Santa Fe, Cordoba, Lanus
	 * 3: Pehuajo, Santa Fe, Cordoba, Lanus
	 * 4: Olivos, Pehuajo, Santa Fe, Cordoba, Lanus
	 * 5: Springfield, Olivos, Pehuajo, Santa Fe, Cordoba, Lanus
	 */

	if (!vecVotantes.empty()) vecVotantes.clear();
	Votante votante1(5000000,"Lenny Leonard","carl","Saraza 601",vecDistritos[1]);
	Votante votante2(10000000,"Carl Carlson","lenny","Sorozo 101",vecDistritos[5]);
	Votante votante3(15000000,"Homero Simpson","cerveza","Avenida Evergreen 555",vecDistritos[2]);
	Votante votante4(20000000,"Bart Simpson","patineta","Avenida Evergreen 555",vecDistritos[3]);
	Votante votante5(25000000,"Barney Gomez","cerveza","Linyera 1402",vecDistritos[4]);
	Votante votante6(30000000,"Moe Szyslack","escopeta","Sargento Cabral 740",vecDistritos[2]);
	Votante votante7(35000000,"Ned Flanders","jesus","Avenida Evergreen 557",vecDistritos[5]);
	Votante votante8(40000000,"Charles Montgomery Burns","money","Paseo Lucrativo 55",vecDistritos[0]);
	Votante votante9(45000000,"Tony Fatso","spaghetti","Little Italy 940",vecDistritos[4]);

	/* Elecciones de cada Votante:
	 * i=
	 * 0: Lenny: Cordoba. Vota en 02/02/2002 - 03/03/2003 - 04/04/2004 - 05/05/2005 - 06/06/2006
	 * 1: Carl: Springfield. Vota en 06/06/2006
	 * 2: Homero: Santa Fe. Vota en 03/03/2003 - 04/04/2004 - 05/05/2005 - 06/06/2006
	 * 3: Bart: Pehuajo. Vota en 04/04/2004 - 05/05/2005 - 06/06/2006
	 * 4: Barney: Olivos. Vota en 05/05/2005 - 06/06/2006
	 * 5: Moe: Santa Fe. Vota en 03/03/2003 - 04/04/2004 - 05/05/2005 - 06/06/2006
	 * 6: Ned: Springfield. Vota en 06/06/2006
	 * 7: Charles: Cordoba. Vota en 01/01/2001 - 02/02/2002 - 03/03/2003 - 04/04/2004 - 05/05/2005 - 06/06/2006
	 * 8: Tony: Olivos. Vota en 05/05/2005 - 06/06/2006
	 */

	votante1.agregarEleccion(vecElecciones[1]);
	votante1.agregarEleccion(vecElecciones[2]);
	votante1.agregarEleccion(vecElecciones[3]);
	votante1.agregarEleccion(vecElecciones[4]);
	votante1.agregarEleccion(vecElecciones[5]);
	votante2.agregarEleccion(vecElecciones[5]);
	votante3.agregarEleccion(vecElecciones[2]);
	votante3.agregarEleccion(vecElecciones[3]);
	votante3.agregarEleccion(vecElecciones[4]);
	votante3.agregarEleccion(vecElecciones[5]);
	votante4.agregarEleccion(vecElecciones[3]);
	votante4.agregarEleccion(vecElecciones[4]);
	votante4.agregarEleccion(vecElecciones[5]);
	votante5.agregarEleccion(vecElecciones[4]);
	votante5.agregarEleccion(vecElecciones[5]);
	votante6.agregarEleccion(vecElecciones[2]);
	votante6.agregarEleccion(vecElecciones[3]);
	votante6.agregarEleccion(vecElecciones[4]);
	votante6.agregarEleccion(vecElecciones[5]);
	votante7.agregarEleccion(vecElecciones[5]);
	votante8.agregarEleccion(vecElecciones[0]);
	votante8.agregarEleccion(vecElecciones[1]);
	votante8.agregarEleccion(vecElecciones[2]);
	votante8.agregarEleccion(vecElecciones[3]);
	votante8.agregarEleccion(vecElecciones[4]);
	votante8.agregarEleccion(vecElecciones[5]);
	votante9.agregarEleccion(vecElecciones[4]);
	votante9.agregarEleccion(vecElecciones[5]);

	vecVotantes.push_back(votante1);
	vecVotantes.push_back(votante2);
	vecVotantes.push_back(votante3);
	vecVotantes.push_back(votante4);
	vecVotantes.push_back(votante5);
	vecVotantes.push_back(votante6);
	vecVotantes.push_back(votante7);
	vecVotantes.push_back(votante8);
	vecVotantes.push_back(votante9);

	return;
}


void UtilidadesTests::cargarCandidatos(vector<Candidato> &vecCandidatos, vector<Lista> &vecListas, vector<Votante> &vecVotantes) {
	if (!vecCandidatos.empty()) vecCandidatos.clear();
	Candidato candidato1(vecVotantes[0],vecListas[0]);
	Candidato candidato2(vecVotantes[1],vecListas[1]);
	Candidato candidato3(vecVotantes[2],vecListas[3]);
	Candidato candidato4(vecVotantes[3],vecListas[6]);
	Candidato candidato5(vecVotantes[4],vecListas[10]);
	Candidato candidato6(vecVotantes[5],vecListas[15]);

	vecCandidatos.push_back(candidato1);
	vecCandidatos.push_back(candidato2);
	vecCandidatos.push_back(candidato3);
	vecCandidatos.push_back(candidato4);
	vecCandidatos.push_back(candidato5);
	vecCandidatos.push_back(candidato6);

	return;
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
