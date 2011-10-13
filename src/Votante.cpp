/*
 * Votante.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Votante.h"
#include "ManejoIDs.h"

/* Constructor que no se deberia usar. No guardar algo contruido asi. Desp se saca si no es necesario.*/
Votante::Votante() {
	this->_dni = -1;
	this->_nombreYApellido = "";
	this->_clave = "";
	this->_domicilio = "";
	this->_distrito = NULL;
	this->_id = -1;
}

Votante::Votante(int dni, string nombreYApellido, string clave, string domicilio, Distrito distrito)
{
	this->_dni = dni;
	this->_nombreYApellido = nombreYApellido;
	this->_clave = clave;
	this->_domicilio = domicilio;
	this->_distrito = new Distrito(distrito);
	this->_id = ManejoIDs::obtenerIDnuevo(this->getClassName());
}


Votante::Votante(const Votante &votante) {
	this->_dni = votante._dni;
	this->_clave = votante._clave;
	this->_domicilio = votante._domicilio;
	this->_id = votante._id;
	this->_nombreYApellido = votante._nombreYApellido;
	this->_distrito = new Distrito(*(votante._distrito));
	int cantidad = votante._elecciones.size();
	for(int i=0;i<cantidad;i++) this->_elecciones.push_back(new Eleccion(*(votante._elecciones[i])));
}


Votante::~Votante() {
	if (this->_distrito != NULL)	delete this->_distrito;
	int cantidad = this->_elecciones.size();
	for(int i=0;i<cantidad;i++) {
		if (this->_elecciones[i] != NULL)	delete this->_elecciones[i];
	}
}


string Votante::getClave() {return this->_clave;}


long Votante::getId() {return _id;}


int Votante::getDNI() {return this->_dni;}


string Votante::getNombreYApellido() {return this->_nombreYApellido;}


string Votante::getDomicilio() {return this->_domicilio;}


Distrito Votante::getDistrito() {return *(this->_distrito);}


void Votante::votarEnEleccionALista(Eleccion& eleccion, Lista& lista)
{
	//TODO: Implementar el metodo votar
}


void Votante::agregarEleccion(Eleccion eleccion) {
	this->_elecciones.push_back(new Eleccion(eleccion));
}


/* Devuelve una copia del vector de punteros a Eleccion, y copias de los datos apuntados por cada Eleccion*.
 * Si no fueran copias, se podria modificar desde el que lo llame y arruina todo
 * ESTAS SERIAN EN REALIDAD LAS ELECCIONES EN LAS QUE YA VOTO
 */
vector<Eleccion *> Votante::getElecciones() {
	int cantidad = this->_elecciones.size();
	vector<Eleccion *> retorno;
	for(int i=0;i<cantidad;i++){
		retorno.push_back(new Eleccion(*(this->_elecciones[i])));
	}
	return retorno;
}


bool Votante::cambiarClave(string claveAnterior, string claveNueva)
{
	if (claveAnterior == this->_clave) {
		this->_clave = claveNueva;
		return true;
	}
	return false;
}


void Votante::setDistrito(Distrito distrito)
{
	delete this->_distrito;
	this->_distrito = new Distrito(distrito);
}


void Votante::setDomicilio(string nuevo_domicilio){
	this->_domicilio=nuevo_domicilio;
}


void Votante::Imprimir()
{
	cout<<"DNI: "<<_dni<<endl;
	cout<<"Apellido y Nombre: "<<_nombreYApellido<<endl;
	cout<<"Clave: "<<_clave<<endl;
	cout<<"Domicilio: "<<_domicilio<<endl;
	cout<<"Distrito: "<<endl;
	(*(_distrito)).Imprimir();

	//TODO: Si no funciona size_type usar un long
	vector<Eleccion *>::size_type cantidadElecciones = _elecciones.size();

	//TODO: vale la misma aclaracion que para distrito
	cout << "Elecciones en las que ya voto: "<<endl;
	for(vector<Eleccion *>::size_type i = 0; i < cantidadElecciones; i++)
	{
		(*(_elecciones[i])).Imprimir();
		cout<<endl;
	}
}


unsigned long int Votante::Guardar(ofstream & ofs)
{
	unsigned long int offset = ofs.tellp();
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
	return offset;
}


void Votante::Leer(ifstream & ifs, unsigned long int offset)
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
	return (*Configuracion::getConfig()).getValorPorPrefijo(Configuracion::URL_VOTANTES);
}


string Votante::getClassName() {return "Votante";}