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

#define RUTA_VOTANTES "<ruta_votantes>"
#define RUTA_DISTRITOS "<ruta_distritos>"
#define RUTA_ELECCION "<ruta_eleccion>"
#define RUTA_LISTA "<ruta_lista>"
#define RUTA_CONTEO "<ruta_conteo>"
#define RUTA_CANDIDATO "<ruta_candidato>"
#define RUTA_CARGO "<ruta_cargo>"
#define RUTA_ADMINISTRADOR "<ruta_administrador>"

#define CANT_CONF 8

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

		static Configuracion *getConfig();
        ~Configuracion();
        string getValorPorPrefijo(string prefijo);
};

#endif /* CONFIGURACION_H_ */

