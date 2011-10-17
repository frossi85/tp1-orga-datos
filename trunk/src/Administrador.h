/*
 * Administrador.h
 *
 *  Created on: 17/10/2011
 *      Author: facundo
 */

#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_

#include "Grabable.h"
#include "Logueable.h"
#include <string>

using namespace std;

class Administrador : public Grabable  {
public:
	Administrador();
	virtual ~Administrador();

	//Interface de Guardable
	unsigned long int Guardar(ofstream & ofs);
	void Leer(ifstream & ifs, unsigned long int offset);
	void Imprimir();

	inline string getURLArchivoDatos();

	//Metodos interfaz Logueable
	string getClassName();
};

#endif /* ADMINISTRADOR_H_ */
