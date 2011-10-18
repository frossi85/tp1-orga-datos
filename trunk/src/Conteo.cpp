/*
 * Conteo.cpp
 *
 *  Created on: 24/09/2011
 *      Author: facundo
 */

#include "Conteo.h"
#include "ArbolBMas.h"

Conteo::Conteo(Lista& lista, Distrito& distrito) : _distrito(&distrito), _lista(&lista), _eleccion(&(lista.getEleccion())){
	this->_cantidad = 1;
}

Conteo::Conteo(const Conteo &conteo){
	this->_distrito = new Distrito(*(conteo._distrito));
	this->_lista = new Lista(*(conteo._lista));
	this->_eleccion = new Eleccion(*(conteo._eleccion));
	this->_cantidad = conteo._cantidad;
}

Conteo::Conteo(){
    this->_distrito = NULL;
    this->_lista = NULL;
    this->_eleccion = NULL;
    this->_cantidad = 0;
}

Conteo::~Conteo() {
	if (this->_distrito != NULL) {
		delete this->_distrito;
		this->_distrito = NULL;
	}
	if (this->_lista != NULL) {
		delete this->_lista;
		this->_lista = NULL;
	}
	if (this->_eleccion != NULL) {
		delete this->_eleccion;
		this->_eleccion = NULL;
	}
}

void Conteo::incrementar(){	this->_cantidad++;}

long Conteo::getVotos(){ return _cantidad; }

Lista& Conteo::getLista(){ return *(this->_lista); }

Distrito& Conteo::getDistrito(){ return *(this->_distrito); }


unsigned long int Conteo::Guardar(ofstream & ofs){

	unsigned long int offset = ofs.tellp();

	// Comienzo escritura de atributos

	//Se escribe la referencia al Distrito guardando su id
	long idDistrito = this->_distrito->getId();
	ofs.write(reinterpret_cast<char *>(&idDistrito), sizeof(idDistrito));

	//Se escribe la referencia al Lista guardando su id
	long idLista = this->_lista->getId();
	ofs.write(reinterpret_cast<char *>(&idLista), sizeof(idLista));

	//Se escribe la referencia al Eleccion guardando su id
	long idEleccion = this->_eleccion->getId();
	ofs.write(reinterpret_cast<char *>(&idEleccion), sizeof(idEleccion));

	ofs.write(reinterpret_cast<char *>(&_cantidad), sizeof(_cantidad));

	return offset;
}

void Conteo::Leer(ifstream & ifs, unsigned long int offset){

	// Elimino atributos de la instancia
	if (this->_distrito != NULL) {
		delete this->_distrito;
		this->_distrito = NULL;
	}
	if (this->_lista != NULL) {
		delete this->_lista;
		this->_lista = NULL;
	}
	if (this->_eleccion != NULL) {
		delete this->_eleccion;
		this->_eleccion = NULL;
	}

	// Me posiciono en el archivo
	ifs.seekg(offset,ios::beg);

	//Comienzo lectura de atributos

	// Leo el id del distrito
	long idDistrito = 0;
	ifs.read(reinterpret_cast<char *>(&idDistrito), sizeof(idDistrito));

	// Busco en el hash id_distrito/offset el offset de ese idDistrito
	string idDist = Utilidades::toString(idDistrito);
	string arch_registros_dist((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_REGS));
	string arch_bloq_libres_dist((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_BLOQ_LIB));
	string arch_tabla_dist((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_TABLA));
	hash_extensible *hashIDDistritos = new hash_extensible(arch_registros_dist,arch_bloq_libres_dist,arch_tabla_dist);
	RegistroIndice DistritoBuscar(idDist,0);
	RegistroIndice *returnDistrito = hashIDDistritos->buscar(&DistritoBuscar);
	if (returnDistrito == NULL) throw VotoElectronicoExcepcion("No se encuentra el id de distrito en el hash");
	offset = returnDistrito->getOffset();

	// Leo el distrito del archivo de distritos
	DataAccess dataAccess;
	Distrito distrito;
	dataAccess.Leer(distrito,offset);
	_distrito = new Distrito(distrito);
	delete hashIDDistritos;


	// Leo el id de la lista
	long idLista = 0;
	ifs.read(reinterpret_cast<char *>(&idLista), sizeof(idLista));

	// Busco en el hash id_lista/offset el offset de ese idLista
	string idLis = Utilidades::toString(idLista);
	string arch_registros_lis((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDLISTA_REGS));
	string arch_bloq_libres_lis((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDLISTA_BLOQ_LIB));
	string arch_tabla_lis((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDLISTA_TABLA));
	hash_extensible *hashIDListas = new hash_extensible(arch_registros_lis,arch_bloq_libres_lis,arch_tabla_lis);
	RegistroIndice ListaBuscar(idLis,0);
	RegistroIndice *returnLista = hashIDListas->buscar(&ListaBuscar);
	if (returnLista == NULL) throw VotoElectronicoExcepcion("No se encuentra el id de lista en el hash");
	offset = returnLista->getOffset();

	// Leo la lista del archivo de listas
	Lista lista;
	dataAccess.Leer(lista,offset);
	_lista = new Lista(lista);
	delete hashIDListas;


	// Leo el id de la eleccion
	long idEleccion = 0;
	ifs.read(reinterpret_cast<char *>(&idEleccion), sizeof(idEleccion));

	// Busco en el hash id_eleccion/offset el offset de ese idEleccion
	string idElec = Utilidades::toString(idEleccion);
	string arch_registros_elec((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_REGS));
	string arch_bloq_libres_elec((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_BLOQ_LIB));
	string arch_tabla_elec((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_TABLA));
	hash_extensible *hashIDElecciones = new hash_extensible(arch_registros_elec,arch_bloq_libres_elec,arch_tabla_elec);
	RegistroIndice EleccionBuscar(idElec,0);
	RegistroIndice *returnEleccion = hashIDElecciones->buscar(&EleccionBuscar);
	if (returnEleccion == NULL) throw VotoElectronicoExcepcion("No se encuentra el id de eleccion en el hash");
	offset = returnEleccion->getOffset();

	// Leo la eleccion del archivo de elecciones
	Eleccion eleccion;
	dataAccess.Leer(eleccion,offset);
	_eleccion = new Eleccion(eleccion);
	delete hashIDElecciones;


	ifs.read(reinterpret_cast<char *>(&_cantidad), sizeof(_cantidad));
}

