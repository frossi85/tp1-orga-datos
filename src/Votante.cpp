/*
 * Votante.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Votante.h"

Votante::Votante(int dni, string nombreYApellido, string clave, string domicilio, Distrito& distrito)
{
	this->_dni = dni;
	this->_nombreYApellido = nombreYApellido;
	this->_clave = clave;
	this->_domicilio = domicilio;
	this->_distrito = &distrito;
}



string Votante::getClave()
{
	return this->_clave;
}



void Votante::votarEnEleccionALista(Eleccion& eleccion, Lista& lista)
{
	//TODO: Implementar el metodo votar
}



Votante::~Votante()
{
}



string Votante::getNombreYApellido()
{
	return this->_nombreYApellido;
}



string Votante::getDomicilio()
{
	return this->_domicilio;
}



Distrito& Votante::getDistrito()
{
	return *(this->_distrito);
}



void Votante::cambiarClave(string claveAnterior, string claveNueva)
{
	//TODO:VErificar si claveAnterior es igual a this->clave, si lo es
	//cambiarla por claveNueva. Sino arrojar una excepcion
	this->_clave = claveNueva;
}



int Votante::getDNI()
{
	return this->_dni;
}



void Votante::setDistrito(Distrito& distrito)
{
	this->_distrito = &distrito;
}



