/*
 * Nodo.cpp
 *
 *  Created on: 02/10/2011
 *      Author: martin
 */

#include "Nodo.h"

Nodo::Nodo() {
	this->nivel = 0;
	this->nroNodo = 0;
	this->cantidadRegistros = 0;
	this->capacidadRegistros = 0;
}

Nodo::Nodo(unsigned int nivel, unsigned int nroNodo, unsigned int capacidadRegistros) {
	this->nivel = nivel;
	this->nroNodo = nroNodo;
	this->cantidadRegistros = 0;
	this->capacidadRegistros = capacidadRegistros;

}

unsigned int getNivel() {
	return this->nivel;
}

unsigned int getNroNodo() {
	return this->nroNodo;
}
unsigned int getCantidadRegistros() {
	return this->cantidadRegistros;
}
unsigned int getCapacidadRegistros() {
	return this->capacidadRegistros;
}

Nodo::~Nodo() {
	// TODO Auto-generated destructor stub
}
