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

long Votante::getId()
{
	return _id;
}

int Votante::getDNI()
{
	return this->_dni;
}

void Votante::setDistrito(Distrito& distrito)
{
	this->_distrito = &distrito;
}


void Votante::Imprimir()
{
	cout<<_id;
	cout<<endl;
	cout<<_dni;
	cout<<endl;
	cout<<_nombreYApellido;
	cout<<endl;
	cout<<_clave; //TODO: La clave se imprime en las pruebas despues sacarlo
	cout<<endl;
	cout<<_domicilio;
	cout<<endl;

	//TODO: Creo q hay q imprimir lo basico del Votante, ya q podria hacer algo como
	//votante1.getDistrito.Imprimir(); cuando necesite imprimir info del distrito
	cout<<"Distrito del votante ";
	(*(_distrito)).Imprimir();
	cout<<endl;

	//TODO: Si no funciona size_type usar un long
	vector<Eleccion *>::size_type cantidadElecciones = _elecciones.size();

	//TODO: vale la misma aclaracion que para distrito
	for(vector<Eleccion *>::size_type i = 0; i < cantidadElecciones; i++)
	{
		(*(_elecciones[i])).Imprimir();
		cout<<endl;
	}
}

void Votante::Guardar(ofstream & ofs)
{
	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&_id), sizeof(_id));
	ofs.write(reinterpret_cast<char *>(&_dni), sizeof(_dni));
	Utilidades::stringToFile(_nombreYApellido, ofs);
	Utilidades::stringToFile(_clave, ofs);
	Utilidades::stringToFile(_domicilio, ofs);

	//Habria q verificar q no se guarde un Votante q se halla creado con Votante()
	//Se escribe la referencia al Cargo guardando su id
	long idDistrito = (*(_distrito)).getId();
	ofs.write(reinterpret_cast<char *>(&idDistrito), sizeof(idDistrito));

	//Aca se tendrian q guardar todos los ids(u offsets) de elecciones
	//O el offset dentro del archivo VotanteEleccion
}

void Votante::Leer(ifstream & ifs)
{
	//Comienzo escritura de atributos
	ifs.read(reinterpret_cast<char *>(&_id), sizeof(_id));
	ifs.read(reinterpret_cast<char *>(&_dni), sizeof(_dni));
	_nombreYApellido = Utilidades::stringFromFile(ifs);
	_clave = Utilidades::stringFromFile(ifs);
	_domicilio = Utilidades::stringFromFile(ifs);

	//Habria q verificar q no se guarde un Votante q se halla creado con Votante()
	//Se escribe la referencia al Cargo guardando su id
	long idDistrito = 0;
	ifs.read(reinterpret_cast<char *>(&idDistrito), sizeof(idDistrito));

	//DataAccess dataAccess;
	//Distrito distrito;
	//dataAccess.Leer(idDistrito, Distrito);
	//_distrito = &distrito; //Ver si la instancia q creo aca se guarda en el puntero o se elimina al salir del metodo

	//Aca se tendrian q leer todos los ids(u offsets) de elecciones
	//O el offset dentro del archivo VotanteEleccion y cargar los distritos al array
}


inline string Votante::getURLArchivoDatos()
{
	//Arroja una excepcion si lo uso y encima no devuelve el valor correcto
	string url((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_votante>"));

	url = "./archivos/votante.db";

	return url;
}


string Votante::getClassName()
{
	return "Votante";
}



