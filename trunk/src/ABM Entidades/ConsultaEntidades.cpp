/*
 * ConsultaEntidades.cpp
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */

#include "ConsultaEntidades.h"


ConsultaEntidades::ConsultaEntidades() {}


ConsultaEntidades::~ConsultaEntidades() {}

/* Se debe pasar la clave como un solo string concatenado con "$" si es de varias palabras, y con la fecha indexada */
/* IMPORTANTE: SI LA CLAVE TIENE UNA FECHA, PRIMERO PASAR LA FECHA A FORMATO INDEXADO (METODO EN UTILIDADES) */

/*
 * Formato de las Claves (todas strings):
 *
 * Aclaraciones:
 * 1 - Cuando se guarda una clave en el hash o arbol, antes se hace Utilidaes::formatearClave(clave)
 * para reemplazar los espacios por '&'.
 *
 * 2 - Para las claves con fechas, tambien antes de guardarlas se le hace a la fecha Utilidades::indexarFecha(fecha)
 * para llevarla al formato aaaammdd (la fecha original ingresada por el admin debe ser del formato ddmmaaaa o dd/mm/aaaa. No es
 * valido un formato d/m/aaaa, es decir, debe completarse con ceros si es menor a 10.
 *
 * 3 - Tambien cuando una clave es compuesta, se concatenan los strings con '$'.
 *
 * Ejemplo ilustrativo: el admin habia insertado una lista con fecha "20/10/2011", cargo "Diputado Cordoba", nombre "UCR".
 * El ABMentidades::altaLista inserta la clave en la forma "20111020$Diputado&Cordoba$UCR".
 * De esta ultima forma es como se debe pasar la clave a ConsultaEntidades::ObtenerRegistro.
 *
 * Distrito: "nombre_distrito" | Ejemplo: "Lanus"
 *
 * Cargo: "nombre_cargo" | Ejemplo: "Intendente&Lanus"
 *
 * Eleccion: "fecha$cargo" | Ejemplo: "20111020$Intendente&Lanus"
 *
 * Lista: "fecha$cargo$nombreLista" | Ejemplo: "20111020$Intendente&Lanus$UCR"
 *
 * Votante: "DNI" | Ejemplo: "34094150"
 *
 * Candidato: "fecha$cargo$nombreLista$DNI" | Ejemplo: "20111020$Intendente&Lanus$UCR$34094150"
 *
 */



/* No usar este metodo para recuperar Conteos */
bool ConsultaEntidades::ObtenerRegistro(string clave, Grabable &aSobreescribir) {
	long int offsetArbol = 0;
	unsigned long int IDobtenido;

	/* Formatea la clave (no indexa fecha!) */
	Utilidades::formatearClave(clave);

	/* Obtiene las rutas de los hash o arboles */
	bool esHash = this->getURLs(aSobreescribir.getClassName());


	/* Busco el id del registro en el primer hash (si es hash) */
	if(esHash) {
		this->hash = new hash_extensible(this->URL_hash_regs,this->URL_hash_bloq_lib,this->URL_hash_tabla);
		RegistroIndice aBuscar(clave,0);
		RegistroIndice *returnReg = this->hash->buscar(&aBuscar);
		delete this->hash;
		this->hash = NULL;
		if (returnReg == NULL) return false;					// No se encontro el registro
		else IDobtenido = returnReg->getOffset();
	}

	/* Busco el id del registro en el arbol (si no es hash) */
	else {
		this->arbol = new ArbolBMas();
		this->arbol->abrir(this->URL_arbol);
		bool encontrado = this->arbol->buscar(clave,offsetArbol);
		this->arbol->cerrar();
		delete this->arbol;
		this->arbol = NULL;
		if (!encontrado) return false;		// No se encontro el registro
		else IDobtenido = offsetArbol;
	}

	/* Busco el offset del id obtenido */
	this->hash = new hash_extensible(this->URL_idhash_regs,this->URL_idhash_bloq_lib,this->URL_idhash_tabla);
	RegistroIndice aBuscarID(Utilidades::toString(IDobtenido),0);
	RegistroIndice *returnRegID = this->hash->buscar(&aBuscarID);
	delete this->hash;
	if (returnRegID == NULL) throw VotoElectronicoExcepcion("No se encontro el id de " + aSobreescribir.getClassName());
	unsigned long int offset = returnRegID->getOffset();

	/* Recupero el registro del archivo de datos */
	this->dataAccess.Leer(aSobreescribir,offset);
	return true;
}


/* Devuelve un booleano de control. Si devuelve true, es un hash, si devuelve false, es un arbol */
bool ConsultaEntidades::getURLs(string classname) {
	if (classname == "Distrito") {
		this->URL_hash_regs = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_DISTRITO_REGS);
		this->URL_hash_bloq_lib = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_DISTRITO_BLOQ_LIB);
		this->URL_hash_tabla = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_DISTRITO_TABLA);
		this->URL_idhash_regs = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDDISTRITO_REGS);
		this->URL_idhash_bloq_lib = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDDISTRITO_BLOQ_LIB);
		this->URL_idhash_tabla = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDDISTRITO_TABLA);
		return true;
	}
	if (classname == "Cargo") {

		this->URL_hash_regs = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_CARGO_REGS);
		this->URL_hash_bloq_lib = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_CARGO_BLOQ_LIB);
		this->URL_hash_tabla = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_CARGO_TABLA);
		this->URL_idhash_regs = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDCARGO_REGS);
		this->URL_idhash_bloq_lib = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDCARGO_BLOQ_LIB);
		this->URL_idhash_tabla = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDCARGO_TABLA);
		return true;
	}
	if (classname == "Votante") {
		this->URL_hash_regs = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_VOTANTE_REGS);
		this->URL_hash_bloq_lib = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_VOTANTE_BLOQ_LIB);
		this->URL_hash_tabla = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_VOTANTE_TABLA);
		this->URL_idhash_regs = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDVOTANTE_REGS);
		this->URL_idhash_bloq_lib = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDVOTANTE_BLOQ_LIB);
		this->URL_idhash_tabla = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDVOTANTE_TABLA);
		return true;
	}
	if (classname == "Eleccion") {
		this->URL_arbol = Configuracion::getConfig()->getValorPorPrefijo(RUTA_ARBOL_ELECCION);
		this->URL_idhash_regs = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDELECCION_REGS);
		this->URL_idhash_bloq_lib = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDELECCION_BLOQ_LIB);
		this->URL_idhash_tabla = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDELECCION_TABLA);
		return false;
	}
	if (classname == "Lista") {
		this->URL_arbol = Configuracion::getConfig()->getValorPorPrefijo(RUTA_ARBOL_LISTA);
		this->URL_idhash_regs = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDLISTA_REGS);
		this->URL_idhash_bloq_lib = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDLISTA_BLOQ_LIB);
		this->URL_idhash_tabla = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDLISTA_TABLA);
		return false;
	}
	if (classname == "Candidato") {
		this->URL_arbol = Configuracion::getConfig()->getValorPorPrefijo(RUTA_ARBOL_CANDIDATO);
		this->URL_idhash_regs = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDCANDIDATO_REGS);
		this->URL_idhash_bloq_lib = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDCANDIDATO_BLOQ_LIB);
		this->URL_idhash_tabla = Configuracion::getConfig()->getValorPorPrefijo(RUTA_HASH_IDCANDIDATO_TABLA);
		return false;
	}
	throw VotoElectronicoExcepcion("El registro pasado no pertenece a ninguna entidad (no usar este metodo para buscar Conteos)");
}
