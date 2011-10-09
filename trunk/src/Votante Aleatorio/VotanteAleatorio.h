/*
 * VotanteAleatorio.h
 *
 *  Created on: 08/10/2011
 *      Author: martin
 */

#ifndef VOTANTEALEATORIO_H_
#define VOTANTEALEATORIO_H_
#include "../Votante.h"
#include "../Utilidades.h"
#include <stdlib.h>
#include <time.h>
#include <string>
#include <stdio.h>

class VotanteAleatorio {
public:
	VotanteAleatorio(unsigned int cantidad);
	virtual ~VotanteAleatorio();
	void Imprimir();


private:
	Votante **vectorVotantes;
	unsigned int cantidad;
	string getStringAleatorio();
};

#endif /* VOTANTEALEATORIO_H_ */
