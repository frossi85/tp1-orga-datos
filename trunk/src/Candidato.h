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

class Candidato : public Votante {
private:
	Lista * _listaPropia;
	Cargo * _cargoAPresentarse;

public:
	Candidato(int dni, string nombreYApellido, string clave, string domicilio, Distrito& distrito, Lista& lista, Cargo& cargo);
	virtual ~Candidato();

	//Getters
	Lista& getLista();
	Cargo& getCargo();

	//TODO: los setters deberian ser por la entidad entera o pasarles el id y despues ir a buscarlos
	//a la BD y asignarselos a el atributo privado q lo contiene
	//Setters
	void setLista(Lista& lista);
	void setCargo(Cargo& cargo);
};

#endif /* CANDIDATO_H_ */
