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
#include "../ABMEntidades/ABMentidades.h"
#include "../ABMEntidades/ConsultaEntidades.h"
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
	void testAltaConteo();
	void testBajaDistrito();
	void testBajaCargo();
	void testBajaEleccion();
	void testBajaVotante();
	void testBajaLista();
	void testBajaCandidato();


private:
	ABMentidades ABMtest;
	ConsultaEntidades ConsultaEntidadesTest;
};

#endif /* TESTABMENTIDADES_H_ */
