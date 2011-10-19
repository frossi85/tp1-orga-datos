/*
 * CargaInicial.h
 *
 *  Created on: 19/10/2011
 *      Author: facundo
 */

#ifndef CARGAINICIAL_H_
#define CARGAINICIAL_H_

#include "Utilidades.h"
#include "./Tests/UtilidadesTests.h"
#include "./ABM Entidades/ABMentidades.h"
#include "Votante.h"

using namespace std;

class CargaInicial {
private:
	CargaInicial();
	virtual ~CargaInicial();
public:
	static void ejecutar();
	static void getVotantes(vector<Votante *> &votantes, vector<Distrito> &distritos);
	vector<string> getFechasElecciones();
};

#endif /* CARGAINICIAL_H_ */
