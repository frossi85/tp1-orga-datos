/*
 * Candidato.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Candidato.h"

Candidato::Candidato(int dni, string nombreYApellido, string clave, string domicilio, Distrito& distrito, Lista& lista, Cargo& cargo)
: Votante::Votante(dni, nombreYApellido, clave, domicilio, distrito)
//: _listaPropia(lista), _cargoAPresentarse(cargo)
{
	//TODO: En la asignacion de abajo va &lista o solo lista??
	this->_listaPropia = &lista;
	this->_cargoAPresentarse = &cargo;
}



Cargo& Candidato::getCargo()
{
	return *(this->_cargoAPresentarse);
}



Lista& Candidato::getLista()
{
	return *(this->_listaPropia);
}



void Candidato::setLista(Lista& lista)
{
	this->_listaPropia = &lista;
}



void Candidato::setCargo(Cargo& cargo)
{
	this->_cargoAPresentarse = &cargo;
}



Candidato::~Candidato() {
	// TODO Auto-generated destructor stub
}
