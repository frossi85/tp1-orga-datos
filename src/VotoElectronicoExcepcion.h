/*
 * VotoElectronicoExcepcion.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef VOTOELECTRONICOEXCEPCION_H_
#define VOTOELECTRONICOEXCEPCION_H_

#include <string>
#include <exception>

using namespace std;

class VotoElectronicoExcepcion : public exception{
private:
	string mensajePersonalizado;
public:
	VotoElectronicoExcepcion(string mensaje) throw();
	virtual ~VotoElectronicoExcepcion() throw();

	virtual const char* what() const throw()
	{
		string mensaje("VotoElectronicoExcepcion: ");
		mensaje+= this->mensajePersonalizado;

		return mensaje.c_str();
	}
};

#endif /* VOTOELECTRONICOEXCEPCION_H_ */
