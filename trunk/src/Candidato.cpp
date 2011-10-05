/*
 * Candidato.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Candidato.h"

Candidato::Candidato(int dni, string nombreYApellido, string clave, string domicilio, Distrito& distrito, Lista& lista, Cargo& cargo)
//: Votante::Votante(dni, nombreYApellido, clave, domicilio, distrito)
{
	//TODO: Verificar con el ID de la clase, no _id, antes de guardar, para comprobar si fue creado
	//correctamente o sea validacion
	this->_id = -1;
	//TODO: En la asignacion de abajo va &lista o solo lista??
	this->_listaPropia = &lista;
	this->_cargoAPresentarse = &cargo;

	//TODO verificar q se guarde la referencia y no se pierda cuando salgo del metodo
	//Usar un get Votante asi puedo ver si la referencia se conserva, sino ver como se hace
	//si con new o q, malloc??
	this->_votante = new Votante(dni, nombreYApellido, clave, domicilio, distrito);
	//El compilador dice: warning: taking address of temporary por lo q tengo q usar algo como malloc
	//Con el new no lanza el warning solo con &Votante, pero el new entrega un puntero o el objeto
	//TODO: Leer informacion de q hace el new en C++, creo q es el reemplazo del malloc y realoc de C
}

long Candidato::getId()
{
	return _id;
}

Cargo& Candidato::getCargo()
{
	return *(this->_cargoAPresentarse);
}



Lista& Candidato::getLista()
{
	return *(this->_listaPropia);
}



void Candidato::setLista(Lista& lista)
{
	this->_listaPropia = &lista;
}



void Candidato::setCargo(Cargo& cargo)
{
	this->_cargoAPresentarse = &cargo;
}



Candidato::~Candidato() {
	delete _votante;
}

void Candidato::Imprimir()
{
	cout<<_id;
	cout<<endl;
	(*(this->_votante)).Imprimir();

	//TODO: Creo q hay q imprimir lo basico del Candidato, ya q podria hacer algo como
	//votante1.getCargo.Imprimir(); cuando necesite imprimir info del cargo
	cout<<"Cargo del candidato ";
	(*(_cargoAPresentarse)).Imprimir();
	cout<<endl;

	//TODO: Creo q hay q imprimir lo basico del Candidato, ya q podria hacer algo como
	//votante1.getLista.Imprimir(); cuando necesite imprimir info del lista
	cout<<"Lista del candidato ";
	(*(_listaPropia)).Imprimir();
	cout<<endl;
}

void Candidato::Guardar(ofstream & ofs)
{
	//TODO: capaz por cada puntero a una instancia de otra clase deberia tener el id(offset)
	//y en leer cargar eso en vez de la instancia en si, y hacer metodos como getLista()
	//y q si el puntero esta en NULL ahi cargarlo desde la BD y mantenerlo en memoria

	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&_id), sizeof(_id));

	//Habria q verificar q no se guarde un Candidato q se halla creado con Candidato()
	//Se escribe la referencia al Cargo guardando su id
	long idVotante = (*(_votante)).getId();
	ofs.write(reinterpret_cast<char *>(&idVotante), sizeof(idVotante));

	long idCargo = (*(_cargoAPresentarse)).getId();
	ofs.write(reinterpret_cast<char *>(&idCargo), sizeof(idCargo));

	long idLista = (*(_listaPropia)).getId();
	ofs.write(reinterpret_cast<char *>(&idLista), sizeof(idLista));
}

void Candidato::Leer(ifstream & ifs)
{
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


inline string Candidato::getURLArchivoDatos()
{
	//Arroja una excepcion si lo uso y encima no devuelve el valor correcto
	string url((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_candidato>"));

	url = "./archivos/candidato.db";

	return url;
}


string Candidato::getClassName()
{
	return "Candidato";
}




