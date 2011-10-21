/*
 * ABMentidades.cpp
 *
 *  Created on: 10/10/2011
 *      Author: martin
 */

#include "ABMentidades.h"

ABMentidades::ABMentidades() {}

ABMentidades::~ABMentidades() {}


/* ALTA EN ARBOL */
bool ABMentidades::altaEleccion(Eleccion &eleccion) {
	long int offsetArbol = 0;

	/* Inicializo el arbol */
	string archivo((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_ELECCION));
	this->arbol = new ArbolBMas();
	if (!this->arbol->abrir(archivo)) throw VotoElectronicoExcepcion("No se abrio el arbol de eleccion");
	
	/* Busco en el arbol si ya existe la eleccion */
	string clave = Utilidades::obtenerClaveEleccion(eleccion.getFecha(),eleccion.getCargo().getCargoPrincipal());
	if (this->arbol->buscar(clave,offsetArbol)) {
		this->arbol->cerrar();
		delete this->arbol;
		this->arbol = NULL;
		return false;		// Caso de que ya existia.
	}

	/* Le seteo un id y lo guardo en el archivo de datos */
	eleccion.setId(ManejoIDs::obtenerIDnuevo(eleccion.getClassName()));
	unsigned long int offset = this->dataAccess.Guardar(eleccion);

	/* Guardo en el arbol eleccion/id_eleccion */
	if (!this->arbol->agregar(clave,eleccion.getId()))
		throw VotoElectronicoExcepcion("No se pudo dar de alta la eleccion por fallos en el insertar del arbol");
	this->arbol->cerrar();
	delete this->arbol;
	this->arbol = NULL;

	/* Guardo en el hash id_eleccion/offset */
	string arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_REGS));
	string arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_BLOQ_LIB));
	string arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregarID(Utilidades::toString(eleccion.getId()), offset);
	this->hash->guardar(&aAgregarID);
	this->hash->imprimir("./archivos/Otros/hash_ideleccion");
	delete this->hash;
	this->hash = NULL;

	Logger::Alta(eleccion);

	return true;
}


/* ALTA EN HASH */
bool ABMentidades::altaDistrito(Distrito &distrito) {
	/* Inicializo el hash */
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_DISTRITO_REGS));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_DISTRITO_BLOQ_LIB));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_DISTRITO_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

	/* Busco en el hash si ya existe el distrito */
	string clave = Utilidades::obtenerClaveDistrito(distrito.getNombre());
	RegistroIndice aAgregar(clave,0);
	RegistroIndice *returnReg = this->hash->buscar(&aAgregar);
	if (returnReg != NULL) {
		delete this->hash;
		this->hash = NULL;
		return false;							// Ya existia en el hash, no se agrega
	}

	/* Le seteo un id y lo guardo en el archivo de datos */
	distrito.setId(ManejoIDs::obtenerIDnuevo(distrito.getClassName()));
	unsigned long int offset = this->dataAccess.Guardar(distrito);

	/* Guardo en el hash distrito/id_distrito */
	aAgregar.setOffset(distrito.getId());
	this->hash->guardar(&aAgregar);
	this->hash->imprimir("./archivos/Otros/hash_distrito");
	delete this->hash;

	/* Guardo en el hash id_distrito/offset */
	arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_REGS));
	arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_BLOQ_LIB));
	arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregarID(Utilidades::toString(distrito.getId()), offset);
	this->hash->guardar(&aAgregarID);
	this->hash->imprimir("./archivos/Otros/hash_iddistrito");
	delete this->hash;
	this->hash = NULL;

	Logger::Alta(distrito);

	return true;
}


/* ALTA EN HASH */
bool ABMentidades::altaCargo(Cargo &cargo) {
	/* Inicializo el hash */
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_CARGO_REGS));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_CARGO_BLOQ_LIB));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_CARGO_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

	/* Busco en el hash si ya existe el cargo */
	string clave = Utilidades::obtenerClaveCargo(cargo.getCargoPrincipal());
	RegistroIndice aAgregar(clave,0);
	RegistroIndice *returnReg = this->hash->buscar(&aAgregar);
	if (returnReg != NULL) {
		delete this->hash;
		this->hash = NULL;
		return false;							// Ya existia en el hash, no se agrega
	}

	/* Le seteo un id y lo guardo en el archivo de datos */
	cargo.setId(ManejoIDs::obtenerIDnuevo(cargo.getClassName()));
	unsigned long int offset = this->dataAccess.Guardar(cargo);

	/* Guardo en el hash cargo/id_cargo */
	aAgregar.setOffset(cargo.getId());
	this->hash->guardar(&aAgregar);
	this->hash->imprimir("./archivos/Otros/hash_cargo");
	delete this->hash;

	/* Guardo en el hash id_cargo/offset */
	arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCARGO_REGS));
	arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCARGO_BLOQ_LIB));
	arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCARGO_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregarID(Utilidades::toString(cargo.getId()), offset);
	this->hash->guardar(&aAgregarID);
	this->hash->imprimir("./archivos/Otros/hash_idcargo");
	delete this->hash;
	this->hash = NULL;

	Logger::Alta(cargo);

	return true;
}


