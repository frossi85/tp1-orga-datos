/*
 * Grabable.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef GRABABLE_H_
#define GRABABLE_H_

#include <string>

using namespace std;

class Grabable {
private:
	string _stringId;// = "Falta Implementar";
public:
	Grabable();
	virtual ~Grabable();

	void Crear();
	void Modificar();
	void Borrar();

	bool operator ==(const Grabable &obj) const;
};

#endif /* GRABABLE_H_ */
