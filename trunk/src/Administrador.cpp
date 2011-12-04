/*
 * Administrador.cpp
 *
 *  Created on: 26/11/2011
 *      Author: martin
 */

#include "Administrador.h"

Administrador::Administrador() {
	this->usuario = "";
	this->clave = "";
}


Administrador::Administrador(string usuario, string clave) {
	this->usuario = usuario;
	this->clave = clave;
}


Administrador::Administrador(const Administrador &admin) {
	this->usuario = admin.usuario;
	this->clave = admin.clave;
}


Administrador::~Administrador() {}


string Administrador::getUsuario() { return this->usuario; }


string Administrador::getClave() { return this->clave; }


void Administrador::Imprimir() {
	cout<<"Usuario: " << this->usuario << endl;
	cout<<"Clave: " << this->clave << endl;
}


int Administrador::getTamanioEnDisco() {

	int tamanio = 0;

	int size_usuario = this->usuario.size();
	int size_clave = this->clave.size();

	tamanio+=sizeof(size_usuario);
	tamanio+=sizeof(char)*size_usuario;
	tamanio+=sizeof(size_clave);
	tamanio+=sizeof(char)*size_clave;

	return tamanio;
}


bool Administrador::Leer(ifstream & ifs, unsigned long int offset) {

	// Me posiciono en el archivo
	ifs.seekg(offset,ios::beg);

	//Comienzo lectura de atributos
	//usuario = Utilidades::stringFromFile(ifs);
	//clave = Utilidades::stringFromFile(ifs);

        Clave publica = Clave(34333445, 100160063);
	Clave privada = Clave(10013, 100160063);

        RSA rsa(privada, publica);

        //lectura de los atributos
        usuario = rsa.desencriptar(Utilidades::stringFromFile(ifs));
        clave = rsa.desencriptar(Utilidades::stringFromFile(ifs));

	return true;
}


unsigned long int Administrador::Guardar(ofstream & ofs) {

	unsigned long int offset = ofs.tellp();

        Clave publica = Clave(34333445, 100160063);
	Clave privada = Clave(10013, 100160063);

	RSA rsa(privada, publica);

	// Comienzo escritura de atributos
	//Utilidades::stringToFile(usuario, ofs);
	//Utilidades::stringToFile(clave, ofs);

        //Para encriptar
	string usuario = rsa.encriptar(this->usuario);
	string clave = rsa.encriptar(this->clave);

	Utilidades::stringToFile(usuario, ofs);
	Utilidades::stringToFile(clave, ofs);


	return offset;
}


inline string Administrador::getURLArchivoDatos() {
	return (*Configuracion::getConfig()).getValorPorPrefijo(Configuracion::URL_ADMINISTRADOR);
}


string Administrador::getClassName() {
	return "Administrador";
}
