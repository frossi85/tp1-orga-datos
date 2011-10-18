/*
 * TestABMentidades.h
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */

#ifndef TESTABMENTIDADES_H_
#define TESTABMENTIDADES_H_

#include <iostream>
#include <vector>
#include "../ABM Entidades/ABMentidades.h"
#include "../ABM Entidades/ConsultaEntidades.h"
#include "Test.h"
#include "UtilidadesTests.h"
using namespace std;


class TestABMentidades {
public:
	TestABMentidades();
	virtual ~TestABMentidades();

	void testAltaDistrito();
	void testAltaCargo();
	void testAltaEleccion();
	void testAltaVotante();
	void testAltaLista();
	void testAltaCandidato();


private:
	ABMentidades ABMtest;
	ConsultaEntidades ConsultaEntidadesTest;
};

#endif /* TESTABMENTIDADES_H_ */
