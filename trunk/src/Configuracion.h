/*
 * Configuracion.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

class Configuracion {
public:
	Configuracion();
	virtual ~Configuracion();
	string getValorPorPrefijo(string prefijo);
};

#endif /* CONFIGURACION_H_ */
