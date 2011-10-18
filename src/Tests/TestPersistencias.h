/*
 * TestPersistencias.h
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */

#ifndef TESTPERSISTENCIAS_H_
#define TESTPERSISTENCIAS_H_

#include <iostream>
#include <vector>
#include "Test.h"

#include "../Distrito.h"
#include "../Cargo.h"
#include "../Eleccion.h"
#include "../Conteo.h"
#include "../DataAccess.h"
#include "../hash_extensible.h"
#include "../RegistroIndice.h"
#include "../Configuracion.h"
#include "../ABM Entidades/ABMentidades.h"
#include "UtilidadesTests.h"


class TestPersistencias {
public:
	TestPersistencias();
	virtual ~TestPersistencias();

	void TestDistrito();
	void TestCargo();
	void TestEleccion();
	void TestVotante();
	void TestLista();
	void TestCandidato();
    void TestConteo();

private:
	DataAccess dataAccess;
};

#endif /* TESTPERSISTENCIAS_H_ */
