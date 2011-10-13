/*
 * DataAccess.h
 *
 *  Created on: 03/10/2011
 *      Author: facundo
 */

#ifndef DATAACCESS_H_
#define DATAACCESS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Grabable.h"
#include "Logueable.h"
#include "Logger.h"
#include "Utilidades.h"
#include "VotoElectronicoExcepcion.h"
#include "Configuracion.h"
#include "Distrito.h"
#include "Conteo.h"
#include "Votante.h"
#include "Eleccion.h"
#include "Lista.h"


class DataAccess {
	//En el contructor levantar todas las configuraciones
private:
	Configuracion & configuracion;
public:
	DataAccess();
	virtual ~DataAccess();

	//Hay q hacer uno q reciba un GuardableHash y otro con un GuardableArbol --> No te preocupes, q esta clase sea solo para guardar en los arch de datos (MARTIN)
	unsigned long int Guardar(Grabable & obj);				// Retorna el offset de donde lo guardo.
	void Eliminar(Grabable & obj);
	void Leer(Grabable & obj, unsigned long int offset);

	long getIdPorNombre(char objeto, string clave);

	//Falta Implemetar
	vector<Conteo*> getConteos_por_Eleccion_y_Distrito(Eleccion &eleccion,Distrito&);

	//Falta Implementar
	vector<Conteo*> getConteos_por_Lista_y_Eleccion(Lista &lista,Eleccion &eleccion);

	//Devuelve el puntero a un votante
	//Devuelve NULL si no encontro al votante con ese dni
	//Falta Implementar
	Votante* getVotante(const char dni[]);
};

#endif /* DATAACCESS_H_ */
