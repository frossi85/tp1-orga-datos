/*
 * Lista.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef LISTA_H_
#define LISTA_H_

#include <string>
#include "Grabable.h"
#include "Logueable.h"
#include "Eleccion.h"
#include "ManejoIDs.h"

using namespace std;

class Lista : public Grabable {
private:
	long _id;
	string _nombre;
	Eleccion *_eleccion;

public:
	Lista();
	Lista(string nombre, Eleccion eleccion);
	Lista(const Lista &lista);
	virtual ~Lista();

	//Getters
	long getId();
	Eleccion& getEleccion();
	string getNombre();

	void setId(long id) {this->_id=id;}

	unsigned long int Guardar(ofstream & ofs);
	void Leer(ifstream & ifs, unsigned long int offset);
	void Imprimir();

	inline string getURLArchivoDatos();

	//Metodos interfaz Logueable
	string getClassName();
};

#endif /* LISTA_H_ */
