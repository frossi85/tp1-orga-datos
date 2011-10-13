/*
 * Lista.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Lista.h"
#include "ManejoIDs.h"

/* Constructor que no se deberia usar. No guardar algo contruido asi. Desp se saca si no es necesario.*/
Lista::Lista()
{
	this->_eleccion = NULL;
	this->_nombre = "";
	this->_id = -1;
}


Lista::Lista(string nombre, Eleccion eleccion)
{
	this->_eleccion = new Eleccion(eleccion);
	this->_nombre = nombre;
	this->_id = ManejoIDs::obtenerIDnuevo(this->className);
}

Lista::Lista(const Lista &lista) {
	this->_id = lista._id;
	this->_nombre = lista._nombre;
	this->_eleccion = new Eleccion(*(lista._eleccion));
}


Lista::~Lista() {
	if (this->_eleccion != NULL) delete this->_eleccion;
}


long Lista::getId() {return _id;}


Eleccion& Lista::getEleccion() {return *(this->_eleccion);}


string Lista::getNombre() {return this->_nombre;}


void Lista::Imprimir()
{
	cout<<"Id Lista: " <<_id << endl;
	cout<< "Nombre Lista: " << _nombre << endl;
	cout << "Eleccion a la que se presenta: "<<endl;
	(*(_eleccion)).Imprimir();
	cout<<endl;
}


unsigned long int Lista::Guardar(ofstream & ofs)
{
	unsigned long int offset = ofs.tellp();
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
	return offset;
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

//	DataAccess dataAccess;
//	Eleccion eleccion; //si no funciona probar con un puntero a eleccion
	//dataAccess.getPorId(idEleccion, eleccion);
	//_eleccion = eleccion;
}


inline string Lista::getURLArchivoDatos() {
	return (*Configuracion::getConfig()).getValorPorPrefijo(Configuracion::URL_LISTA);
}


string Lista::getClassName() {return "Lista";}