inline string Conteo::getURLArchivoDatos(){
	return ((*Configuracion::getConfig()).getValorPorPrefijo(Configuracion::URL_CONTEO));
}

string Conteo::getClassName(){return "Conteo";}

void Conteo::AgregarVoto(Lista& lista, Distrito& distrito){
    //Usando los datos recibidos por parámetro busca el objeto conteo
    //en el árbol de reporte por distrito.
    ArbolBMas *arbolDistrito = new ArbolBMas();
    arbolDistrito->abrir(RUTA_ARBOL_REPORTE_DISTRITO);

    //obtiene la clave concatenada para buscar
    string fecha = Utilidades::indexarFecha(lista.getEleccion().getFecha());
    string nombreCargo = lista.getEleccion().getCargo().getCargoPrincipal();

    string claveConcatenada = distrito.getNombre() +"$" +fecha +"$" +nombreCargo +"$" +lista.getNombre();
    Utilidades::formatearClave(claveConcatenada);
    long int offsetConteo;

    //Si el conteo no existe, le da de alta con cantidad = 1 y
    //lo indexa en los 3 árboles de índices para reportes, y termina
    if(!arbolDistrito->buscar(claveConcatenada, offsetConteo)){

       Conteo conteoNuevo(lista, distrito);
       DataAccess dataAccess;
       offsetConteo = dataAccess.Guardar(conteoNuevo);

       //indexa en árbol de reporte por distrito:
       arbolDistrito->agregar(claveConcatenada, offsetConteo);
       arbolDistrito->cerrar();
       delete arbolDistrito;

       //indexa en árbol de reporte por lista:
       ArbolBMas *arbolLista = new ArbolBMas();
       arbolLista->abrir(RUTA_ARBOL_REPORTE_LISTA);

       string claveArbolLista = fecha +"$" +nombreCargo +"$" +lista.getNombre() +"$" +distrito.getNombre();
       Utilidades::formatearClave(claveArbolLista);

       arbolLista->agregar(claveArbolLista, offsetConteo);
       arbolLista->cerrar();
       delete arbolLista;

       //indexa en árbol de reporte por eleccion:
       ArbolBMas *arbolEleccion = new ArbolBMas();
       arbolEleccion->abrir(RUTA_ARBOL_REPORTE_ELECCION);


       string claveArbolEleccion =  fecha +"$" +nombreCargo +"$" +distrito.getNombre() +"$" +lista.getNombre();
       Utilidades::formatearClave(claveArbolEleccion);

       arbolEleccion->agregar(claveArbolEleccion, offsetConteo);
       arbolEleccion->cerrar();
       delete arbolEleccion;

       return;
    }

    arbolDistrito->cerrar();
    delete arbolDistrito;

    //Si ya existía, lo lee, incrementa en 1 su cantidad, y guarda
    //el cambio (en el archivo de registros variables)
    
    //(en este caso no puedo usar el Guardar de DataAccess, porque solo
    //guarda al final, en vez de sobreescribirlo, así que eso lo hago a mano).
    DataAccess dataAccess;
    Conteo *conteoExistente = NULL;

    dataAccess.Leer(*conteoExistente, offsetConteo);
    conteoExistente->incrementar();

    //sobreescribe el registro
    string rutaArchivo = conteoExistente->getURLArchivoDatos();
    ofstream ofs(rutaArchivo.c_str(), ios::out | ios::binary);
    if(!ofs.is_open())
	throw VotoElectronicoExcepcion("No se pudo abrir el archivo de Conteo");
    ofs.seekp(offsetConteo);
    conteoExistente->Guardar(ofs);
    ofs.close();
}

void Conteo::Imprimir(){

    cout << "Cantidad de votos: " << this->_cantidad << endl;
    cout << "Lista: " << endl;
    this->_lista->Imprimir();
    cout << "Distrito: " << endl;
    this->_distrito->Imprimir();
    cout << "Eleccion: " << endl;
    this->_eleccion->Imprimir();
}
