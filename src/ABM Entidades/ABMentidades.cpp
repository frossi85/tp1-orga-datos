/*
 * ABMentidades.cpp
 *
 *  Created on: 10/10/2011
 *      Author: martin
 */

#include "ABMentidades.h"

ABMentidades::ABMentidades() {
//	this->dataAccess();
}

ABMentidades::~ABMentidades() {}

bool ABMentidades::guardarEleccion(Eleccion &eleccion) {
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_eleccion_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_eleccion_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_eleccion_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	//RegistroIndice aAgregar(eleccion)
	
	
	delete this->hash;
	return false;
}

bool ABMentidades::guardarDistrito(Distrito &distrito) {
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregar(distrito.getNombre(),0);
	RegistroIndice *returnReg = hash->buscar(&aAgregar);
	if (returnReg == NULL) return false;
	//distrito.setId()
	//this->dataAccess.Guardar()


	delete this->hash;
	return false;
}


bool ABMentidades::guardarCargo(Cargo &cargo) {
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_cargo_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_cargo_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_cargo_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);



	delete this->hash;
	return false;
}


bool ABMentidades::guardarVotante(Votante &votante) {
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_votante_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_votante_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_votante_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);



	delete this->hash;
	return false;
}


bool ABMentidades::guardarLista(Lista &lista) {
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_lista_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_lista_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_lista_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

	delete this->hash;
	return false;
}


bool ABMentidades::guardarCandidato(Candidato &candidato) {
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_candidato_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_candidato_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_candidato_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);


	delete this->hash;
	return false;
}
