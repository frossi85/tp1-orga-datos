/*
 * Candidato.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef CANDIDATO_H_
#define CANDIDATO_H_

#include "Grabable.h"
#include "Logueable.h"
#include "Votante.h"
#include "Cargo.h"
#include <string>

using namespace std;

class Candidato : Grabable {//: public Votante {
private:
	long _id;
	Lista * _listaPropia;
	Cargo * _cargoAPresentarse;
	Votante * _votante;
public:
	Candidato(int dni, string nombreYApellido, string clave, string domicilio, Distrito& distrito, Lista& lista, Cargo& cargo);
	//TODO: IMPORTANTE: Cuando creo el votante dentro del candidato y lo guardo primero tengo q ver no exista el votante, por q si existe
	//en vez de guardarlo deberia guarrdar la referencia al existente
	//Igual podria duplicar Votantes, para simplificar ya q lo importante es el arbol y el hash

	virtual ~Candidato();

	//Getters
	long getId();
	Lista& getLista();
	Cargo& getCargo();

	//TODO: los setters deberian ser por la entidad entera o pasarles el id y despues ir a buscarlos
	//a la BD y asignarselos a el atributo privado q lo contiene
	//Setters
	void setLista(Lista& lista);
	void setCargo(Cargo& cargo);

	//Interface de Guardable
	unsigned long int Guardar(ofstream & ofs);
	void Leer(ifstream & ifs, unsigned long int offset);
	void Imprimir();

	inline string getURLArchivoDatos();

	//Metodo de prueba
	void setId(long id){
		this->_id=id;
	}

	//Metodos interfaz Logueable
	string getClassName();
};

#endif /* CANDIDATO_H_ */
