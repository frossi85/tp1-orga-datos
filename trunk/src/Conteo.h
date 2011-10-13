/*
 * Conteo.h
 *
 *  Created on: 24/09/2011
 *      Author: facundo
 */


#ifndef CONTEO_H_
#define CONTEO_H_

#include <string>
#include "Grabable.h"
#include "Lista.h"
#include "Logueable.h"
#include "Distrito.h"
#include "Eleccion.h"
#include "Configuracion.h"
#include "hash_extensible.h"


using namespace std;

class Conteo : public Grabable {
private:
	Distrito& _distrito;
	Lista& _lista;
	Eleccion& _eleccion;
	long int cantidad;

public:
	//Las referencias deben ser inicializadas si o si en el constructor mediante listas de
	//inicializacion como en el ejemplo de abajo
	Conteo(Eleccion& eleccion, Lista& lista, Distrito& distrito);
	virtual ~Conteo();

	void incrementar();
	long getVotos();
	Lista* getLista();
	Distrito* getDistrito();


	//Falte Implementar
	unsigned long int Guardar(ofstream & ofs);

	//Falta Implementar
	void Leer(ifstream & ifs, unsigned long int offset);

	//Falta Implementar
	string getURLArchivoDatos();

	string getClassName();

};

#endif /* CONTEO_H_ */
