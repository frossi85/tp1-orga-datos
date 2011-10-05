/*
 * NodoHoja.h
 *
 *  Created on: 02/10/2011
 *      Author: martin
 */

#ifndef NODOHOJA_H_
#define NODOHOJA_H_

#include "Nodo.h"

class NodoHoja: public Nodo {
public:
	NodoHoja();
	virtual ~NodoHoja();

private:
	unsigned int siguienteHoja;
};


#endif /* NODOHOJA_H_ */
