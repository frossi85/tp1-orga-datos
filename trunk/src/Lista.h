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
#include "DataAccess.h"


using namespace std;

class Lista : public Grabable {
private:
	long _id;
	string _nombre;
	Eleccion * _eleccion;
public:
	Lista();
	Lista(string nombre, Eleccion& eleccion);
	virtual ~Lista();

	//Getters
	Eleccion const& getEleccion() const;
	string getNombre();

	void Guardar(ofstream & ofs);
	void Leer(ifstream & ifs);
	void Imprimir();

	inline string getURLArchivoDatos();

	//Metodo de prueba
	void setId(long id){
		this->_id=id;
	}

	//Metodos interfaz Logueable
	string getClassName();

	//Por lo q veo en el modelo una lista esta asociada con una y solo una eleccion en particular
	//por lo cual no se necesitan setters
	//TODO: Una lista solo se presenta a una eleccion, si se quieren presentar los mismos candidatos
	//para una proxima eleccion deben crear otra lista
};

#endif /* LISTA_H_ */