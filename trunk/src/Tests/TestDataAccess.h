/*
 * testDataAccess.h
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#ifndef TESTDATAACCESS_H_
#define TESTDATAACCESS_H_

#include "Test.h"
#include "../DataAccess.h"

class TestDataAccess: public Test {
private:
	DataAccess *dataAccess;

public:
	TestDataAccess();
	virtual void comenzar();
	virtual void inicializar();
	virtual ~TestDataAccess();
};

#endif /* TESTDATAACCESS_H_ */
