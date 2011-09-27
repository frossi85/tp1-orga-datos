/*
 * Logger.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "Logueable.h"
#include "Utilidades.h"
#include "VotoElectronicoExcepcion.h"
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

class Logger {
private:
	static const string RUTA_ARCHIVO_VOTAR;
	static void logAccion(Logueable obj, string accion);
public:
	Logger();
	virtual ~Logger();
	static void Alta(Logueable obj);
	static void Modificacion(Logueable obj);
	static void Baja(Logueable obj);

	//Configuracion::getValorPorPrefijo(RUTA_ARCHIVO_VOTAR);
};

#endif /* LOGGER_H_ */
