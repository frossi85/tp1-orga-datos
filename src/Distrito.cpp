/*
 * Distrito.cpp
 *
 *  Created on: 16/09/2011
 *      Author: leo
 */

#include "Distrito.h"

Distrito::Distrito(string nombre){
	this->nombre = nombre;
}

Distrito::Distrito(long id, string nombre){
	this->nombre = nombre;
	this->id = id;
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

void Distrito::Crear(ofstream & ofs)
{
	//Distrito::_dataBaseUrl = "./distrito.db";

	if(!ofs.is_open())  //o if(!ofs)
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de Distritos");

	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&id), sizeof(id));
	Utilidades::stringToFile(nombre, ofs);
}

void Distrito::Leer(ifstream & ifs)
{
	//Distrito::_dataBaseUrl = "./distrito.db";

	//ifstream ifs("./distrito.db", ios::binary);

	if(!ifs.is_open())  //o if(!ifs)
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de Distritos");

	//Comienzo escritura de atributos
	ifs.read(reinterpret_cast<char *>(&id), sizeof(id));
	string nombreDistrito = Utilidades::stringFromFile(ifs);

	ifs.close();

	this->nombre = nombreDistrito;
	//Distrito distrito(nombreDistrito);
	//distrito.id = id;

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







