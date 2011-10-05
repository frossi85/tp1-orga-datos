/*
 * Conteo.h
 *
 *  Created on: 24/09/2011
 *      Author: facundo
 */

#ifndef CONTEO_H_
#define CONTEO_H_

#include <string>
#include "Grabable.h"
#include "Logueable.h"
#include "Lista.h"
#include "Distrito.h"
#include "Eleccion.h"

using namespace std;

class Conteo : public Grabable {
private:
	Lista& _lista;
	Distrito& _distrito;
	Eleccion& _eleccion;
	int cantidad;

public:
	//Las referencias deben ser inicializadas si o si en el constructor mediante listas de
	//inicializacion como en el ejemplo de abajo
	Conteo(Eleccion& eleccion, Lista& lista, Distrito& distrito);
	virtual ~Conteo();

	void incrementar();
};

#endif /* CONTEO_H_ */
