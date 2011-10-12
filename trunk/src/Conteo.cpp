/*
 * Conteo.cpp
 *
 *  Created on: 24/09/2011
 *      Author: facundo
 */

#include "Conteo.h"

Conteo::Conteo(Eleccion& eleccion, Lista& lista, Distrito& distrito) : _lista(lista), _distrito(distrito), _eleccion(eleccion){
	this->cantidad = 0;
}

Conteo::~Conteo() {
	// TODO Auto-generated destructor stub
}

void Conteo::incrementar()
{
	this->cantidad++;
}

long Conteo::getVotos(){

	return cantidad;
}

Lista* Conteo::getLista(){

	return &this->_lista;

}

Distrito* Conteo::getDistrito(){

	return &this->_distrito;
}

unsigned long int Conteo::Guardar(ofstream & ofs){

}

void Conteo::Leer(ifstream & ifs, unsigned long int offset){

}

string Conteo::getURLArchivoDatos(){

}

string Conteo::getClassName(){

	return "Conteo";

}


