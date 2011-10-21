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
	if (this->arbol->buscar(clave,offsetArbol)) return false;		// Caso de que ya existia.

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
	if (returnReg != NULL) return false;							// Ya existia en el hash, no se agrega

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
	if (returnReg != NULL) return false;							// Ya existia en el hash, no se agrega

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
	if (returnReg != NULL) return false;								// Ya existia en el hash, no se agrega

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
	if (this->arbol->buscar(clave,offsetArbol)) return false;				// Caso de que ya existia.

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
	if (this->arbol->buscar(clave,offsetArbol)) return false;					// Caso de que ya existia.

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
	return true;
}

void ABMentidades::agregarVoto(Lista &lista, Distrito &distrito) {
//void ABMentidades::agregarVoto(Votante &votante, Lista &lista, Distrito &distrito) {

	 //Usando los datos recibidos por parámetro busca el objeto conteo
    //en el árbol de reporte por distrito.
    this->arbol = new ArbolBMas();
    this->arbol->abrir((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_REPORTE_DISTRITO));

    //obtiene la clave concatenada para buscar
    string fecha = Utilidades::indexarFecha(lista.getEleccion().getFecha());
    string nombreCargo = lista.getEleccion().getCargo().getCargoPrincipal();

    string claveConcatenada = distrito.getNombre() + "$" + fecha + "$" + nombreCargo + "$" + lista.getNombre();
    Utilidades::formatearClave(claveConcatenada);
    long int offsetConteo;

    // Si el conteo no existe, se lanza una excepcion. O se puede llamar a crearConteo xq los q ya existian no se sobreescriben.
    // Llamar a conteo si se lanza muchas veces esta excepcion.
    if(!this->arbol->buscar(claveConcatenada, offsetConteo)) throw VotoElectronicoExcepcion("No se encontro el conteo correspondiente");

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
    ofstream ofs(rutaArchivo.c_str(), ios::out | ios::binary);
    if(!ofs.is_open())	throw VotoElectronicoExcepcion("No se pudo abrir el archivo de Conteo");
    ofs.seekp(offsetConteo,ios::beg);	// ESTE SEEK A MI NO ME FUNCIONABA EN OTRA CLASE. REVISAR SI ANDA. URGENTE!!!
    conteoExistente.Guardar(ofs);
    ofs.close();

    //TODO:Guardar una modificacion de votante para q se guarden la eleccion agregada a las
    //votadas por el votante
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


bool ABMentidades::modificacionEleccion(Eleccion &eleccion)
{
    return true;
}

/* Modificacion de Distrito:
 * Modificaciones posibles: nombre_distrito
 * El distrito que se le pasa por parametro debe tener el id correcto. Para esto la forma correcta para modificar un distrito es:
 * 1- Se le pregunta al admin por un nombre de distrito que quiere modificar.
 * 2- Se usa ObtenerRegistro(clave,aSobreescribir) para ver si existe el distrito pedido.
 * 3- En caso de existir, se debe preguntar al admin por el nuevo nombre que quiere darle al distrito,
 * y se le asigna el nuevo nombre al distrito "aSobreescribir", ya que ese distrito tiene el id correcto.
 * Es decir se haria: aSobreescribir.setNombre(nuevoNombre).
 * 4- Se llama a modificacionDistrito(aSobreescribir).
 * 5- Listo.
 */
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
		/* Retorno false ya que no se puede hacer la modificacion porque ya existia ese distrito */
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

	/* Chequeo que no sean el mismo registro */
	if (distrito.getNombre() == distritoRecuperado.getNombre()) {
		delete hash_auxiliar;
		hash_auxiliar = NULL;
		delete this->hash;
		this->hash = NULL;
		return true;
	}

	/* Comparo el tamanio en disco de los registros. Si el modificado es menor o igual al original, se sobreescribe.
	 * Si es mayor, se da de alta al final */
	int tamanioOriginal = distritoRecuperado.getTamanioEnDisco();
	int tamanioModificado = distrito.getTamanioEnDisco();
	if (tamanioOriginal >= tamanioModificado) {
		/* Sobreescribo el registro anterior */
		string rutaArchivo = distrito.getURLArchivoDatos();
		ofstream ofs(rutaArchivo.c_str(), ios::out | ios::binary);
		if(!ofs.is_open())	throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + distrito.getClassName());
		ofs.seekp(offset,ios::beg);
		distrito.Guardar(ofs);
		ofs.close();
	}
	else {
		/* Doy de alta al final del archivo y modifico el indice del hash id_distrito/offset */
		unsigned long int nuevoOffset = this->dataAccess.Guardar(distrito);
		RegistroIndice aGuardar(Utilidades::toString(distrito.getId()),nuevoOffset);
		this->hash->guardar(&aGuardar);
		this->hash->imprimir("./archivos/Otros/hash_iddistrito");
	}
	delete this->hash;
	this->hash = NULL;

	/* Cambio la clave en el hash distrito/id_distrito */

	/* Elimino la clave con el nombre de distrito viejo */
	string claveOriginal = Utilidades::obtenerClaveDistrito(distritoRecuperado.getNombre());
	RegistroIndice aEliminar(claveOriginal,0);
	if (!this->hash->borrar(&aEliminar)) throw VotoElectronicoExcepcion("Se quizo borrar una clave que no existia (modificacion distrito)");

	/* Inserto la clave modificada */
	RegistroIndice aModificar(claveModificada,distrito.getId());
	this->hash->guardar(&aModificar);

	delete hash_auxiliar;
	hash_auxiliar = NULL;
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
    string clave = Utilidades::obtenerClaveEleccion(eleccion.getFecha(),eleccion.getCargo().getCargoPrincipal());
    return bajaEleccion(clave);
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
    return false;
}

bool ABMentidades::bajaDistrito(Distrito &distrito)
{
    string clave = Utilidades::obtenerClaveDistrito(distrito.getNombre());
    return bajaDistrito(clave);
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
    return bajaCargo(clave);
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
    return bajaVotante(clave);
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
    return bajaLista(clave);
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
    return false;
}

bool ABMentidades::bajaCandidato(Candidato &candidato)
{
    string clave = Utilidades::obtenerClaveCandidato(candidato.getLista().getEleccion().getFecha(),candidato.getLista().getEleccion().getCargo().getCargoPrincipal(),candidato.getLista().getNombre(),candidato.getDNI());
    return bajaCandidato(clave);
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
