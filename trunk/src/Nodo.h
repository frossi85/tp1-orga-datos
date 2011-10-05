/*
 * Nodo.h
 *
 *  Created on: 02/10/2011
 *      Author: martin
 */

#ifndef NODO_H_
#define NODO_H_

class Nodo {
public:
	Nodo();
	Nodo(unsigned int nivel, unsigned int nroNodo, unsigned int capacidadRegistros);
	unsigned int getNivel();
	unsigned int getNroNodo();
	unsigned int getCantidadRegistros();
	unsigned int getCapacidadRegistros();

	virtual ~Nodo();

protected:
	unsigned int nivel;
	unsigned int nroNodo;
	unsigned int cantidadRegistros;
	unsigned int capacidadRegistros;
	RegistroArbol registros[];
};


#endif /* NODO_H_ */
