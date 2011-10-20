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
#include "ArbolBMas.h"
#include "hash_extensible.h"

class DataGetter {
public:
	DataGetter();
	virtual ~DataGetter();

	static vector<Lista* > getListas_por_Eleccion(Eleccion& eleccion);

	static vector<Eleccion *> getElecciones_por_Votante(Votante &votante);

	/* Se le pasa un vector vacio de punteros a elecciones (vecElecciones), una fecha en formato normal (dd/mm/aaaa o ddmmaaaa)
	 * y el votante que pide las elecciones. */
	/* Retorna TRUE si se encontro por lo menos una eleccion, retorna FALSE si no se encontro ninguna */
	static bool getEleccionesPorFechayDistrito(vector<Eleccion*> vecElecciones,string fecha, Votante &votante);


	//Metodos para Informes

	static vector<Conteo *> getConteosPorDistrito(Distrito& distrito);

	static vector<Conteo *> getConteosPorLista(Lista& lista);

	static vector<Conteo *> getConteosPorEleccion(Eleccion& eleccion);

};

#endif /* DATAGETTER_H_ */
