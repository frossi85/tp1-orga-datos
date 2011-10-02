#include "RegistroIndice.h"

RegistroIndice::RegistroIndice(string clave, unsigned int offset){
	this->clave = clave;
	this->offset = offset;
}

string RegistroIndice::getClave(){
	return this->clave;
}

unsigned int RegistroIndice::getOffset(){
	return this->offset;
}

void RegistroIndice::setOffset(unsigned int offset){
	this->offset = offset;
}