/* ALTA EN HASH */
bool ABMentidades::altaVotante(Votante &votante) {
	/* Inicializo el hash */
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_VOTANTE_REGS));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_VOTANTE_BLOQ_LIB));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_VOTANTE_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);

	/* Busco en el hash si ya existe el votante */
	string clave = Utilidades::obtenerClaveVotante(votante.getDNI());
	RegistroIndice aAgregar(clave,0);
	RegistroIndice *returnReg = this->hash->buscar(&aAgregar);
	if (returnReg != NULL) {
		delete this->hash;
		this->hash = NULL;
		return false;								// Ya existia en el hash, no se agrega
	}

	/* Le seteo un id y lo guardo en el archivo de datos */
	votante.setId(ManejoIDs::obtenerIDnuevo(votante.getClassName()));
	unsigned long int offset = this->dataAccess.Guardar(votante);

	/* Guardo en el hash votante/id_votante */
	aAgregar.setOffset(votante.getId());
	this->hash->guardar(&aAgregar);
	this->hash->imprimir("./archivos/Otros/hash_votante");
	delete this->hash;

	/* Guardo en el hash id_votante/offset */
	arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_REGS));
	arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_BLOQ_LIB));
	arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregarID(Utilidades::toString(votante.getId()), offset);
	this->hash->guardar(&aAgregarID);
	this->hash->imprimir("./archivos/Otros/hash_idvotante");
	delete this->hash;
	this->hash = NULL;

	Logger::Alta(votante);

	return true;
}


/* ALTA EN ARBOL */
bool ABMentidades::altaLista(Lista &lista) {
	long int offsetArbol = 0;

	/* Inicializo el arbol */
	string archivo((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_LISTA));
	this->arbol = new ArbolBMas();
	if (!this->arbol->abrir(archivo)) throw VotoElectronicoExcepcion("No se abrio el arbol de lista");

	/* Busco en el arbol si ya existe la lista */
	string clave = Utilidades::obtenerClaveLista(lista.getEleccion().getFecha(),lista.getEleccion().getCargo().getCargoPrincipal(),lista.getNombre());
	if (this->arbol->buscar(clave,offsetArbol)) {
		this->arbol->cerrar();
		delete this->arbol;
		this->arbol = NULL;
		return false;				// Caso de que ya existia.
	}

	/* Le seteo un id y lo guardo en el archivo de datos */
	lista.setId(ManejoIDs::obtenerIDnuevo(lista.getClassName()));
	unsigned long int offset = this->dataAccess.Guardar(lista);

	/* Guardo en el arbol lista/id_lista */
	if (!this->arbol->agregar(clave,lista.getId()))
		throw VotoElectronicoExcepcion("No se pudo dar de alta la lista por fallos en el insertar del arbol");
	this->arbol->cerrar();
	delete this->arbol;
	this->arbol = NULL;

	/* Guardo en el hash id_lista/offset */
	string arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDLISTA_REGS));
	string arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDLISTA_BLOQ_LIB));
	string arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDLISTA_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregarID(Utilidades::toString(lista.getId()), offset);
	this->hash->guardar(&aAgregarID);
	this->hash->imprimir("./archivos/Otros/hash_idlista");
	delete this->hash;
	this->hash = NULL;

	Logger::Alta(lista);

	/* Creo los conteos inicializados en 0 */
	this->crearConteo(lista);

	return true;
}


/* ALTA EN ARBOL */
bool ABMentidades::altaCandidato(Candidato &candidato) {
	long int offsetArbol = 0;

	/* Inicializo el arbol */
	string archivo((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_CANDIDATO));
	this->arbol = new ArbolBMas();
	if (!this->arbol->abrir(archivo)) throw VotoElectronicoExcepcion("No se abrio el arbol de candidato");

	/* Busco en el arbol si ya existe el candidato */
	string clave = Utilidades::obtenerClaveCandidato(candidato.getLista().getEleccion().getFecha(),candidato.getLista().getEleccion().getCargo().getCargoPrincipal(),candidato.getLista().getNombre(),candidato.getDNI());
	if (this->arbol->buscar(clave,offsetArbol)) {
		this->arbol->cerrar();
		delete this->arbol;
		this->arbol = NULL;
		return false;					// Caso de que ya existia.
	}

	/* Le seteo un id y lo guardo en el archivo de datos */
	candidato.setId(ManejoIDs::obtenerIDnuevo(candidato.getClassName()));
	unsigned long int offset = this->dataAccess.Guardar(candidato);

	/* Guardo en el arbol candidato/id_candidato */
	if (!this->arbol->agregar(clave,candidato.getId()))
		throw VotoElectronicoExcepcion("No se pudo dar de alta el candidato por fallos en el insertar del arbol");
	this->arbol->cerrar();
	delete this->arbol;
	this->arbol = NULL;

	/* Guardo en el hash id_candidato/offset */
	string arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCANDIDATO_REGS));
	string arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCANDIDATO_BLOQ_LIB));
	string arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCANDIDATO_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aAgregarID(Utilidades::toString(candidato.getId()), offset);
	this->hash->guardar(&aAgregarID);
	this->hash->imprimir("./archivos/Otros/hash_idcandidato");
	delete this->hash;
	this->hash = NULL;

	Logger::Alta(candidato);

	return true;
}


