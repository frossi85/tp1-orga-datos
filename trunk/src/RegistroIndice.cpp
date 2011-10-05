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
	unsigned int tamanioLongitudClave = sizeof(tamanioLongitudClave);
	unsigned int tamanioClave = (this->getClave().size()) * sizeof(char);
	unsigned int tamanioOffset = sizeof(this->getOffset());
	unsigned int tamanioTotal = sizeof(tamanioTotal) + tamanioLongitudClave + tamanioClave + tamanioOffset;

	return tamanioTotal; //en bytes
}

////////////////

void RegistroIndice::Persistir(fstream *archivo){

	unsigned int tamTotal = this->getTamanioEnDisco();
	archivo->write((char*)&tamTotal, sizeof(tamTotal));

    std::string clave = this->getClave();
	unsigned int longClave = clave.size();

	archivo->write((char *)&longClave, sizeof(longClave));
	archivo->write(clave.c_str(), sizeof(char) * longClave);

	unsigned int offset = this->getOffset();
	archivo->write((char*)&offset, sizeof(offset));
}

/////////////////

RegistroIndice* RegistroIndice::Leer(fstream *archivo){

	unsigned int longTotal;
	archivo->read((char*)&longTotal, sizeof(longTotal));

    unsigned int longClave = 0;
	archivo->read((char *)&longClave, sizeof(longClave));

	char aux[longClave+1];
	archivo->read(aux, sizeof(char) * longClave);
	string clave(aux);

	unsigned int offset;
	archivo->read((char*)&offset, sizeof(offset));

	return new RegistroIndice(clave, offset);
}

//////////////////

void RegistroIndice::Imprimir(fstream *archImpresion){

    *archImpresion << "(" << this->getClave() << " | " << this->getOffset() << ")";
}
