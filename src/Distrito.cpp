/*
 * Distrito.cpp
 *
 *  Created on: 16/09/2011
 *      Author: Facundo Rossi
 */

#include "Distrito.h"

Distrito::Distrito(string nombre){
	this->_nombre = nombre;
}

Distrito::Distrito()
{
	_id = -1;
	_nombre = "";
}

long Distrito::getId()
{
	return _id;
}

string Distrito::getNombre()
{
	return this->_nombre;
}

Distrito::~Distrito() {
}

void Distrito::Guardar(ofstream & ofs)
{
	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&_id), sizeof(_id));
	Utilidades::stringToFile(_nombre, ofs);
}

void Distrito::Leer(ifstream & ifs)
{
	//Comienzo lectura de atributos
	ifs.read(reinterpret_cast<char *>(&_id), sizeof(_id));
	_nombre = Utilidades::stringFromFile(ifs);

	ifs.close();

	Imprimir();
}

void Distrito::Imprimir()
{
	cout<<endl;
	cout<<"Id: ";
	cout<< _id;
	cout<<endl;
	cout<<"Nombre Distrito: ";
	cout<< _nombre;
	cout<<endl;
}

string Distrito::getURLArchivoDatos()
{
	return ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_distrito>"));
}

string Distrito::getClassName()
{
	return "Distrito";
}







