/*
 * ABMentidades.cpp
 *
 *  Created on: 10/10/2011
 *      Author: martin
 */

#include "ABMentidades.h"

ABMentidades::ABMentidades() {}

ABMentidades::~ABMentidades() {}

bool ABMentidades::altaEleccion(Eleccion &eleccion) {
	/* Inicializo el hash */
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_eleccion_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_eleccion_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_eleccion_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	
	/* Busco en el hash si ya existe la eleccion */
	string fecha = Utilidades::indexarFecha(eleccion.getFecha());
	string cargo = eleccion.getCargo().getCargoPrincipal();
	Utilidades::formatearClave(cargo);
	string clave = fecha + "$" + cargo;
	RegistroIndice aAgregar(clave,0);
	RegistroIndice *returnReg = this->hash->buscar(&aAgregar);
	if (returnReg != NULL) return false;					// Ya existia en el hash, no se agrega

	/* Le seteo un id y lo guardo en el archivo de datos */
	eleccion.setId(ManejoIDs::obtenerIDnuevo(eleccion.getClassName()));
	unsigned long int offset = this->dataAccess.Guardar(eleccion);

	/* Guardo en el hash eleccion/id_eleccion */
	aAgregar.setOffset(eleccion.getId());
	this->hash->guardar(&aAgregar);
	delete this->hash;

	/* Guardo en el hash id_eleccion/offset */
	arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_ideleccion_regs>"));
	arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_ideleccion_bloq_lib>"));
	arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_ideleccion_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregarID(Utilidades::toString(eleccion.getId()), offset);
	this->hash->guardar(&aAgregarID);
	delete this->hash;
	return true;
}

bool ABMentidades::altaDistrito(Distrito &distrito) {
	/* Inicializo el hash */
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

	/* Busco en el hash si ya existe el distrito */
	string clave = distrito.getNombre();
	Utilidades::formatearClave(clave);
	RegistroIndice aAgregar(clave,0);
	RegistroIndice *returnReg = this->hash->buscar(&aAgregar);
	if (returnReg != NULL) return false;					// Ya existia en el hash, no se agrega

	/* Le seteo un id y lo guardo en el archivo de datos */
	distrito.setId(ManejoIDs::obtenerIDnuevo(distrito.getClassName()));
	unsigned long int offset = this->dataAccess.Guardar(distrito);

	/* Guardo en el hash distrito/id_distrito */
	aAgregar.setOffset(distrito.getId());
	this->hash->guardar(&aAgregar);
	delete this->hash;

	/* Guardo en el hash id_distrito/offset */
	arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_iddistrito_regs>"));
	arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_iddistrito_bloq_lib>"));
	arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_iddistrito_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregarID(Utilidades::toString(distrito.getId()), offset);
	this->hash->guardar(&aAgregarID);
	delete this->hash;
	return true;
}


bool ABMentidades::altaCargo(Cargo &cargo) {
	/* Inicializo el hash */
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_cargo_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_cargo_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_cargo_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

	/* Busco en el hash si ya existe el cargo */
	string clave = cargo.getCargoPrincipal();
	Utilidades::formatearClave(clave);
	RegistroIndice aAgregar(clave,0);
	RegistroIndice *returnReg = this->hash->buscar(&aAgregar);
	if (returnReg != NULL) return false;					// Ya existia en el hash, no se agrega

	/* Le seteo un id y lo guardo en el archivo de datos */
	cargo.setId(ManejoIDs::obtenerIDnuevo(cargo.getClassName()));
	unsigned long int offset = this->dataAccess.Guardar(cargo);

	/* Guardo en el hash cargo/id_cargo */
	aAgregar.setOffset(cargo.getId());
	this->hash->guardar(&aAgregar);
	delete this->hash;

	/* Guardo en el hash id_cargo/offset */
	arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcargo_regs>"));
	arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcargo_bloq_lib>"));
	arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcargo_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregarID(Utilidades::toString(cargo.getId()), offset);
	this->hash->guardar(&aAgregarID);
	delete this->hash;
	return true;
}


