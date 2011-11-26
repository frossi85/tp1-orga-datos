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
#include "../Administrador.h"
#include "../RegistroIndice.h"
#include "../ManejoIDs.h"
#include "../Utilidades.h"
#include "../Logger.h"
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
	bool altaAdministrador(Administrador &admin);
	void agregarVoto(Votante &votante, Lista &lista, Distrito &distrito);


    bool modificacionEleccion(Eleccion &eleccion);
	bool modificacionDistrito(Distrito &distrito);
	bool modificacionCargo(Cargo &cargo);
	bool modificacionVotante(Votante &votante);
	bool modificacionLista(Lista &lista);

    bool bajaEleccion(Eleccion &eleccion);
    bool bajaDistrito(Distrito &distrito);
    bool bajaCargo(Cargo &cargo);
	bool bajaVotante(Votante &votante);
	bool bajaLista(Lista &lista);
	bool bajaCandidato(Candidato &candidato);
	bool bajaAdministrador(Administrador &admin);

private:
	DataAccess dataAccess;
	hash_extensible* hash;
	ArbolBMas* arbol;

	void crearConteo(Lista &lista);
	bool bajaEleccion(string claveEleccion);
	bool bajaDistrito(string claveDistrito);
	bool bajaCargo(string claveCargo);
	bool bajaVotante(string claveVotante);
	bool bajaLista(string claveLista);
	bool bajaCandidato(string claveCandidato);
	bool bajaAdministrador(string claveAdmin);
};

#endif /* ABMENTIDADES_H_ */
