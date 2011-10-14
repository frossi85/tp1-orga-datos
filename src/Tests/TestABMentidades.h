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
#include "Test.h"
/*#include "../Distrito.h"
#include "../Cargo.h"
#include "../Eleccion.h"
#include "../DataAccess.h"
#include "../hash_extensible.h"
#include "../RegistroIndice.h"
#include "../Configuracion.h"*/


/*
 * Ya Agregue Este Test para que se ejecute con Tester
 */


class TestABMentidades: public Test {
public:
	TestABMentidades();
	virtual ~TestABMentidades();

	void testAltaDistrito();
	void testAltaCargo();
	void testAltaEleccion();
	void testAltaVotante();
	void testAltaCandidato();
	void testAltaLista();

	void comenzar();
	void inicializar(){ }
	void liberarMemoria(){ }

private:
	ABMentidades ABMtest;
	ConsultaEntidades ConsultaEntidadesTest;
};

#endif /* TESTABMENTIDADES_H_ */