bool ABMentidades::altaVotante(Votante &votante) {
	/* Inicializo el hash */
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_votante_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_votante_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_votante_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

	/* Busco en el hash si ya existe el votante */
	RegistroIndice aAgregar(Utilidades::toString(votante.getDNI()),0);
	RegistroIndice *returnReg = this->hash->buscar(&aAgregar);
	if (returnReg != NULL) return false;					// Ya existia en el hash, no se agrega

	/* Le seteo un id y lo guardo en el archivo de datos */
	votante.setId(ManejoIDs::obtenerIDnuevo(votante.getClassName()));
	unsigned long int offset = this->dataAccess.Guardar(votante);

	/* Guardo en el hash votante/id_votante */
	aAgregar.setOffset(votante.getId());
	this->hash->guardar(&aAgregar);
	delete this->hash;

	/* Guardo en el hash id_votante/offset */
	arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idvotante_regs>"));
	arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idvotante_bloq_lib>"));
	arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idvotante_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregarID(Utilidades::toString(votante.getId()), offset);
	this->hash->guardar(&aAgregarID);
	delete this->hash;
	return true;
}


bool ABMentidades::altaLista(Lista &lista) {
	/* Inicializo el hash */
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_lista_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_lista_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_lista_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

	/* Busco en el hash si ya existe la lista */
	string fecha = Utilidades::indexarFecha(lista.getEleccion().getFecha());
	string cargo = lista.getEleccion().getCargo().getCargoPrincipal();
	string nombreLista = lista.getNombre();
	Utilidades::formatearClave(cargo);
	Utilidades::formatearClave(nombreLista);
	string clave = fecha + "$" + cargo + "$" + nombreLista;
	RegistroIndice aAgregar(clave,0);
	RegistroIndice *returnReg = this->hash->buscar(&aAgregar);
	if (returnReg != NULL) return false;					// Ya existia en el hash, no se agrega

	/* Le seteo un id y lo guardo en el archivo de datos */
	lista.setId(ManejoIDs::obtenerIDnuevo(lista.getClassName()));
	unsigned long int offset = this->dataAccess.Guardar(lista);

	/* Guardo en el hash lista/id_lista */
	aAgregar.setOffset(lista.getId());
	this->hash->guardar(&aAgregar);
	delete this->hash;

	/* Guardo en el hash id_lista/offset */
	arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idlista_regs>"));
	arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idlista_bloq_lib>"));
	arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idlista_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregarID(Utilidades::toString(lista.getId()), offset);
	this->hash->guardar(&aAgregarID);
	delete this->hash;
	return true;
}


bool ABMentidades::altaCandidato(Candidato &candidato) {
	/* Inicializo el hash */
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_candidato_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_candidato_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_candidato_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

	/* Busco en el hash si ya existe el candidato */
	string fecha = Utilidades::indexarFecha(candidato.getLista().getEleccion().getFecha());
	string cargo = candidato.getLista().getEleccion().getCargo().getCargoPrincipal();
	string lista = candidato.getLista().getNombre();
	string DNI = Utilidades::toString(candidato.getDNI());
	Utilidades::formatearClave(cargo);
	Utilidades::formatearClave(lista);
	string clave = fecha + "$" + cargo + "$" + lista + "$" + DNI;
	RegistroIndice aAgregar(clave,0);
	RegistroIndice *returnReg = this->hash->buscar(&aAgregar);
	if (returnReg != NULL) return false;					// Ya existia en el hash, no se agrega

	/* Le seteo un id y lo guardo en el archivo de datos */
	candidato.setId(ManejoIDs::obtenerIDnuevo(candidato.getClassName()));
	unsigned long int offset = this->dataAccess.Guardar(candidato);

	/* Guardo en el hash candidato/id_candidato */
	aAgregar.setOffset(candidato.getId());
	this->hash->guardar(&aAgregar);
	delete this->hash;

	/* Guardo en el hash id_candidato/offset */
	arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcandidato_regs>"));
	arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcandidato_bloq_lib>"));
	arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcandidato_tabla>"));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregarID(Utilidades::toString(candidato.getId()), offset);
	this->hash->guardar(&aAgregarID);
	delete this->hash;
	return true;
}


bool ABMentidades::modificacionEleccion(Eleccion &eleccion)
{
    return true;
}

bool ABMentidades::modificacionDistrito(Distrito &distrito)
{
    return true;
}
bool ABMentidades::modificacionCargo(Cargo &cargo)
{
    return true;
}

bool ABMentidades::modificacionVotante(Votante &votante)
{
    return true;
}

bool ABMentidades::modificacionLista(Lista &lista)
{
    return true;
}

bool ABMentidades::modificacionCandidato(Candidato &candidato)
{
    return true;
}

bool ABMentidades::bajaEleccion(Eleccion &eleccion)
{
    return true;
}

