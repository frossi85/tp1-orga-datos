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
#include "../Cargo.h"
#include "../Distrito.h"

class TestEleccion: public Test {

	Eleccion *eleccion;
	Cargo *cargo;
	Distrito *distrito;
	bool testConstructor();
	bool testAgregarDistrito();
	bool testLectura_y_Escritura();

public:
	TestEleccion();
	virtual void comenzar();
	virtual void inicializar();
	virtual void liberarMemoria();
	virtual ~TestEleccion();
};

#endif /* TESTELECCION_H_ */
