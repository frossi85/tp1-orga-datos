/*
 * ABMentidades.h
 *
 *  Created on: 10/10/2011
 *      Author: martin
 */

#ifndef ABMENTIDADES_H_
#define ABMENTIDADES_H_
#include "../DataAccess.h"
#include "../Configuracion.h"
#include "../hash_extensible.h"
#include "../Eleccion.h"
#include "../Distrito.h"
#include "../Cargo.h"
#include "../Votante.h"
#include "../Lista.h"
#include "../Candidato.h"
#include "../RegistroIndice.h"
#include "../hash_extensible.h"
using namespace std;


class ABMentidades {
public:
	ABMentidades();
	virtual ~ABMentidades();
	bool guardarEleccion(Eleccion &eleccion);
	bool guardarDistrito(Distrito &distrito);
	bool guardarCargo(Cargo &cargo);
	bool guardarVotante(Votante &votante);
	bool guardarLista(Lista &lista);
	bool guardarCandidato(Candidato &candidato);

private:
	DataAccess dataAccess;
	hash_extensible* hash;

};

#endif /* ABMENTIDADES_H_ */
