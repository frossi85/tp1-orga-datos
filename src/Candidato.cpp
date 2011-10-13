/*
 * Candidato.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Candidato.h"

/* Constructor que no se deberia usar. No guardar algo contruido asi. Desp se saca si no es necesario.*/
Candidato::Candidato() {
	this->_id = -1;
	this->_listaPropia =  NULL;
	this->_votante = NULL;
}


Candidato::Candidato(Votante votante, Lista lista) {
	this->_id = ManejoIDs::obtenerIDnuevo(this->getClassName());
	this->_listaPropia =  new Lista(lista);
	this->_votante = new Votante(votante);
}


Candidato::Candidato(const Candidato &candidato) {
	this->_id = candidato._id;
	this->_listaPropia = new Lista(*(candidato._listaPropia));
	this->_votante = new Votante(*(candidato._votante));
}


Candidato::~Candidato() {
	if (this->_listaPropia != NULL)	delete this->_listaPropia;
	if (this->_votante != NULL)	delete this->_votante;
}


long Candidato::getId() {return _id;}


int Candidato::getDNI(){return this->_votante->getDNI();}


string Candidato::getNombreYApellido(){return this->_votante->getNombreYApellido();}


Cargo& Candidato::getCargo() {return (this->_listaPropia->getEleccion().getCargo());}


Lista& Candidato::getLista() {return *(this->_listaPropia);}


void Candidato::setLista(Lista lista) {
	if (this->_listaPropia != NULL) delete this->_listaPropia;
	this->_listaPropia = new Lista(lista);
}


void Candidato::setCargo(Cargo cargo) {
	this->_listaPropia->getEleccion().setCargo(cargo);
}


void Candidato::Imprimir()
{
	cout<<"Id Candidato: " <<_id <<endl;
	cout << "Informacion del candidato: " << endl;
	(*(this->_votante)).Imprimir();

	cout<<"Lista del candidato: "<<endl;
	(*(_listaPropia)).Imprimir();
	cout<<endl;
}


unsigned long int Candidato::Guardar(ofstream & ofs)
{
	//TODO: capaz por cada puntero a una instancia de otra clase deberia tener el id(offset)
	//y en leer cargar eso en vez de la instancia en si, y hacer metodos como getLista()
	//y q si el puntero esta en NULL ahi cargarlo desde la BD y mantenerlo en memoria

	unsigned long int offset = ofs.tellp();

	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&_id), sizeof(_id));

	//Habria q verificar q no se guarde un Candidato q se halla creado con Candidato()
	//Se escribe la referencia al Cargo guardando su id
	long idVotante = (*(_votante)).getId();
	ofs.write(reinterpret_cast<char *>(&idVotante), sizeof(idVotante));


	long idLista = (*(_listaPropia)).getId();
	ofs.write(reinterpret_cast<char *>(&idLista), sizeof(idLista));

	return offset;
}


void Candidato::Leer(ifstream & ifs, unsigned long int offset)
{
	// Me posiciono en el archivo
	ifs.seekg(offset,ios::beg);

	//Comienzo lectura de atributos
	ifs.read(reinterpret_cast<char *>(&_id), sizeof(_id));

	//Habria q verificar q no se guarde un Candidato q se halla creado con Candidato()
	//Se escribe la referencia al Cargo guardando su id
	long idVotante = 0;
	ifs.read(reinterpret_cast<char *>(&idVotante), sizeof(idVotante));

	long idCargo = 0;
	ifs.read(reinterpret_cast<char *>(&idCargo), sizeof(idCargo));

	long idLista = 0;
	ifs.read(reinterpret_cast<char *>(&idLista), sizeof(idLista));

	//DataAccess dataAccess;
	//Votante votante;
	//dataAccess.Leer(idVotante, votante);
	//_votante = &votante; //Ver si la instancia q creo aca se guarda en el puntero o se elimina al salir del metodo

	//Cargo cargo;
	//dataAccess.Leer(idCargo, cargo);
	//_cargoAPresentarse = &cargo; //Ver si la instancia q creo aca se guarda en el puntero o se elimina al salir del metodo

	//Lista lista;
	//dataAccess.Leer(idLista, lista);
	//_listaPropia = &lista; //Ver si la instancia q creo aca se guarda en el puntero o se elimina al salir del metodo
}


inline string Candidato::getURLArchivoDatos() {
	string url((*Configuracion::getConfig()).getValorPorPrefijo(Configuracion::URL_CANDIDATO));
	return url;
}


string Candidato::getClassName() {return "Candidato";}
