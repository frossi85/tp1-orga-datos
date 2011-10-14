/*
 * ConsultaEntidades.h
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */

#ifndef CONSULTAENTIDADES_H_
#define CONSULTAENTIDADES_H_

#include "../Grabable.h"
#include "../hash_extensible.h"
#include "../DataAccess.h"
#include "../RegistroIndice.h"

using namespace std;

class ConsultaEntidades {
public:
	ConsultaEntidades();
	virtual ~ConsultaEntidades();

	bool ObtenerRegistro(string clave, Grabable &aGuardar);

private:
	string URL_hash_regs;
	string URL_hash_bloq_lib;
	string URL_hash_tabla;
	string URL_idhash_regs;
	string URL_idhash_bloq_lib;
	string URL_idhash_tabla;

	DataAccess dataAccess;
	hash_extensible *hash;

	void getURLs(string classname);
};

#endif /* CONSULTAENTIDADES_H_ */
