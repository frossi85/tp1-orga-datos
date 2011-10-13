/*
 * TestVotante.h
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#ifndef TESTVOTANTE_H_
#define TESTVOTANTE_H_

#include "Test.h"
#include "../Votante.h"
#include "../Distrito.h"

class TestVotante: public Test {

	Votante *votante;
	Distrito *distrito;
	bool testConstructor();
	bool testCambioClave();
	bool testSetters();
	bool testLectura_y_Escritura();
public:
	TestVotante();
	virtual void comenzar();
	virtual void inicializar();
	virtual void liberarMemoria();
	virtual ~TestVotante();
};

#endif /* TESTVOTANTE_H_ */
