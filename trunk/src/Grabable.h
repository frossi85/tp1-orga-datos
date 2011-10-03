/*
 * Grabable.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef GRABABLE_H_
#define GRABABLE_H_

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Grabable {
private:
	//string _stringId;// = "Falta Implementar";
public:
	virtual void Crear(ofstream & ofs) = 0;
	//virtual void Modificar() = 0;
	//virtual void Borrar() = 0;
	virtual void Leer(ifstream & ifs) = 0;

	//Esta funcion tiene adentro harcodeado un string
	//virtual void setURLBaseDatos(string url) = 0;


	//Lo de abajo seria una interface Comparable
	//bool operator ==(const Grabable &obj) const;
};

#endif /* GRABABLE_H_ */