void ABMentidades::agregarVoto(Votante &votante, Lista &lista, Distrito &distrito) {

    /* Le agrego la eleccion al votante como "ya votada" y guardo el votante en disco */
    votante.agregarEleccion(lista.getEleccion());
    this->modificacionVotante(votante);

	//Usando los datos recibidos por parámetro busca el objeto conteo
    //en el árbol de reporte por distrito.
    this->arbol = new ArbolBMas();
    this->arbol->abrir((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_REPORTE_DISTRITO));

    /* Obtengo la clave de la lista */
   	string fecha = Utilidades::indexarFecha(lista.getEleccion().getFecha());
   	string nombreCargo = lista.getEleccion().getCargo().getCargoPrincipal();
   	string nombreLista = lista.getNombre();
   	string claveLista = fecha + "$" + nombreCargo + "$" + nombreLista;

    string claveConcatenada = distrito.getNombre() + "$" + claveLista;
    Utilidades::formatearClave(claveConcatenada);
    long int offsetConteo;

    if(!this->arbol->buscar(claveConcatenada, offsetConteo)) {
    	/* Si no existia, hago un nuevo conteo */

    	/* Creo el conteo */
  		Conteo conteoNuevo(lista,distrito);
  		conteoNuevo.incrementar();

  		/* Guardo el conteo en archivo */
  	    offsetConteo = this->dataAccess.Guardar(conteoNuevo);

  	    /* Indexo en el arbol de reporte por distrito */
    	this->arbol->agregar(claveConcatenada, offsetConteo);
        this->arbol->cerrar();
        delete this->arbol;
        this->arbol = NULL;

    	//indexa en árbol de reporte por lista:
    	ArbolBMas *arbolLista = new ArbolBMas();
   		arbolLista->abrir((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_REPORTE_LISTA));

    	claveConcatenada = claveLista + "$" + distrito.getNombre();
    	Utilidades::formatearClave(claveConcatenada);
    	arbolLista->agregar(claveConcatenada, offsetConteo);
        arbolLista->cerrar();
        delete arbolLista;

    	//indexa en árbol de reporte por eleccion:
    	ArbolBMas *arbolEleccion = new ArbolBMas();
    	arbolEleccion->abrir((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_REPORTE_ELECCION));
    	claveConcatenada =  fecha + "$" +nombreCargo + "$" + distrito.getNombre() + "$" + nombreLista;
    	Utilidades::formatearClave(claveConcatenada);
    	arbolEleccion->agregar(claveConcatenada, offsetConteo);
        arbolEleccion->cerrar();
        delete arbolEleccion;

    	return;
    }

    this->arbol->cerrar();
    delete this->arbol;
    this->arbol = NULL;

    //Si ya existía, lo lee, incrementa en 1 su cantidad, y guarda
    //el cambio (en el archivo de registros variables)
    Conteo conteoExistente;

    this->dataAccess.Leer(conteoExistente, offsetConteo);
    conteoExistente.incrementar();

    //sobreescribe el registro
    string rutaArchivo = conteoExistente.getURLArchivoDatos();

    ofstream ofs;

    ofs.open(rutaArchivo.c_str(), ios::binary | ios::in);
	if(!ofs.is_open())
	{
		//Si no existia lo creo
		ofs.open(rutaArchivo.c_str(), ios::binary | ios::out);
		ofs.close();
	}
	else
		ofs.close();

	ofs.open(rutaArchivo.c_str(), ios::in | ios::out | ios::binary);

    if(!ofs.is_open())	throw VotoElectronicoExcepcion("No se pudo abrir el archivo de Conteo");
    ofs.seekp(offsetConteo);
    conteoExistente.Guardar(ofs);
    ofs.close();

    return;
}


void ABMentidades::crearConteo(Lista &lista) {

	/* Instancio los arboles */
	ArbolBMas *arbolDistrito = new ArbolBMas();
	arbolDistrito->abrir((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_REPORTE_DISTRITO));
	ArbolBMas *arbolLista = new ArbolBMas();
	arbolLista->abrir((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_REPORTE_LISTA));
	ArbolBMas *arbolEleccion = new ArbolBMas();
	arbolEleccion->abrir((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_REPORTE_ELECCION));

	/* Obtengo la clave de la lista */
	string fecha = Utilidades::indexarFecha(lista.getEleccion().getFecha());
	string nombreCargo = lista.getEleccion().getCargo().getCargoPrincipal();
	string nombreLista = lista.getNombre();
	string claveLista = fecha + "$" + nombreCargo + "$" + nombreLista;

	/* Instancio algunas variables */
	string claveConcatenada;
    int cantidadDistritos = lista.getEleccion().getDistritos().size();
    long int offsetConteo;
	Conteo *conteoNuevo = NULL;

	for(int i=0;i<cantidadDistritos;i++) {
		/* Creo el conteo */
		conteoNuevo = new Conteo(lista,*(lista.getEleccion().getDistritos()[i]));

		/* Guardo el conteo en archivo */
	    offsetConteo = this->dataAccess.Guardar(*conteoNuevo);

	    /* Indexo en el arbol de reporte por distrito */
	    claveConcatenada = lista.getEleccion().getDistritos()[i]->getNombre() + "$" + claveLista;
	    Utilidades::formatearClave(claveConcatenada);
	    arbolDistrito->agregar(claveConcatenada, offsetConteo);


	    //indexa en árbol de reporte por lista:
	    claveConcatenada = claveLista + "$" + lista.getEleccion().getDistritos()[i]->getNombre();
	    Utilidades::formatearClave(claveConcatenada);
	    arbolLista->agregar(claveConcatenada, offsetConteo);


	    //indexa en árbol de reporte por eleccion:
        claveConcatenada =  fecha + "$" +nombreCargo + "$" + lista.getEleccion().getDistritos()[i]->getNombre() + "$" + nombreLista;
        Utilidades::formatearClave(claveConcatenada);
        arbolEleccion->agregar(claveConcatenada, offsetConteo);

        delete conteoNuevo;
	}

	/* Cierro y elimino los arboles */
    arbolDistrito->cerrar();
    delete arbolDistrito;
    arbolLista->cerrar();
    delete arbolLista;
    arbolEleccion->cerrar();
    delete arbolEleccion;

    return;
}


