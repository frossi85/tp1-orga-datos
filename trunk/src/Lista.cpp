/*
 * Lista.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Lista.h"

Lista::Lista(string nombre, Eleccion& eleccion)
{
	this->_nombre = nombre;
	this->_eleccion = &eleccion;
}



Eleccion& Lista::getEleccion()
{
	return *(this->_eleccion);
}



string Lista::getNombre()
{
	return this->_nombre;
}



Lista::~Lista()
{
}



