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
#include "../ManejoIDs.h"
using namespace std;


class ABMentidades {
public:
	ABMentidades();
	virtual ~ABMentidades();
	bool altaEleccion(Eleccion &eleccion);
	bool altaDistrito(Distrito &distrito);
	bool altaCargo(Cargo &cargo);
	bool altaVotante(Votante &votante);
	bool altaLista(Lista &lista);
	bool altaCandidato(Candidato &candidato);

private:
	DataAccess dataAccess;
	hash_extensible* hash;

};

#endif /* ABMENTIDADES_H_ */
