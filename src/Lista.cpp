/*
 * Lista.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Lista.h"
#include "DataAccess.h"

Lista::Lista()
{
	this->_eleccion = NULL;
	this->_nombre = "";
	this->_id = -1;
}


Lista::Lista(string nombre, Eleccion & eleccion)
{
	this->_eleccion = &eleccion;
	this->_nombre = nombre;
	this->_id = 0;
}

long Lista::getId()
{
	return _id;
}

Eleccion const& Lista::getEleccion() const
{
	return *(this->_eleccion);
}



string Lista::getNombre()
{
	return this->_nombre;
}

Lista::~Lista()
{//Q pasa con el puntero a eleccion, debo liberar esa memoria?? o llamar al destructor de eleccion??
}

void Lista::Imprimir()
{
	cout<<_id;
	cout<<endl;
	cout<<_nombre;
	cout<<endl;
	(*(_eleccion)).Imprimir(); //ver q imprimo de la eleccion
	cout<<endl;
}

unsigned long int Lista::Guardar(ofstream & ofs)
{
	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&_id), sizeof(_id));
	Utilidades::stringToFile(_nombre, ofs);

	//Habria q verificar q no se guarde una Lista q se halla creado con Lista()
	//Se escribe la referencia a la Eleccion guardando su id
	long idEleccion = (*(_eleccion)).getId();
	ofs.write(reinterpret_cast<char *>(&idEleccion), sizeof(idEleccion));

	//No se si va lo de abajo por q tendria sentido si se modifico
	//y se tendria q tener un flag q indique si se modifico algun atributo
	//es un quilombo no hacer lo de abajo, solo actualizar la referencia.
	//(*(_eleccion)).fueModificada();
	//DataAccess dataAccess;
	//dataAccess.Guardar(*(_eleccion));
}

void Lista::Leer(ifstream & ifs, unsigned long int offset)
{
	//Comienzo lectura de atributos
	ifs.read(reinterpret_cast<char *>(&_id), sizeof(_id));
	_nombre = Utilidades::stringFromFile(ifs);

	//Habria q verificar q no se guarde una Lista q se halla creado con Lista()
	//Se escribe la referencia a la Eleccion guardando su id
	long idEleccion = 0;
	ifs.read(reinterpret_cast<char *>(&idEleccion), sizeof(idEleccion));

	DataAccess dataAccess;
	Eleccion eleccion; //si no funciona probar con un puntero a eleccion
	//dataAccess.getPorId(idEleccion, eleccion);
	//_eleccion = eleccion;
}



inline string Lista::getURLArchivoDatos()
{
	cout<<(*Configuracion::getConfig()).getValorPorPrefijo("<ruta_lista>");
	return (*Configuracion::getConfig()).getValorPorPrefijo("<ruta_lista>");
}



string Lista::getClassName()
{
	return "Lista";
}










