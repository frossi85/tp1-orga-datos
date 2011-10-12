/*
 * TestEleccion.h
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#ifndef TESTELECCION_H_
#define TESTELECCION_H_

#include "Test.h"
#include "../Eleccion.h"

class TestEleccion: public Test {

	Eleccion *eleccion;
	bool testConstructor();
	bool testLectura_y_Escritura();

public:
	TestEleccion();
	virtual void comenzar();
	virtual void inicializar();
	virtual ~TestEleccion();
};

#endif /* TESTELECCION_H_ */