bool ABMentidades::bajaEleccion(string claveEleccion)
{
    //busca la clave en el hash (supongo que ya recibí la clave concatenada y formateada)
    string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_ELECCION_REGS));
    string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_ELECCION_BLOQ_LIB));
    string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_ELECCION_TABLA));
    hash_extensible *hashEleccion = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

    //Si existe, la borra del hash de clave/Id y del hash de Id/offset
    //(baja lógica) y devuelve true
    RegistroIndice registroABuscar(claveEleccion, 0);
    RegistroIndice *registroObtenido = hashEleccion->buscar(&registroABuscar);
    if(registroObtenido != NULL){

        int IDEleccion = registroObtenido->getOffset();
        hashEleccion->borrar(registroObtenido);
        delete hashEleccion;

        string arch_id_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_REGS));
        string arch_id_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_BLOQ_LIB));
        string arch_id_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_TABLA));
        hash_extensible *hashIDEleccion = new hash_extensible(arch_id_registros,arch_id_bloq_libres,arch_id_tabla);

        string IDaux = Utilidades::toString(IDEleccion);
        RegistroIndice registroABorrar(IDaux, 0);
        hashIDEleccion->borrar(&registroABorrar);
        delete hashIDEleccion;

        return true;
    }
    //devuelve false si la Elección no existía
    delete hashEleccion;
    return false;
}

bool ABMentidades::bajaDistrito(Distrito &distrito)
{
    return true;
}

bool ABMentidades::bajaDistrito(string claveDistrito)
{
    //busca la clave en el hash (supongo que ya recibí la clave concatenada y formateada)
    string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_DISTRITO_REGS));
    string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_DISTRITO_BLOQ_LIB));
    string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_DISTRITO_TABLA));
    hash_extensible *hashDistrito = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

    //Si existe, la borra del hash de clave/Id y del hash de Id/offset
    //(baja lógica) y devuelve true
    RegistroIndice registroABuscar(claveDistrito, 0);
    RegistroIndice *registroObtenido = hashDistrito->buscar(&registroABuscar);
    if(registroObtenido != NULL){

        int IDDistrito = registroObtenido->getOffset();
        hashDistrito->borrar(registroObtenido);
        delete hashDistrito;

        string arch_id_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_REGS));
        string arch_id_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_BLOQ_LIB));
        string arch_id_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_TABLA));
        hash_extensible *hashIDDistrito = new hash_extensible(arch_id_registros,arch_id_bloq_libres,arch_id_tabla);

        string IDaux = Utilidades::toString(IDDistrito);
        RegistroIndice registroABorrar(IDaux, 0);
        hashIDDistrito->borrar(&registroABorrar);
        delete hashIDDistrito;

        return true;
    }
    //devuelve false si el Distrito no existía
    delete hashDistrito;
    return false;
     /* En realidad se necesitan borrar tb las cosas que tenian referencias a ese
      * distrito, pero eso desp lo agregamos.
      */
}

bool ABMentidades::bajaCargo(Cargo &cargo)
{
    return true;
}

bool ABMentidades::bajaCargo(string claveCargo)
{
    //busca la clave en el hash (supongo que ya recibí la clave concatenada y formateada)
    string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_CARGO_REGS));
    string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_CARGO_BLOQ_LIB));
    string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_CARGO_TABLA));
    hash_extensible *hashCargo = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

    //Si existe, la borra del hash de clave/Id y del hash de Id/offset
    //(baja lógica) y devuelve true
    RegistroIndice registroABuscar(claveCargo, 0);
    RegistroIndice *registroObtenido = hashCargo->buscar(&registroABuscar);
    if(registroObtenido != NULL){

        int IDCargo = registroObtenido->getOffset();
        hashCargo->borrar(registroObtenido);
        delete hashCargo;

        string arch_id_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCARGO_REGS));
        string arch_id_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCARGO_BLOQ_LIB));
        string arch_id_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCARGO_TABLA));
        hash_extensible *hashIDCargo = new hash_extensible(arch_id_registros,arch_id_bloq_libres,arch_id_tabla);

        string IDaux = Utilidades::toString(IDCargo);
        RegistroIndice registroABorrar(IDaux, 0);
        hashIDCargo->borrar(&registroABorrar);
        delete hashIDCargo;

        return true;
    }
    //devuelve false si el Cargo no existía
    delete hashCargo;
    return false;
}

bool ABMentidades::bajaVotante(Votante &votante)
{
    return true;
}

