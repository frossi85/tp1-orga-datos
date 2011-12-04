/*
 * Administrador.h
 *
 *  Created on: 26/11/2011
 *      Author: martin
 */

#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_

#include "Grabable.h"
#include "Logueable.h"
#include "Utilidades.h"
#include "Configuracion.h"
#include "Criptografía/RSA/RSA.h"
#include <string>

using namespace std;

class Administrador : public Grabable  {
public:
	Administrador();
	Administrador(string usuario, string clave);
	virtual ~Administrador();
	Administrador(const Administrador &admin);

	unsigned long int Guardar(ofstream & ofs);
	bool Leer(ifstream & ifs, unsigned long int offset);

	string getUsuario();
	string getClave();
	void Imprimir();
	int getTamanioEnDisco();
	string getClassName();
	inline string getURLArchivoDatos();

private:
	string usuario;
	string clave;
};

#endif /* ADMINISTRADOR_H_ */
