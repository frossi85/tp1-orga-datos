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
	//Falta Implemetar
	static vector<Conteo*> getConteos_por_Eleccion_y_Distrito(Eleccion &eleccion,Distrito& distrito);

	//Falta Implementar
	static vector<Conteo*> getConteos_por_Lista_y_Eleccion(Lista &lista,Eleccion &eleccion);


	static vector<Eleccion *> getElecciones_por_Distrito(Distrito& distrito);

	static vector<Lista* > getListas_por_Eleccion(Eleccion& eleccion);

	static Conteo* getConteo(Eleccion& eleccion,Lista& lista, Distrito& distrito);

	//Devuelve el puntero a un votante
	//Devuelve NULL si no encontro al votante con ese dni
	//Falta Implementar
	static Votante* getVotante(const char dni[]);


	static vector<Eleccion *> getElecciones_por_Votante(Votante &votante);
	virtual ~DataGetter();

};

#endif /* DATAGETTER_H_ */