/* NO SE PUEDE CAMBIAR LA FECHA, NI EL CARGO PRINCIPAL.
* TAMPOCO SE PUEDEN AGREGAR CARGOS SECUNDARIOS. SI SE QUIEREN AGREGAR, SE HACE DESDE EL MODIFICAR DE CARGO, Y CUANDO SE LEVANTE DE DISCO
* LA ELECCION NUEVAMENTE (OBTENERREGISTRO) YA VAN A ESTAR LOS CARGOS SECUNDARIOS AGREGADOS.
* EL MODIFICAR ELECCION TE PERMITE AGREGAR O SACAR DISTRITOS SIEMPRE Y CUANDO SE AGREGUEN DISTRITOS QUE YA EXISTAN */
bool ABMentidades::modificacionEleccion(Eleccion &eleccion) {

	/* Busco el offset del id de la eleccion */
	string arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_REGS));
	string arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_BLOQ_LIB));
	string arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aBuscarID(Utilidades::toString(eleccion.getId()),0);
	RegistroIndice *returnRegID = this->hash->buscar(&aBuscarID);
	if (returnRegID == NULL) throw VotoElectronicoExcepcion("No se encontro el id de la eleccion");
	unsigned long int offset = returnRegID->getOffset();

	/* Recupero el registro del archivo de datos */
	Eleccion eleccionRecuperada;
	this->dataAccess.Leer(eleccionRecuperada,offset);

	/* Chequeo si hay un cambio de clave */
	if ((eleccion.getFecha() != eleccionRecuperada.getFecha() || (eleccion.getCargo().getCargoPrincipal() != eleccionRecuperada.getCargo().getCargoPrincipal())) ) {
		/* No se cumplio la condicion pedida, no se modifica el registro */
		delete this->hash;
		this->hash = NULL;
		return false;
	}

	/* Comparo el tamanio en disco de los registros. Si el modificado es menor o igual al original, se sobreescribe.
	 * Si es mayor, se da de alta al final */
	int tamanioOriginal = eleccionRecuperada.getTamanioEnDisco();
	int tamanioModificado = eleccion.getTamanioEnDisco();
	if (tamanioOriginal >= tamanioModificado) {
		/* Sobreescribo el registro anterior */
		string rutaArchivo = eleccion.getURLArchivoDatos();
		ofstream ofs;
		ofs.open(rutaArchivo.c_str(), ios::in | ios::out | ios::binary);
		if(!ofs.is_open())	throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + eleccion.getClassName());
		ofs.seekp(offset,ios::beg);
		eleccion.Guardar(ofs);
		ofs.close();
	}
	else {
		/* Doy de alta al final del archivo y modifico el indice del hash id_eleccion/offset */
		unsigned int nuevoOffset = this->dataAccess.Guardar(eleccion);
		RegistroIndice aGuardar(Utilidades::toString(eleccion.getId()),nuevoOffset);
		this->hash->borrar(&aBuscarID);
		this->hash->guardar(&aGuardar);
		this->hash->imprimir("./archivos/Otros/hash_ideleccion");
	}
	delete this->hash;
	this->hash = NULL;

	Logger::Modificacion(eleccion);

	return true;
}


/* Retorna true si se hizo la modificacion, retorna false si no se logro modificar porque ya existia un registro igual
 * a la modificacion que se intenta hacer */
