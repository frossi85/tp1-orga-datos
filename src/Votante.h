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

class Votante {//: public Grabable, public Logueable {
private:
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

	//Getters
	int getDNI();
	string getNombreYApellido();
	string getClave(); //TODO: Ver si en vez de esto hacemos una funciona q verifique si la clave es correcta
	string getDomicilio();
	Distrito& getDistrito();

	//Setters
	void cambiarClave(string claveAnterior, string claveNueva);
	void setDistrito(Distrito& distrito);

	//Vota para una determinada eleccion a una lista, se registra
	//q voto en la elecccion, por eso el vector eleccion pero solo
	//se incrementa el contador en el Conteo asociado a una eleccion
	//en esa Lista en el Distrito q vota
	void votarEnEleccionALista(Eleccion& eleccion, Lista& lista);
};

#endif /* VOTANTE_H_ */
