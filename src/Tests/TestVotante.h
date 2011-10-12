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

class TestVotante: public Test {

	Votante *votante;
	bool testConstructor();
	bool testCambioClave();
	bool testSetters();
public:
	TestVotante();
	virtual void comenzar();
	virtual void inicializar();
	virtual ~TestVotante();
};

#endif /* TESTVOTANTE_H_ */
