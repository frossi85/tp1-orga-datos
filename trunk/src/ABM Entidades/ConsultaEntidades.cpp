/*
 * ConsultaEntidades.cpp
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */

#include "ConsultaEntidades.h"


ConsultaEntidades::ConsultaEntidades() {}


ConsultaEntidades::~ConsultaEntidades() {}

/* Se debe pasar la clave como un solo string concatenado con "$" si es de varias palabras */
/* IMPORTANTE: SI LA CLAVE TIENE UNA FECHA, PRIMERO PASAR LA FECHA A FORMATO INDEXADO (METODO EN UTILIDADES)*/
bool ConsultaEntidades::ObtenerRegistro(string clave, Grabable &aGuardar) {
	/* Obtiene las rutas de los hash */
	this->getURLs(aGuardar.getClassName());

	/* Busco el id del registro en el primer hash */
	this->hash = new hash_extensible(this->URL_hash_regs,this->URL_hash_bloq_lib,this->URL_hash_tabla);
	RegistroIndice aBuscar(clave,0);
	RegistroIndice *returnReg = this->hash->buscar(&aBuscar);
	if (returnReg == NULL) {
		delete this->hash;
		return false;			// No se encontro el registro
	}
	delete this->hash;

	/* Busco el offset del id obtenido */
	this->hash = new hash_extensible(this->URL_idhash_regs,this->URL_idhash_bloq_lib,this->URL_idhash_tabla);
	RegistroIndice aBuscarID(Utilidades::toString(returnReg->getOffset()),0);
	returnReg = this->hash->buscar(&aBuscarID);
	if (returnReg == NULL) {
		delete this->hash;
		return false;			// No se encontro el id...lo que seria un problema..
	}
	unsigned long int offset = returnReg->getOffset();
	delete this->hash;

	/* Recupero el registro del archivo de datos */
	this->dataAccess.Leer(aGuardar,offset);
	return true;
}

void ConsultaEntidades::getURLs(string classname) {
	if (classname == "Distrito") {
		this->URL_hash_regs = "<ruta_hash_distrito_regs>";
		this->URL_hash_bloq_lib = "<ruta_hash_distrito_bloq_lib>";
		this->URL_hash_tabla = "<ruta_hash_distrito_tabla>";
		this->URL_idhash_regs = "<ruta_hash_iddistrito_regs>";
		this->URL_idhash_bloq_lib = "<ruta_hash_iddistrito_bloq_lib>";
		this->URL_idhash_tabla = "<ruta_hash_iddistrito_tabla>";
		return;
	}
	if (classname == "Cargo") {
		this->URL_hash_regs = "<ruta_hash_cargo_regs>";
		this->URL_hash_bloq_lib = "<ruta_hash_cargo_bloq_lib>";
		this->URL_hash_tabla = "<ruta_hash_cargo_tabla>";
		this->URL_idhash_regs = "<ruta_hash_idcargo_regs>";
		this->URL_idhash_bloq_lib = "<ruta_hash_idcargo_bloq_lib>";
		this->URL_idhash_tabla = "<ruta_hash_idcargo_tabla>";
		return;
	}
	if (classname == "Votante") {
		this->URL_hash_regs = "<ruta_hash_votante_regs>";
		this->URL_hash_bloq_lib = "<ruta_hash_votante_bloq_lib>";
		this->URL_hash_tabla = "<ruta_hash_votante_tabla>";
		this->URL_idhash_regs = "<ruta_hash_idvotante_regs>";
		this->URL_idhash_bloq_lib = "<ruta_hash_idvotante_bloq_lib>";
		this->URL_idhash_tabla = "<ruta_hash_idvotante_tabla>";
		return;
	}
	if (classname == "Eleccion") {
		this->URL_hash_regs = "<ruta_hash_eleccion_regs>";
		this->URL_hash_bloq_lib = "<ruta_hash_eleccion_bloq_lib>";
		this->URL_hash_tabla = "<ruta_hash_eleccion_tabla>";
		this->URL_idhash_regs = "<ruta_hash_ideleccion_regs>";
		this->URL_idhash_bloq_lib = "<ruta_hash_ideleccion_bloq_lib>";
		this->URL_idhash_tabla = "<ruta_hash_ideleccion_tabla>";
		return;
	}
	if (classname == "Lista") {
		this->URL_hash_regs = "<ruta_hash_lista_regs>";
		this->URL_hash_bloq_lib = "<ruta_hash_lista_bloq_lib>";
		this->URL_hash_tabla = "<ruta_hash_lista_tabla>";
		this->URL_idhash_regs = "<ruta_hash_idlista_regs>";
		this->URL_idhash_bloq_lib = "<ruta_hash_idlista_bloq_lib>";
		this->URL_idhash_tabla = "<ruta_hash_idlista_tabla>";
		return;
	}
	if (classname == "Candidato") {
		this->URL_hash_regs = "<ruta_hash_candidato_regs>";
		this->URL_hash_bloq_lib = "<ruta_hash_candidato_bloq_lib>";
		this->URL_hash_tabla = "<ruta_hash_candidato_tabla>";
		this->URL_idhash_regs = "<ruta_hash_idcandidato_regs>";
		this->URL_idhash_bloq_lib = "<ruta_hash_idcandidato_bloq_lib>";
		this->URL_idhash_tabla = "<ruta_hash_idcandidato_tabla>";
		return;
	}
	return;
}
