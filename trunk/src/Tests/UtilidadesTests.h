/*
 * UtilidadesTests.h
 *
 *  Created on: 14/10/2011
 *      Author: martin
 */

#ifndef UTILIDADESTESTS_H_
#define UTILIDADESTESTS_H_

#include "../Distrito.h"
#include "../Cargo.h"
#include "../Eleccion.h"
#include "../Lista.h"
#include "../Votante.h"
#include "../Candidato.h"
#include "../Conteo.h"
#include "../Administrador.h"
#include <vector>

class UtilidadesTests {
public:
	UtilidadesTests();
	virtual ~UtilidadesTests();

	static void cargarDistritos(vector<Distrito> &vecDistritos);
	static void cargarCargos(vector<Cargo> &vecCargos);
	static void cargarElecciones(vector<Eleccion> &vecElecciones, vector<Cargo> &vecCargos, vector<Distrito> &vecDistritos);
	static void cargarListas(vector<Lista> &vecListas, vector<Eleccion> &vecElecciones);
	static void cargarVotantes(vector<Votante> &vecVotantes, vector<Distrito> &vecDistritos, vector<Eleccion> &vecElecciones);
	static void cargarCandidatos(vector<Candidato> &vecCandidatos, vector<Lista> &vecListas, vector<Votante> &vecVotantes);
    static void cargarConteos(vector<Conteo> &vecConteos, vector<Lista> &vecListas, vector<Distrito> &vecDistritos);
    static void cargarAdministradores(vector<Administrador> &vecAdministradores);
};

#endif /* UTILIDADESTESTS_H_ */
