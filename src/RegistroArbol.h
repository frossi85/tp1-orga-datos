/*
 * RegistroArbol.h
 *
 *  Created on: 02/10/2011
 *      Author: martin
 */

#ifndef REGISTROARBOL_H_
#define REGISTROARBOL_H_

#include <string>
#include <fstream>
#include "Utilidades.h"
#include "VotoElectronicoExcepcion.h"

using namespace std;

class RegistroArbol{
public:
	//PARA EJECUTAR PROGRAMAS EN LINUX ESCRIBIR EL COMANDO  ./VotoElectronico

	RegistroArbol();
	RegistroArbol(string clave, long offset);
    RegistroArbol(RegistroArbol & registro);
	virtual ~RegistroArbol();
	string getClave();
	long getOffset();
	void setClave(string offset);
	void setOffset(long offset);
	long getTamanioEnDisco();
	static RegistroArbol * Leer(fstream & archivo);
	void Guardar(fstream & archivo);
	void Imprimir();

	string clave;
	long offset;
	long link_; //Si no me equivoco es el puntero al nodo hoja de la derecha para
	//hacer el barrido secuencial
};


#endif /* REGISTROARBOL_H_ */
