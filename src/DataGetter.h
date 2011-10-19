/*
 * DataGetter.h
 *
 *  Created on: 13/10/2011
 *      Author: administrador
 */

#ifndef DATAGETTER_H_
#define DATAGETTER_H_

#include <vector>
#include "Votante.h"
#include "Eleccion.h"
#include "Lista.h"
#include "Distrito.h"
#include "Conteo.h"

class DataGetter {
public:
	DataGetter();
	virtual ~DataGetter();

	static vector<Lista* > getListas_por_Eleccion(Eleccion& eleccion);

	//Devuelve el puntero a un votante
	//Devuelve NULL si no encontro al votante con ese dni
	//Falta Implementar
	static Votante* getVotante(const string dni);


	static vector<Eleccion *> getElecciones_por_Votante(Votante &votante);


	//Metodos para Informes

	static vector<Conteo *> getConteosPorDistrito(Distrito& distrito);

	static vector<Conteo *> getConteosPorLista(Lista& lista);

	static vector<Conteo *> getConteosPorEleccion(Eleccion& eleccion);

};

#endif /* DATAGETTER_H_ */
