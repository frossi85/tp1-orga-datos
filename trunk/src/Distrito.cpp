/*
 * Distrito.cpp
 *
 *  Created on: 16/09/2011
 *      Author: Facundo Rossi
 */

#include "Distrito.h"

Distrito::Distrito(string nombre){
	this->nombre = nombre;
}

Distrito::Distrito()
{
	id = -1;
	nombre = "";
}

string Distrito::getNombre()
{
	return this->nombre;
}

Distrito::~Distrito() {
}

void Distrito::Guardar(ofstream & ofs)
{
	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&id), sizeof(id));
	Utilidades::stringToFile(nombre, ofs);
}

void Distrito::Leer(ifstream & ifs)
{
	//Comienzo lectura de atributos
	ifs.read(reinterpret_cast<char *>(&id), sizeof(id));
	nombre = Utilidades::stringFromFile(ifs);

	ifs.close();

	Imprimir();
}

void Distrito::Imprimir()
{
	cout<<endl;
	cout<<"Id: ";
	cout<< id;
	cout<<endl;
	cout<<"Nombre Distrito: ";
	cout<<nombre;
	cout<<endl;
}

string Distrito::getURLArchivoDatos()
{
	//Arroja una excepcion si lo uso y encima no devuelve el valor correcto
	string url((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_distritos>"));

	url = "./distrito.db";

	return url;
}

string Distrito::getClassName()
{
	return "Distrito";
}







