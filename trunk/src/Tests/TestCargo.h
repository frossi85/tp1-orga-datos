/*
 * TestCargo.h
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#ifndef TESTCARGO_H_
#define TESTCARGO_H_

#include "Test.h"
#include "../Cargo.h"

class TestCargo: public Test {
	Cargo* cargo;

	bool testConstructor();
	bool testAgregarCargoSecundarios();
	bool testLectura_y_Escritura();

public:
	TestCargo();
	virtual void comenzar();
	virtual void inicializar();
	virtual void liberarMemoria();
	virtual ~TestCargo();
};

#endif /* TESTCARGO_H_ */
