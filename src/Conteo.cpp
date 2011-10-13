/*
 * Conteo.cpp
 *
 *  Created on: 24/09/2011
 *      Author: facundo
 */

#include "Conteo.h"

Conteo::Conteo(Eleccion& eleccion, Lista& lista, Distrito& distrito) : _lista(lista), _distrito(distrito), _eleccion(eleccion){
	this->cantidad = 0;
}

Conteo::~Conteo() {
	// TODO Auto-generated destructor stub
}

void Conteo::incrementar()
{
	this->cantidad++;
}

long Conteo::getVotos(){

	return cantidad;
}

Lista* Conteo::getLista(){

	return &this->_lista;

}

Distrito* Conteo::getDistrito(){

	return &this->_distrito;
}

unsigned long int Conteo::Guardar(ofstream & ofs){

	unsigned long int offset = ofs.tellp();

	//obtengo el ID de la clase conteo como la concatenación de lista$IDeleccion$distrito
	std::stringstream aux;
	aux << this->_lista.getNombre() << "$" << this->_eleccion.getId() << "$" << this->_distrito.getNombre();
	string clave = aux.str();

	// Comienzo escritura de atributos
	Utilidades::stringToFile(clave, ofs);
	ofs.write(reinterpret_cast<char *>(&cantidad), sizeof(cantidad));

	return offset;
}

void Conteo::Leer(ifstream & ifs, unsigned long int offset){

	// Me posiciono en el archivo
	ifs.seekg(offset,ios::beg);

	//Comienzo lectura de atributos
	string clave = Utilidades::stringFromFile(ifs);
	ifs.read(reinterpret_cast<char *>(&cantidad), sizeof(cantidad));

	//Descompongo el string clave en cada una de sus partes
	size_t ocurrencia1 = clave.find_first_of("$");
	string nombreLista = clave.substr(0, ocurrencia1);

	size_t ocurrencia2 = clave.find_last_of("$");
	std::stringstream aux( clave.substr(ocurrencia1 + 1, ocurrencia2) );
	string IDEleccion = aux.str();

	string nombreDistrito = clave.substr(ocurrencia2 + 1);

	//usa lo anterior para recuperar la lista, la eleccion y el distrito

	//recupera lista:

	hash_extensible hashListas(Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_LISTA_REGS),
	Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_LISTA_BLOQ_LIB), Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_LISTA_TABLA));

	RegistroIndice regListaAux(nombreLista, 0);
	RegistroIndice *regLista = hashListas.buscar(&regListaAux);

	//OJO: si no encuentra el registro no va a leer nada
	if(regLista != NULL){
		ifstream archListas(this->_lista.getURLArchivoDatos().c_str(), ios::binary);
		this->_lista.Leer(archListas, regLista->getOffset());
	}

	//recupera eleccion:

	hash_extensible hashIDElecciones(Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_ELECCION_REGS),
	Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_ELECCION_BLOQ_LIB), Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_ELECCION_TABLA));

	RegistroIndice regEleccionAux(IDEleccion, 0);
	RegistroIndice *regEleccion = hashIDElecciones.buscar(&regEleccionAux);

	//OJO: si no encuentra el registro no va a leer nada
	if(regEleccion != NULL){
		ifstream archElecciones(this->_eleccion.getURLArchivoDatos().c_str(), ios::binary);
		this->_eleccion.Leer(archElecciones, regEleccion->getOffset());
	}

	//recupera distrito:

	hash_extensible hashDistritos(Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_DISTRITO_REGS),
	Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_DISTRITO_BLOQ_LIB), Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_DISTRITO_TABLA));

	RegistroIndice regDistritoAux(nombreDistrito, 0);
	RegistroIndice *regDistrito = hashDistritos.buscar(&regDistritoAux);

	//OJO: si no encuentra el registro no va a leer nada
	if(regDistrito != NULL){
		ifstream archDistritos(this->_distrito.getURLArchivoDatos().c_str(), ios::binary);
		this->_distrito.Leer(archDistritos, regDistrito->getOffset());
	}
}

string Conteo::getURLArchivoDatos(){

}

string Conteo::getClassName(){

	return "Conteo";

}