bool ABMentidades::modificacionDistrito(Distrito &distrito) {

	/* Busco en el hash de distrito/id_distrito si existe la clave nueva del distrito */
	string idarch_registros((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_DISTRITO_REGS));
	string idarch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_DISTRITO_BLOQ_LIB));
	string idarch_tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_DISTRITO_TABLA));
	hash_extensible *hash_auxiliar = new hash_extensible(idarch_registros,idarch_bloq_libres,idarch_tabla);
	string claveModificada = Utilidades::obtenerClaveDistrito(distrito.getNombre());
	RegistroIndice aBuscar(claveModificada,0);
	RegistroIndice *returnReg = hash_auxiliar->buscar(&aBuscar);
	if (returnReg != NULL) {
		/* Retorno false ya que no se puede hacer la modificacion porque ya existe ese distrito */
		delete hash_auxiliar;
		hash_auxiliar = NULL;
		return false;
	}

	/* Busco el offset del id del distrito */
	string arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_REGS));
	string arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_BLOQ_LIB));
	string arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aBuscarID(Utilidades::toString(distrito.getId()),0);
	RegistroIndice *returnRegID = this->hash->buscar(&aBuscarID);
	if (returnRegID == NULL) throw VotoElectronicoExcepcion("No se encontro el id del distrito");
	unsigned long int offset = returnRegID->getOffset();

	/* Recupero el registro del archivo de datos */
	Distrito distritoRecuperado;
	this->dataAccess.Leer(distritoRecuperado,offset);

	/* Comparo el tamanio en disco de los registros. Si el modificado es menor o igual al original, se sobreescribe.
	 * Si es mayor, se da de alta al final */
	int tamanioOriginal = distritoRecuperado.getTamanioEnDisco();
	int tamanioModificado = distrito.getTamanioEnDisco();
	if (tamanioOriginal >= tamanioModificado) {
		/* Sobreescribo el registro anterior */
		string rutaArchivo = distrito.getURLArchivoDatos();
		ofstream ofs;
		ofs.open(rutaArchivo.c_str(), ios::in | ios::out | ios::binary);
		if(!ofs.is_open())	throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + distrito.getClassName());
		ofs.seekp(offset,ios::beg);
		distrito.Guardar(ofs);
		ofs.close();
	}
	else {
		/* Doy de alta al final del archivo y modifico el indice del hash id_distrito/offset */
		unsigned int nuevoOffset = this->dataAccess.Guardar(distrito);
		RegistroIndice aGuardar(Utilidades::toString(distrito.getId()),nuevoOffset);
		this->hash->borrar(&aBuscarID);
		this->hash->guardar(&aGuardar);
		this->hash->imprimir("./archivos/Otros/hash_iddistrito");
	}
	delete this->hash;
	this->hash = NULL;

	Logger::Modificacion(distrito);

	/* Cambio la clave en el hash distrito/id_distrito */

	/* Elimino la clave con el nombre de distrito viejo */
	string claveOriginal = Utilidades::obtenerClaveDistrito(distritoRecuperado.getNombre());
	RegistroIndice aEliminar(claveOriginal,0);
	if (!hash_auxiliar->borrar(&aEliminar)) throw VotoElectronicoExcepcion("Se quizo borrar una clave que no existia (modificacion distrito)");

	/* Inserto la clave modificada */
	RegistroIndice aModificar(claveModificada,distrito.getId());
	hash_auxiliar->guardar(&aModificar);
	hash_auxiliar->imprimir("./archivos/Otros/hash_distrito");

	delete hash_auxiliar;
	hash_auxiliar = NULL;

	/* Debo cambiar las claves en el arbol de reporte por distrito */

	/* Inicializo el arbol */
	string archivo((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_REPORTE_DISTRITO));
	this->arbol = new ArbolBMas();
	if (!this->arbol->abrir(archivo)) throw VotoElectronicoExcepcion("No se abrio el arbol de reporte por distrito");
    string claveFinal = claveOriginal + "&";

    /* Busco todas las claves que tengan mi nombre de distrito viejo */
    list<RegistroArbol *> clavesEncontradas;
    if (!this->arbol->buscar(clavesEncontradas, claveOriginal, claveFinal)) {
    	this->arbol->cerrar();
   	    delete this->arbol;
   	    this->arbol = NULL;
    	return true;	// Si no habia ninguna coincidencia, se retorna
    }

    /* Cambio los nombres por el nuevo nombre de distrito */
    RegistroArbol *registroEnLista = NULL;
    string claveDistrito;
    string aConcatenar;
    list<RegistroArbol *>::iterator it;
    size_t aux;
    for (it = clavesEncontradas.begin(); it != clavesEncontradas.end(); it++){
    	aConcatenar = claveModificada;
    	registroEnLista = *it;
       	claveDistrito = registroEnLista->getClave();
       	aux = claveDistrito.find_first_of("$");
       	aConcatenar.append(claveDistrito,aux,100);
       	if(!this->arbol->cambiarClave(claveDistrito,aConcatenar))
       		throw VotoElectronicoExcepcion("No se pudo cambiar la clave en el arbol de reporte distrito");
    }

    /* Cierro el Arbol */
	this->arbol->cerrar();
    delete this->arbol;
    this->arbol = NULL;

	return true;
}


