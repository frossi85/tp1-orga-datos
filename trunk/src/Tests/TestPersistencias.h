/*
 * TestPersistencias.h
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */

#ifndef TESTPERSISTENCIAS_H_
#define TESTPERSISTENCIAS_H_

#include <iostream>

#include "../Distrito.h"
#include "../Cargo.h"
#include "../Eleccion.h"
#include "../DataAccess.h"
#include "../hash_extensible.h"
#include "../RegistroIndice.h"
#include "../Configuracion.h"

class TestPersistencias {
public:
	TestPersistencias();
	virtual ~TestPersistencias();

	void TestDistrito();
	void TestCargo();
	void TestEleccion();

private:
	DataAccess dataAccess;
};

#endif /* TESTPERSISTENCIAS_H_ */
