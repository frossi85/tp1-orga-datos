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
#include "DataAccess.h"


using namespace std;

class Conteo : public Grabable {
private:
	Distrito *_distrito;
	Lista *_lista;
	Eleccion *_eleccion;
	long int _cantidad;

public:
	//Las referencias deben ser inicializadas si o si en el constructor mediante listas de
	//inicializacion como en el ejemplo de abajo
	Conteo(Lista& lista, Distrito& distrito);
	Conteo(const Conteo &conteo);
        Conteo();
	virtual ~Conteo();
	void incrementar();
	long getVotos();
	Lista& getLista();
	Distrito& getDistrito();

	unsigned long int Guardar(ofstream & ofs);

	void Leer(ifstream & ifs, unsigned long int offset);

	string getURLArchivoDatos();

	string getClassName();

	static void AgregarVoto(Lista& lista, Distrito& distrito);

        void Imprimir();
};

#endif /* CONTEO_H_ */