/* NO SE PUEDE MODIFICAR EL IDENTIFICADOR DE UN CARGO, ES DECIR, CAMBIAR EL NOMBRE AL CARGO PRINCIPAL */
/* SOLO SE PUEDE AGREGAR O QUITAR CARGOS SECUNDARIOS */
/* Retorna true si se hizo la modificacion, retorna false si no se logro modificar porque no cumple la condicion de arriba */
bool ABMentidades::modificacionCargo(Cargo &cargo) {

	/* Busco el offset del id del cargo */
	string arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCARGO_REGS));
	string arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCARGO_BLOQ_LIB));
	string arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCARGO_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aBuscarID(Utilidades::toString(cargo.getId()),0);
	RegistroIndice *returnRegID = this->hash->buscar(&aBuscarID);
	if (returnRegID == NULL) throw VotoElectronicoExcepcion("No se encontro el id del cargo");
	unsigned long int offset = returnRegID->getOffset();

	/* Recupero el registro del archivo de datos */
	Cargo cargoRecuperado;
	this->dataAccess.Leer(cargoRecuperado,offset);

	/* Chequeo si hay un cambio de clave */
	if (cargo.getCargoPrincipal() != cargoRecuperado.getCargoPrincipal()) {
		/* No se cumplio la condicion pedida, no se modifica el registro */
		delete this->hash;
		this->hash = NULL;
		return false;
	}

	/* Comparo el tamanio en disco de los registros. Si el modificado es menor o igual al original, se sobreescribe.
	 * Si es mayor, se da de alta al final */
	int tamanioOriginal = cargoRecuperado.getTamanioEnDisco();
	int tamanioModificado = cargo.getTamanioEnDisco();
	if (tamanioOriginal >= tamanioModificado) {
		/* Sobreescribo el registro anterior */
		string rutaArchivo = cargo.getURLArchivoDatos();
		ofstream ofs;
		ofs.open(rutaArchivo.c_str(), ios::in | ios::out | ios::binary);
		if(!ofs.is_open())	throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + cargo.getClassName());
		ofs.seekp(offset,ios::beg);
		cargo.Guardar(ofs);
		ofs.close();
	}
	else {
		/* Doy de alta al final del archivo y modifico el indice del hash id_cargo/offset */
		unsigned int nuevoOffset = this->dataAccess.Guardar(cargo);
		RegistroIndice aGuardar(Utilidades::toString(cargo.getId()),nuevoOffset);
		this->hash->borrar(&aBuscarID);
		this->hash->guardar(&aGuardar);
		this->hash->imprimir("./archivos/Otros/hash_idcargo");
	}
	delete this->hash;
	this->hash = NULL;

	Logger::Modificacion(cargo);

	return true;
}


/* NO SE PUEDE MODIFICAR EL DNI DE UN VOTANTE. LOS DEMAS CAMPOS SI (NOMBRE, CLAVE, DOMICILIO,
 * DISTRITO (QUE EXISTA Y ESTE DADO DE ALTA, USAR OBTENERREGISTRO Y BUSCAR ANTES EL DISTRITO PARA ASEGURARSE Q EXISTA),
 * Y AGREGAR O QUITAR ELECCIONES AL VECTOR DE ELECCIONES */
/* Retorna true si se hizo la modificacion, retorna false si no se logro modificar porque no cumple la condicion de arriba */
bool ABMentidades::modificacionVotante(Votante &votante) {

	/* Busco el offset del id del votante */
	string arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_REGS));
	string arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_BLOQ_LIB));
	string arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aBuscarID(Utilidades::toString(votante.getId()),0);
	RegistroIndice *returnRegID = this->hash->buscar(&aBuscarID);
	if (returnRegID == NULL) throw VotoElectronicoExcepcion("No se encontro el id del votante");
	unsigned long int offset = returnRegID->getOffset();

	/* Recupero el registro del archivo de datos */
	Votante votanteRecuperado;
	this->dataAccess.Leer(votanteRecuperado,offset);

	/* Chequeo si hay un cambio de DNI */
	if (votante.getDNI() != votanteRecuperado.getDNI()) {
		/* No se cumplio la condicion pedida, no se modifica el registro */
		delete this->hash;
		this->hash = NULL;
		return false;
	}

	/* Comparo el tamanio en disco de los registros. Si el modificado es menor o igual al original, se sobreescribe.
	 * Si es mayor, se da de alta al final */
	int tamanioOriginal = votanteRecuperado.getTamanioEnDisco();
	int tamanioModificado = votante.getTamanioEnDisco();
	if (tamanioOriginal >= tamanioModificado) {
		/* Sobreescribo el registro anterior */
		string rutaArchivo = votante.getURLArchivoDatos();
		ofstream ofs;
		ofs.open(rutaArchivo.c_str(), ios::in | ios::out | ios::binary);
		if(!ofs.is_open())	throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + votante.getClassName());
		ofs.seekp(offset,ios::beg);
		votante.Guardar(ofs);
		ofs.close();
	}
	else {
		/* Doy de alta al final del archivo y modifico el indice del hash id_votante/offset */
		unsigned int nuevoOffset = this->dataAccess.Guardar(votante);
		RegistroIndice aGuardar(Utilidades::toString(votante.getId()),nuevoOffset);
		this->hash->borrar(&aBuscarID);
		this->hash->guardar(&aGuardar);
		this->hash->imprimir("./archivos/Otros/hash_idvotante");
	}
	delete this->hash;
	this->hash = NULL;

	Logger::Modificacion(votante);

	return true;
}


