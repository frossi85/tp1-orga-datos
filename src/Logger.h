/*
 * Logger.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef LOGGER_H_
#define LOGGER_H_
#include "Logueable.h"

#include "Logueable.h"

class Logger {
public:
	Logger();
	virtual ~Logger();
	static void Alta(Logueable obj);
	static void Modificacion(Logueable obj);
	static void Baja(Logueable obj);
};

#endif /* LOGGER_H_ */
