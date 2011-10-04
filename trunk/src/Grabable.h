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
#include "Logueable.h"

using namespace std;

class Grabable : public Logueable {
private:
	//string _stringId;// = "Falta Implementar";
public:
	virtual void Guardar(ofstream & ofs) = 0;
	//virtual void Modificar() = 0;
	//virtual void Eliminar() = 0;
	virtual void Leer(ifstream & ifs) = 0;


	virtual string getURLArchivoDatos() = 0;

	//Es la interface Loggueable q heredo
	virtual string getClassName() = 0;
	//Lo de abajo seria una interface Comparable

	//bool operator ==(const Grabable &obj) const;
};

#endif /* GRABABLE_H_ */
