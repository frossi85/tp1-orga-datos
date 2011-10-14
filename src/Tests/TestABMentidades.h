/*
 * TestABMentidades.h
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */

#ifndef TESTABMENTIDADES_H_
#define TESTABMENTIDADES_H_

#include <iostream>
#include "../ABM Entidades/ABMentidades.h"
#include "../ABM Entidades/ConsultaEntidades.h"
/*#include "../Distrito.h"
#include "../Cargo.h"
#include "../Eleccion.h"
#include "../DataAccess.h"
#include "../hash_extensible.h"
#include "../RegistroIndice.h"
#include "../Configuracion.h"*/

class TestABMentidades {
public:
	TestABMentidades();
	virtual ~TestABMentidades();

	void testAltaDistrito();
	void testAltaCargo();
	void testAltaEleccion();
	void testAltaVotante();
	void testAltaCandidato();
	void testAltaLista();

private:
	ABMentidades ABMtest;
	ConsultaEntidades ConsultaEntidadesTest;
};

#endif /* TESTABMENTIDADES_H_ */
