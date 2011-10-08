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


class DataAccess {
	//En el contructor levantar todas las configuraciones
private:
	Configuracion & configuracion;
public:
	DataAccess();
	virtual ~DataAccess();

	//Hay q hacer uno q reciba un GuardableHash y otro con un GuardableArbol
	void Guardar(Grabable & obj);
	void Eliminar(Grabable & obj);
	void getPorId(long id, Grabable & obj);

	long getIdPorNombre(char objeto, string clave);
	vector<Conteo*> getConteos_por_Eleccion_y_Distrito(Eleccion &eleccion,Distrito&);
	vector<Conteo*> getConteos_por_Lista_y_Eleccion(Lista &lista,Eleccion &eleccion);
};

#endif /* DATAACCESS_H_ */