/* SOLO SE PUEDE MODIFICAR EL NOMBRE DE LA LISTA */
bool ABMentidades::modificacionLista(Lista &lista) {
	long int offsetArbol = 0;

	/* Busco en el arbol de lista/id_lista si existe la clave nueva de la lista */
	string archivo((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_LISTA));
	this->arbol = new ArbolBMas();
	if (!this->arbol->abrir(archivo)) throw VotoElectronicoExcepcion("No se abrio el arbol de lista");

	string claveModificada = Utilidades::obtenerClaveLista(lista.getEleccion().getFecha(),lista.getEleccion().getCargo().getCargoPrincipal(),lista.getNombre());
	if (this->arbol->buscar(claveModificada,offsetArbol)) {
		/* Se retorna false, no se puede modificar porque ya existe la clave por la que se intenta reemplazar */
		this->arbol->cerrar();
		delete this->arbol;
		this->arbol = NULL;
		return false;
	}

	/* Busco el offset del id de la lista */
	string arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDLISTA_REGS));
	string arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDLISTA_BLOQ_LIB));
	string arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDLISTA_TABLA));
	this->hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice aBuscarID(Utilidades::toString(lista.getId()),0);
	RegistroIndice *returnRegID = this->hash->buscar(&aBuscarID);
	if (returnRegID == NULL) throw VotoElectronicoExcepcion("No se encontro el id de la lista");
	unsigned long int offset = returnRegID->getOffset();

	/* Recupero el registro del archivo de datos */
	Lista listaRecuperada;
	this->dataAccess.Leer(listaRecuperada,offset);

	/* Comparo el tamanio en disco de los registros. Si el modificado es menor o igual al original, se sobreescribe.
	 * Si es mayor, se da de alta al final */
	int tamanioOriginal = listaRecuperada.getTamanioEnDisco();
	int tamanioModificado = listaRecuperada.getTamanioEnDisco();
	if (tamanioOriginal >= tamanioModificado) {
		/* Sobreescribo el registro anterior */
		string rutaArchivo = lista.getURLArchivoDatos();
		ofstream ofs;
		ofs.open(rutaArchivo.c_str(), ios::in | ios::out | ios::binary);
		if(!ofs.is_open())	throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + lista.getClassName());
		ofs.seekp(offset,ios::beg);
		lista.Guardar(ofs);
		ofs.close();
	}
	else {
		/* Doy de alta al final del archivo y modifico el indice del hash id_lista/offset */
		unsigned int nuevoOffset = this->dataAccess.Guardar(lista);
		RegistroIndice aGuardar(Utilidades::toString(lista.getId()),nuevoOffset);
		this->hash->borrar(&aBuscarID);
		this->hash->guardar(&aGuardar);
		this->hash->imprimir("./archivos/Otros/hash_idlista");
	}
	delete this->hash;
	this->hash = NULL;

	Logger::Modificacion(lista);

	/* Cambio la clave en el arbol lista/id_lista */

	/* Elimino la clave con el nombre de lista vieja */
	string claveOriginal = Utilidades::obtenerClaveLista(listaRecuperada.getEleccion().getFecha(),listaRecuperada.getEleccion().getCargo().getCargoPrincipal(),listaRecuperada.getNombre());
	if(!this->arbol->eliminar(claveOriginal)) throw VotoElectronicoExcepcion("Se quizo borrar una clave que no existia (modificacion lista)");

	/* Inserto la clave modificada */
	if(!this->arbol->agregar(claveModificada,lista.getId())) throw VotoElectronicoExcepcion("Se quizo agregar una clave que ya existia (modificacion lista)");;

	/* Cierro el arbol de lista */
	this->arbol->cerrar();
	delete this->arbol;
	this->arbol = NULL;

	/* Debo cambiar las claves en el arbol de reporte por lista */

	/* Inicializo el arbol */
	archivo = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_REPORTE_LISTA));
	this->arbol = new ArbolBMas();
	if (!this->arbol->abrir(archivo)) throw VotoElectronicoExcepcion("No se abrio el arbol de reporte por lista");
    string claveFinal = claveOriginal + "&";

    /* Busco todas las claves que tengan mi nombre de lista viejo */
    list<RegistroArbol *> clavesEncontradas;
   	bool salto = false;
    if (!this->arbol->buscar(clavesEncontradas, claveOriginal, claveFinal)) {
    	salto = true;		// Si no habia ninguna coincidencia, se prosigue a lo siguiente
    }

    RegistroArbol *registroEnLista = NULL;
   	string claveLista;
   	size_t aux;
   	string aConcatenar;
   	list<RegistroArbol *>::iterator it;

    if (!salto) {
    	/* Cambio los nombres por el nuevo nombre de lista */
    	for (it = clavesEncontradas.begin(); it != clavesEncontradas.end(); it++){
    	  	aConcatenar = claveModificada;
    	   	registroEnLista = *it;
    	   	claveLista = registroEnLista->getClave();
    	    aux = claveLista.find_last_of("$");
    	   	aConcatenar.append(claveLista,aux,100);
    	   	if(!this->arbol->cambiarClave(claveLista,aConcatenar))
    	   		throw VotoElectronicoExcepcion("No se pudo cambiar la clave en el arbol de reporte lista");
    	}
    }

    /* Cierro el Arbol */
	this->arbol->cerrar();
    delete this->arbol;
    this->arbol = NULL;


    /* Debo cambiar las claves en el arbol de candidato */

   	/* Inicializo el arbol */
   	archivo = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_CANDIDATO));
   	this->arbol = new ArbolBMas();
   	if (!this->arbol->abrir(archivo)) throw VotoElectronicoExcepcion("No se abrio el arbol de candidato");

   	/* Busco todas las claves que tengan mi nombre de lista viejo */
   	list<RegistroArbol *> clavesEncontradasCandidato;
    if (!this->arbol->buscar(clavesEncontradasCandidato, claveOriginal, claveFinal)) {
    	this->arbol->cerrar();
      	delete this->arbol;
      	this->arbol = NULL;
       	return true;		// Si no habia ninguna coincidencia, retorno
    }

    /* Cambio los nombres por el nuevo nombre de lista */

    list<RegistroArbol *>::iterator it2;
    for (it2 = clavesEncontradasCandidato.begin(); it2 != clavesEncontradasCandidato.end(); it2++){
     	aConcatenar = claveModificada;
      	registroEnLista = *it2;
      	claveLista = registroEnLista->getClave();
        aux = claveLista.find_last_of("$");
       	aConcatenar.append(claveLista,aux,12);
       	if(!this->arbol->cambiarClave(claveLista,aConcatenar))
       		throw VotoElectronicoExcepcion("No se pudo cambiar la clave en el arbol de candidato");
    }

    /* Cierro el Arbol */
    this->arbol->cerrar();
    delete this->arbol;
    this->arbol = NULL;

    return true;
}


