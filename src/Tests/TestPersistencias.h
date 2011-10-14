/*
 * TestPersistencias.h
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */

#ifndef TESTPERSISTENCIAS_H_
#define TESTPERSISTENCIAS_H_

#include <iostream>
#include "Test.h"

#include "../Distrito.h"
#include "../Cargo.h"
#include "../Eleccion.h"
#include "../DataAccess.h"
#include "../hash_extensible.h"
#include "../RegistroIndice.h"
#include "../Configuracion.h"

/*
 * Ya Agregue Este Test para que se ejecute con Tester
 */

class TestPersistencias: public Test {
public:
	TestPersistencias();
	virtual ~TestPersistencias();

	void TestDistrito();
	void TestCargo();
	void TestEleccion();

	void comenzar();
	void inicializar(){ }
	void liberarMemoria(){ }
private:
	DataAccess dataAccess;

};

#endif /* TESTPERSISTENCIAS_H_ */