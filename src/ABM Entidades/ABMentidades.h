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
#include "../ArbolBMas.h"
#include "../Eleccion.h"
#include "../Distrito.h"
#include "../Cargo.h"
#include "../Votante.h"
#include "../Lista.h"
#include "../Candidato.h"
#include "../Conteo.h"
#include "../RegistroIndice.h"
#include "../ManejoIDs.h"
#include "../Utilidades.h"
#include "../Administrador.h"
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
	bool altaAdministrador(Administrador &administrador);
	void agregarVoto(Lista &lista, Distrito &distrito);

    bool modificacionEleccion(Eleccion &eleccion);
	bool modificacionDistrito(Distrito &distrito);
	bool modificacionCargo(Cargo &cargo);
	bool modificacionVotante(Votante &votante);
	bool modificacionLista(Lista &lista);
	bool modificacionCandidato(Candidato &candidato);
	bool modificacionAdministrador(Administrador &administrador);

    bool bajaEleccion(Eleccion &eleccion);
    bool bajaEleccion(string claveEleccion);
    bool bajaDistrito(Distrito &distrito);
	bool bajaDistrito(string claveDistrito);
	bool bajaCargo(Cargo &cargo);
    bool bajaCargo(string claveCargo);
	bool bajaVotante(Votante &votante);
    bool bajaVotante(string claveVotante);
	bool bajaLista(Lista &lista);
    bool bajaLista(string claveLista);
	bool bajaCandidato(Candidato &candidato);
    bool bajaCandidato(string claveCandidato);
	bool bajaAdministrador(Administrador &administrador);

private:
	DataAccess dataAccess;
	hash_extensible* hash;
	ArbolBMas* arbol;

	void crearConteo(Lista &lista);

};

#endif /* ABMENTIDADES_H_ */
