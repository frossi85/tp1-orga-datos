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
#include "DataAccess.h"
#include <string>
#include <vector>
#include "Criptografía/RSA/RSA.h"

using namespace std;

class Votante : public Grabable {
private:
	long _id;
	int _dni;
	string _nombreYApellido;
	string _clave;
	string _domicilio;

	Distrito* _distrito;
	vector<Eleccion *> _elecciones;


public:
	Votante();
	Votante(int dni, string nombreYApellido, string clave, string domicilio, Distrito distrito);
	virtual ~Votante();

	Votante(const Votante &votante);

	//Getters
	long getId();
	int getDNI();
	string getNombreYApellido();
	string getClave();
	string getDomicilio();
	Distrito & getDistrito();
	vector<Eleccion *> getElecciones();	// Agregado por martin. Devuelve copias de las elecciones del votante. (Liberar memoria desde donde se llame).

	//Setters
	void setId(long id){this->_id=id;}
	bool cambiarClave(string claveAnterior, string claveNueva);
	void setDistrito(Distrito distrito);
	void setDomicilio(string nuevo_domicilio);

	void agregarEleccion(Eleccion eleccion);
	void vaciarVectorElecciones();

	//Interface de Guardable
	unsigned long int Guardar(ofstream & ofs);
	bool Leer(ifstream & ifs, unsigned long int offset);
	int getTamanioEnDisco();
	void Imprimir();

	inline string getURLArchivoDatos();

	//Metodos interfaz Logueable
	string getClassName();
};

#endif /* VOTANTE_H_ */
