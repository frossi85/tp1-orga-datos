/*
 * RegistroArbol.cpp
 *
 *  Created on: 02/10/2011
 *      Author: martin
 */

#include "RegistroArbol.h"

RegistroArbol::RegistroArbol() {
	this->clave = "";
	this->offset = 0;
	this->link_ = 0;
}

RegistroArbol::RegistroArbol(std::string clave, long offset) {
	this->clave = clave;
	this->offset = offset;
	this->link_ = 0;
}

RegistroArbol::RegistroArbol(RegistroArbol & registro)
{
    	this->clave = registro.clave;
	this->offset = registro.offset;
	this->link_ = registro.link_;
}

RegistroArbol::~RegistroArbol() {
	// TODO Auto-generated destructor stub
}

string RegistroArbol::getClave() {
	return this->clave;
}

long RegistroArbol::getOffset() {
	return this->offset;
}

void RegistroArbol::setClave(string clave)
{
	this->clave = clave;
}

void RegistroArbol::setOffset(long offset)
{
	this->offset = offset;
}

long RegistroArbol::getTamanioEnDisco() {
	/* NOTA: lo que se guarda tiene esta forma:
	 * ClaveOffset
	 */
	long tamanioClave = clave.size() * sizeof(char);
	long tamanioOffset = sizeof(offset);
	long tamanioTotal = sizeof(tamanioTotal) + tamanioClave + tamanioOffset;

	return tamanioTotal; //en bytes
}

RegistroArbol * RegistroArbol::Leer(fstream & ifs) {
	long tamanioEnDisco;
	string claveAux;
	long offsetAux;
        long linkAux;
	//ifs.read(reinterpret_cast<char *>(&tamanioEnDisco), sizeof(tamanioEnDisco));
	//claveAux = Utilidades::stringFromFile(ifs);
	//ifs.read(reinterpret_cast<char *>(&offsetAux), sizeof(offsetAux));
        //ifs.read(reinterpret_cast<char *>(&linkAux), sizeof(linkAux));
	
	char delimitador;
	ifs>>tamanioEnDisco>>delimitador;
	claveAux = Utilidades::stringFromFile(ifs);
	ifs>>offsetAux>>delimitador;
        ifs>>linkAux>>delimitador>>delimitador;

        RegistroArbol * registro = new RegistroArbol(claveAux, offsetAux);
        registro->link_ = linkAux;

	return registro;
}
void RegistroArbol::Guardar(fstream & ofs) {
	//long tamanioEnDisco = getTamanioEnDisco();
	//ofs.write(reinterpret_cast<char *>(&tamanioEnDisco), sizeof(tamanioEnDisco));
	//Utilidades::stringToFile(clave, ofs);
	//ofs.write(reinterpret_cast<char *>(&offset), sizeof(offset));
        //ofs.write(reinterpret_cast<char *>(&link_), sizeof(link_));
	
	long tamanioEnDisco = getTamanioEnDisco();
	ofs<<tamanioEnDisco<<"|";
	ofs<<clave<<"|";
	ofs<<offset<<"|";
        ofs<<link_<<"||";
}

void RegistroArbol::Imprimir(){

    cout << "(" << getTamanioEnDisco() << "|" << clave << "|" << offset << "|" << link_<< ")";
}

