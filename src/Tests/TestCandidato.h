/*
 * TestCandidato.h
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#ifndef TESTCANDIDATO_H_
#define TESTCANDIDATO_H_

#include "Test.h"
#include "../Candidato.h"
#include "../Cargo.h"
#include "../Lista.h"
#include "../Votante.h"
#include "../Eleccion.h"

class TestCandidato: public Test {
private:
	Candidato *candidato;
	Votante *votante;
	Eleccion *eleccion;
	Cargo *cargo;
	Lista *lista;

	bool testConstructor();

	bool testLectura_y_Escritura();
public:
	TestCandidato();
	virtual void comenzar();
	virtual void inicializar();
	virtual void liberarMemoria();
	virtual ~TestCandidato();
};

#endif /* TESTCANDIDATO_H_ */
