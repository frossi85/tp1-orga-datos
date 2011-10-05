/*
 * RegistroArbol.cpp
 *
 *  Created on: 02/10/2011
 *      Author: martin
 */

#include "RegistroArbol.h"

RegistroArbol::RegistroArbol(string clave, unsigned int offset) {
	this->clave = clave;
	this->offset = offset;
}

RegistroArbol::~RegistroArbol() {
	// TODO Auto-generated destructor stub
}

string RegistroArbol::getClave() {
	return this->clave;
}

unsigned int RegistroArbol::getOffset() {
	return this->offset;
}

unsigned int RegistroArbol::getTamanioEnDisco(int longitudStringMax) {
	/* NOTA: lo que se guarda tiene esta forma:
	 * ClaveOffset
	 */
	unsigned int tamanioLongitudClave = sizeof(this->getClave().size());
	unsigned int tamanioClave = this->getClave().size() * sizeof(char);
	unsigned int tamanioOffset = sizeof(this->getOffset());
	unsigned int tamanioTotal = sizeof(tamanioTotal) + tamanioLongitudClave + tamanioClave + tamanioOffset;

	return tamanioTotal; //en bytes
}

void Persistir(fstream *archivo) {

}

RegistroArbol* Leer(fstream *archivo) {

}