bool ABMentidades::bajaVotante(string claveVotante)
{
    //busca la clave en el hash (supongo que ya recibí la clave concatenada y formateada)
    string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_VOTANTE_REGS));
    string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_VOTANTE_BLOQ_LIB));
    string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_VOTANTE_TABLA));
    hash_extensible *hashVotante = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

    //Si existe, la borra del hash de clave/Id y del hash de Id/offset
    //(baja lógica) y devuelve true
    RegistroIndice registroABuscar(claveVotante, 0);
    RegistroIndice *registroObtenido = hashVotante->buscar(&registroABuscar);
    if(registroObtenido != NULL){

        int IDVotante = registroObtenido->getOffset();
        hashVotante->borrar(registroObtenido);
        delete hashVotante;

        string arch_id_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_REGS));
        string arch_id_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_BLOQ_LIB));
        string arch_id_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_TABLA));
        hash_extensible *hashIDVotante = new hash_extensible(arch_id_registros,arch_id_bloq_libres,arch_id_tabla);

        string IDaux = Utilidades::toString(IDVotante);
        RegistroIndice registroABorrar(IDaux, 0);
        hashIDVotante->borrar(&registroABorrar);
        delete hashIDVotante;

        return true;
    }
    //devuelve false si el Votante no existía
    delete hashVotante;
    return false;
}

bool ABMentidades::bajaLista(Lista &lista)
{
    return true;
}

bool ABMentidades::bajaLista(string claveLista)
{
    //busca la clave en el hash (supongo que ya recibí la clave concatenada y formateada)
    string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_LISTA_REGS));
    string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_LISTA_BLOQ_LIB));
    string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_LISTA_TABLA));
    hash_extensible *hashLista = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

    //Si existe, la borra del hash de clave/Id y del hash de Id/offset
    //(baja lógica) y devuelve true
    RegistroIndice registroABuscar(claveLista, 0);
    RegistroIndice *registroObtenido = hashLista->buscar(&registroABuscar);
    if(registroObtenido != NULL){

        int IDLista = registroObtenido->getOffset();
        hashLista->borrar(registroObtenido);
        delete hashLista;

        string arch_id_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDLISTA_REGS));
        string arch_id_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDLISTA_BLOQ_LIB));
        string arch_id_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDLISTA_TABLA));
        hash_extensible *hashIDLista = new hash_extensible(arch_id_registros,arch_id_bloq_libres,arch_id_tabla);

        string IDaux = Utilidades::toString(IDLista);
        RegistroIndice registroABorrar(IDaux, 0);
        hashIDLista->borrar(&registroABorrar);
        delete hashIDLista;

        return true;
    }
    //devuelve false si la Lista no existía
    delete hashLista;
    return false;
}

bool ABMentidades::bajaCandidato(Candidato &candidato)
{
    return true;
}

bool ABMentidades::bajaCandidato(string claveCandidato)
{
    //busca la clave en el hash (supongo que ya recibí la clave concatenada y formateada)
    string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_CANDIDATO_REGS));
    string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_CANDIDATO_BLOQ_LIB));
    string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_CANDIDATO_TABLA));
    hash_extensible *hashCandidato = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

    //Si existe, la borra del hash de clave/Id y del hash de Id/offset
    //(baja lógica) y devuelve true
    RegistroIndice registroABuscar(claveCandidato, 0);
    RegistroIndice *registroObtenido = hashCandidato->buscar(&registroABuscar);
    if(registroObtenido != NULL){

        int IDCandidato = registroObtenido->getOffset();
        hashCandidato->borrar(registroObtenido);
        delete hashCandidato;

        string arch_id_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCANDIDATO_REGS));
        string arch_id_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCANDIDATO_BLOQ_LIB));
        string arch_id_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCANDIDATO_TABLA));
        hash_extensible *hashIDCandidato = new hash_extensible(arch_id_registros,arch_id_bloq_libres,arch_id_tabla);

        string IDaux = Utilidades::toString(IDCandidato);
        RegistroIndice registroABorrar(IDaux, 0);
        hashIDCandidato->borrar(&registroABorrar);
        delete hashIDCandidato;

        return true;
    }
    //devuelve false si el Candidato no existía
    delete hashCandidato;
    return false;
}

bool ABMentidades::altaAdministrador(Administrador &administrador)
{
    return true;
}

bool ABMentidades::modificacionAdministrador(Administrador &administrador)
{
    return true;
}

bool ABMentidades::bajaAdministrador(Administrador &administrador)
{
    return true;
}
