/*
 * VotoElectronicoExcepcion.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "VotoElectronicoExcepcion.h"

VotoElectronicoExcepcion::VotoElectronicoExcepcion(string mensaje) throw() {
	this->mensajePersonalizado = mensaje;
}

VotoElectronicoExcepcion::~VotoElectronicoExcepcion() throw() {
	// TODO Auto-generated destructor stub

}
