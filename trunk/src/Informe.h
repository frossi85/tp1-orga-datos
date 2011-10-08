/*
 * Informe.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef INFORME_H_
#define INFORME_H_

#include <string>
#include <vector>
#include "Eleccion.h"
#include "Distrito.h"
#include "Lista.h"
#include "Conteo.h"

using namespace std;

class Informe {
public:
	Informe(Eleccion& eleccion);
	long mostrar_Conteos_por_Distrito(vector<Conteo *> conteos);

	Informe(Distrito& distrito);
	Informe(Lista& lista);


	virtual ~Informe();
};

#endif /* INFORME_H_ */
