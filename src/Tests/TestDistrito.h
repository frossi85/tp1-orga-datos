/*
 * TestDistrito.h
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#ifndef TESTDISTRITO_H_
#define TESTDISTRITO_H_

#include "Test.h"
#include "../Distrito.h"
class TestDistrito: public Test {
	Distrito *distrito;
	bool testConstructor();

public:
	TestDistrito();
	virtual void comenzar();
	virtual void inicializar();
	virtual void liberarMemoria();
	virtual ~TestDistrito();
};

#endif /* TESTDISTRITO_H_ */
