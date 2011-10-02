#include "RegistroIndice.h"

RegistroIndice::RegistroIndice(string clave, unsigned int offset){
	this->clave = clave;
	this->offset = offset;
}

////////////////

string RegistroIndice::getClave(){
	return this->clave;
}

////////////////

unsigned int RegistroIndice::getOffset(){
	return this->offset;
}

//////////////

void RegistroIndice::setOffset(unsigned int offset){
	this->offset = offset;
}

/////////////

unsigned int RegistroIndice::getTamanioEnDisco(){
	/* NOTA: lo que se guarda tiene esta forma:
	 * (long_total)(long_Clave)ClaveOffset
	 */
	unsigned int tamanioLongitudClave = sizeof(this->getClave().size());
	unsigned int tamanioClave = this->getClave().size() * sizeof(char);
	unsigned int tamanioOffset = sizeof(this->getOffset());
	unsigned int tamanioTotal = sizeof(tamanioTotal) + tamanioLongitudClave + tamanioClave + tamanioOffset;

	return tamanioTotal; //en bytes
}
