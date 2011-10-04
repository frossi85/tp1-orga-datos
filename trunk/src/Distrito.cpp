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
	//Arroja una excepcion si lo uso y encima no devuelve el valor correcto
	string url((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_distritos>"));

	url = "./archivos/distrito.db";

	return url;
}

string Distrito::getClassName()
{
	return "Distrito";
}






