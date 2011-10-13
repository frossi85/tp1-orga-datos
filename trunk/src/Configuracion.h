/*
 * Configuracion.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 *
 *  caso de uso
 *  
 *  Configuracion *t = Configuracion::getConfig();
  *  cout << t->getValorPorPrefijo(RUTA_VOTANTES);
 *
 */

#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#define RUTA_VOTANTES "<ruta_votante>"
#define RUTA_DISTRITOS "<ruta_distrito>"
#define RUTA_ELECCION "<ruta_eleccion>"
#define RUTA_LISTA "<ruta_lista>"
#define RUTA_CONTEO "<ruta_conteo>"
#define RUTA_CANDIDATO "<ruta_candidato>"
#define RUTA_CARGO "<ruta_cargo>"
#define RUTA_ADMINISTRADOR "<ruta_administrador>"
#define RUTA_IDs "<ruta_IDs>"
#define RUTA_HASH_ELECCION_REGS "<ruta_hash_eleccion_regs>"
#define RUTA_HASH_ELECCION_BLOQ_LIB "<ruta_hash_eleccion_bloq_lib>"
#define RUTA_HASH_ELECCION_TABLA "<ruta_hash_eleccion_tabla>"
#define RUTA_HASH_DISTRITO_REGS "<ruta_hash_distrito_regs>"
#define RUTA_HASH_DISTRITO_BLOQ_LIB "<ruta_hash_distrito_bloq_lib>"
#define RUTA_HASH_DISTRITO_TABLA "<ruta_hash_distrito_tabla>"
#define RUTA_HASH_CARGO_REGS "<ruta_hash_cargo_regs>"
#define RUTA_HASH_CARGO_BLOQ_LIB "<ruta_hash_cargo_bloq_lib>"
#define RUTA_HASH_CARGO_TABLA "<ruta_hash_cargo_tabla>"
#define RUTA_HASH_LISTA_REGS "<ruta_hash_lista_regs>"
#define RUTA_HASH_LISTA_BLOQ_LIB "<ruta_hash_lista_bloq_lib>"
#define RUTA_HASH_LISTA_TABLA "<ruta_hash_lista_tabla>"
#define RUTA_HASH_CANDIDATO_REGS "<ruta_hash_candidato_regs>"
#define RUTA_HASH_CANDIDATO_BLOQ_LIB "<ruta_hash_candidato_bloq_lib>"
#define RUTA_HASH_CANDIDATO_TABLA "<ruta_hash_candidato_tabla>"
#define RUTA_HASH_VOTANTE_REGS "<ruta_hash_votante_regs>"
#define RUTA_HASH_VOTANTE_BLOQ_LIB "<ruta_hash_votante_bloq_lib>"
#define RUTA_HASH_VOTANTE_TABLA "<ruta_hash_votante_tabla>"
#define RUTA_HASH_IDELECCION_REGS "<ruta_hash_ideleccion_regs>"
#define RUTA_HASH_IDELECCION_BLOQ_LIB "<ruta_hash_ideleccion_bloq_lib>"
#define RUTA_HASH_IDELECCION_TABLA "<ruta_hash_ideleccion_tabla>"
#define RUTA_HASH_IDDISTRITO_REGS "<ruta_hash_iddistrito_regs>"
#define RUTA_HASH_IDDISTRITO_BLOQ_LIB "<ruta_hash_iddistrito_bloq_lib>"
#define RUTA_HASH_IDDISTRITO_TABLA "<ruta_hash_iddistrito_tabla>"
#define RUTA_HASH_IDCARGO_REGS "<ruta_hash_idcargo_regs>"
#define RUTA_HASH_IDCARGO_BLOQ_LIB "<ruta_hash_idcargo_bloq_lib>"
#define RUTA_HASH_IDCARGO_TABLA "<ruta_hash_idcargo_tabla>"

#define CANT_CONF 36

#include <string>

using namespace std;

class Configuracion {
private:
		string constantes[CANT_CONF];
		string valores[CANT_CONF];
		Configuracion();
public:
		static const string URL_VOTANTES;
		static const string URL_DISTRITOS;
		static const string URL_ELECCION;
		static const string URL_LISTA;
		static const string URL_CONTEO;
		static const string URL_CANDIDATO;
		static const string URL_CARGO;
		static const string URL_ADMINISTRADOR;
		static const string URL_IDs;

		static Configuracion *getConfig();
        ~Configuracion();
        string getValorPorPrefijo(string prefijo);
};

#endif /* CONFIGURACION_H_ */

