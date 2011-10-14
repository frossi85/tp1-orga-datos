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
//#include "Conteo.h"


//class Conteo;

class DataAccess {

private:
	Configuracion & configuracion;
public:
	DataAccess();
	virtual ~DataAccess();

	unsigned long int Guardar(Grabable & obj);				// Retorna el offset de donde lo guardo.
	void Eliminar(Grabable & obj);
	void Leer(Grabable & obj, unsigned long int offset);

	//*************************************************************************************************************************
	// LA IDEA DEL DATA ACCESS ES QUE RECIBA Y DEVUELVA OBJETOS DE LA CLASE PADRE GUARDABLE. ESTOS METODOS TENDRIAN QUE ESTAR
	// EN OTRO LADO. ESTA CLASE ES PARA LEER GUARDAR Y ELIMINAR. SI LE METEMOS ESTOS INCLUDES SE HACEN REFERENCIAS CIRCULARES.



};

#endif /* DATAACCESS_H_ */
