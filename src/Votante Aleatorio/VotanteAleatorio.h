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
#include "../Distrito.h"
#include "../Eleccion.h"
#include <stdlib.h>
#include <time.h>
#include <string>
#include <stdio.h>
#include <vector>

class VotanteAleatorio {
public:
	VotanteAleatorio(unsigned int cantidad);
	virtual ~VotanteAleatorio();
	void Imprimir();
	unsigned int getAccesos() {return this->accesos;}
	unsigned int getVotos() {return this->votos;}
	int hacerlosAccederAlSistema();
	int hacerlosVotar();

private:
	Votante **vectorVotantes;
	unsigned int cantidad;
	unsigned int accesos;		// Cantidad de accesos de votantes al sistema (no cuenta accesos fallidos)
	unsigned int votos;			// Cantidad de votos totales (si en una eleccion se cambia de voto X veces, cuenta como 1 solo voto)
	string getStringAleatorio();
	Distrito getDistritoAleatorio();
	void simularAcceso(unsigned int DNI,string clave,bool);
	void simularVotacion(int indice,Eleccion* eleccion,bool esCorrecto);

};

#endif /* VOTANTEALEATORIO_H_ */
