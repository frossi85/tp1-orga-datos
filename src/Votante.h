/*
 * Votante.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef VOTANTE_H_
#define VOTANTE_H_

#include "Grabable.h"
#include "Logueable.h"
#include "Distrito.h"
#include "Eleccion.h"
#include "Lista.h"
#include <string>
#include <vector>

using namespace std;

class Votante : public Grabable {
private:
	long _id;
	int _dni;
	string _nombreYApellido;
	string _clave; //TODO: preguntar que es la clave en el Votante
	string _domicilio;

	//Claves primarias de entidades asociadas al votante
	Distrito* _distrito;
	vector<Eleccion *> _elecciones;


public:
	Votante(int dni, string nombreYApellido, string clave, string domicilio, Distrito& distrito);
	virtual ~Votante();

	Votante(const Votante &votante);

	//Getters
	long getId(); //TODO: Fijarme si lo fuerzo a implementar poniendolo en Guardable como virtual
	int getDNI();
	string getNombreYApellido();
	string getClave(); //TODO: Ver si en vez de esto hacemos una funciona q verifique si la clave es correcta
	string getDomicilio();
	Distrito& getDistrito();
	vector<Eleccion *> getElecciones();		// Agregado por martin. Devuelve copias de las elecciones del votante. (Liberar memoria desde donde se llame).

	//Setters
	void cambiarClave(string claveAnterior, string claveNueva);
	void setDistrito(Distrito& distrito);
	void setDomicilio(string nuevo_domicilio);

	//Vota para una determinada eleccion a una lista, se registra
	//q voto en la elecccion, por eso el vector eleccion pero solo
	//se incrementa el contador en el Conteo asociado a una eleccion
	//en esa Lista en el Distrito q vota
	void votarEnEleccionALista(Eleccion& eleccion, Lista& lista);

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

#endif /* VOTANTE_H_ */
