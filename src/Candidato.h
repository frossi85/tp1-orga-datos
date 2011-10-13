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

class Candidato : Grabable {
private:
	long _id;
	Lista * _listaPropia;
	Votante * _votante;
public:
	Candidato();
	Candidato(Votante votante, Lista lista);
	Candidato(const Candidato &candidato);
	virtual ~Candidato();

	//Getters
	long getId();
	Lista& getLista();
	Cargo& getCargo();
	int getDNI();
	string getNombreYApellido();

	//TODO: los setters deberian ser por la entidad entera o pasarles el id y despues ir a buscarlos
	//a la BD y asignarselos a el atributo privado q lo contiene
	//Setters
	void setId(long id) {this->_id=id;}
	void setLista(Lista lista);
	void setCargo(Cargo cargo);

	//Interface de Guardable
	unsigned long int Guardar(ofstream & ofs);
	void Leer(ifstream & ifs, unsigned long int offset);
	void Imprimir();

	inline string getURLArchivoDatos();

	//Metodos interfaz Logueable
	string getClassName();
};

#endif /* CANDIDATO_H_ */