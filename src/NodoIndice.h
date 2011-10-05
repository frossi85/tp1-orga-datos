/*
 * NodoIndice.h
 *
 *  Created on: 02/10/2011
 *      Author: martin
 */

#ifndef NODOINDICE_H_
#define NODOINDICE_H_

#include "Nodo.h"

class NodoIndice: public Nodo {
public:
	NodoIndice();
	virtual ~NodoIndice();

private:
	unsigned int primerHijoIzq;
};


#endif /* NODOINDICE_H_ */