bool ABMentidades::bajaEleccion(Eleccion &eleccion)
{
    string clave = Utilidades::obtenerClaveEleccion(eleccion.getFecha(),eleccion.getCargo().getCargoPrincipal());
    bool bajaCorrecta = bajaEleccion(clave);
    if (bajaCorrecta) Logger::Eliminar(eleccion);
    return bajaCorrecta;
}


bool ABMentidades::bajaEleccion(string claveEleccion)
{
    //busca la clave en el arbol (supongo que ya recibí la clave concatenada y formateada)
    string archivo((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_ELECCION));
    this->arbol = new ArbolBMas();
    if (!this->arbol->abrir(archivo)) throw VotoElectronicoExcepcion("No se abrio el arbol de eleccion");


    long int IDEleccion = 0;
    if (this->arbol->buscar(claveEleccion,IDEleccion)){
        //Si existe, la borra del arbol de clave/Id y del hash de Id/offset
        //(baja lógica) y devuelve true
        this->arbol->eliminar(claveEleccion);
        this->arbol->cerrar();
        delete this->arbol;
        this->arbol = NULL;


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
    this->arbol->cerrar();
    delete this->arbol;
    this->arbol = NULL;
    return false;
}


bool ABMentidades::bajaDistrito(Distrito &distrito)
{
    string clave = Utilidades::obtenerClaveDistrito(distrito.getNombre());
    bool bajaCorrecta = bajaDistrito(clave);
    if (bajaCorrecta) Logger::Eliminar(distrito);
    return bajaCorrecta;
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
}


bool ABMentidades::bajaCargo(Cargo &cargo)
{
    string clave = Utilidades::obtenerClaveCargo(cargo.getCargoPrincipal());
    bool bajaCorrecta = bajaCargo(clave);
    if (bajaCorrecta) Logger::Eliminar(cargo);
    return bajaCorrecta;
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
    string clave = Utilidades::obtenerClaveVotante(votante.getDNI());
    bool bajaCorrecta = bajaVotante(clave);
    if (bajaCorrecta) Logger::Eliminar(votante);
    return bajaCorrecta;
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
    string clave = Utilidades::obtenerClaveLista(lista.getEleccion().getFecha(),lista.getEleccion().getCargo().getCargoPrincipal(),lista.getNombre());
    bool bajaCorrecta = bajaLista(clave);
    if (bajaCorrecta) Logger::Eliminar(lista);
    return bajaCorrecta;
}


bool ABMentidades::bajaLista(string claveLista)
{
    //busca la clave en el arbol (supongo que ya recibí la clave concatenada y formateada)
    string archivo((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_LISTA));
    this->arbol = new ArbolBMas();
    if (!this->arbol->abrir(archivo)) throw VotoElectronicoExcepcion("No se abrio el arbol de lista");


    long int IDLista = 0;
    if (this->arbol->buscar(claveLista,IDLista)){
        //Si existe, la borra del arbol de clave/Id y del hash de Id/offset
        //(baja lógica) y devuelve true
        this->arbol->eliminar(claveLista);
        this->arbol->cerrar();
        delete this->arbol;
        this->arbol = NULL;

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
    this->arbol->cerrar();
    delete this->arbol;
    this->arbol = NULL;
    return false;
}


bool ABMentidades::bajaCandidato(Candidato &candidato)
{
    string clave = Utilidades::obtenerClaveCandidato(candidato.getLista().getEleccion().getFecha(),candidato.getLista().getEleccion().getCargo().getCargoPrincipal(),candidato.getLista().getNombre(),candidato.getDNI());
    bool bajaCorrecta = bajaCandidato(clave);
    if (bajaCorrecta) Logger::Eliminar(candidato);
    return bajaCorrecta;
}


bool ABMentidades::bajaCandidato(string claveCandidato)
{
    //busca la clave en el arbol (supongo que ya recibí la clave concatenada y formateada)
    string archivo((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_CANDIDATO));
    this->arbol = new ArbolBMas();
    if (!this->arbol->abrir(archivo)) throw VotoElectronicoExcepcion("No se abrio el arbol de candidato");


    long int IDCandidato = 0;
    if (this->arbol->buscar(claveCandidato,IDCandidato)){
        //Si existe, la borra del arbol de clave/Id y del hash de Id/offset
        //(baja lógica) y devuelve true
        this->arbol->eliminar(claveCandidato);
        this->arbol->cerrar();
        delete this->arbol;
        this->arbol = NULL;


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
    //devuelve false si el candidato no existía
    this->arbol->cerrar();
    delete this->arbol;
    this->arbol = NULL;
    return false;
}
