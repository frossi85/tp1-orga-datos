/*
 * Votante.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Votante.h"

/* Constructor que no se deberia usar. No guardar algo contruido asi. Desp se saca si no es necesario.*/
Votante::Votante() {
	this->_dni = -1;
	this->_nombreYApellido = "";
	this->_clave = "";
	this->_domicilio = "";
	this->_distrito = NULL;
	this->_id = -1;
}

Votante::Votante(int dni, string nombreYApellido, string clave, string domicilio, Distrito distrito)
{
	this->_dni = dni;
	this->_nombreYApellido = nombreYApellido;
	this->_clave = clave;
	this->_domicilio = domicilio;
	this->_distrito = new Distrito(distrito);
	this->_id = 0;
}


Votante::Votante(const Votante &votante) {
	this->_dni = votante._dni;
	this->_clave = votante._clave;
	this->_domicilio = votante._domicilio;
	this->_id = votante._id;
	this->_nombreYApellido = votante._nombreYApellido;
	this->_distrito = new Distrito(*(votante._distrito));
	int cantidad = votante._elecciones.size();
	for(int i=0;i<cantidad;i++) this->_elecciones.push_back(new Eleccion(*(votante._elecciones[i])));
}


Votante::~Votante() {
	if (this->_distrito != NULL) {
		delete this->_distrito;
		this->_distrito = NULL;
	}
	this->vaciarVectorElecciones();
}


string Votante::getClave() {return this->_clave;}


long Votante::getId() {return _id;}


int Votante::getDNI() {return this->_dni;}


string Votante::getNombreYApellido() {return this->_nombreYApellido;}


string Votante::getDomicilio() {return this->_domicilio;}


Distrito & Votante::getDistrito() {return *(this->_distrito);}


void Votante::vaciarVectorElecciones() {
	int cantidad = this->_elecciones.size();
	for(int i=0;i<cantidad;i++) {
		if (this->_elecciones[i] != NULL) {
			delete this->_elecciones[i];
			this->_elecciones[i] = NULL;
		}
	}
	this->_elecciones.clear();
}


void Votante::agregarEleccion(Eleccion eleccion) {
	this->_elecciones.push_back(new Eleccion(eleccion));
}


vector<Eleccion *> Votante::getElecciones() { return this->_elecciones;}


bool Votante::cambiarClave(string claveAnterior, string claveNueva)
{
	if (claveAnterior == this->_clave) {
		this->_clave = claveNueva;
		return true;
	}
	return false;
}


void Votante::setDistrito(Distrito distrito)
{
	delete this->_distrito;
	this->_distrito = new Distrito(distrito);
}


void Votante::setDomicilio(string nuevo_domicilio){
	this->_domicilio=nuevo_domicilio;
}


void Votante::Imprimir()
{
	cout<<"Id Votante: " <<_id << endl;
	cout<<"DNI: "<<_dni<<endl;
	cout<<"Apellido y Nombre: "<<_nombreYApellido<<endl;
	cout<<"Clave: "<<_clave<<endl;
	cout<<"Domicilio: "<<_domicilio<<endl;
	cout<<"Distrito: "<<endl;
	(*(_distrito)).Imprimir();

	vector<Eleccion *>::size_type cantidadElecciones = _elecciones.size();

	cout << "Elecciones en las que ya voto: "<<endl;
	for(vector<Eleccion *>::size_type i = 0; i < cantidadElecciones; i++)
	{
		(*(_elecciones[i])).Imprimir();
		cout<<endl;
	}
}


unsigned long int Votante::Guardar(ofstream & ofs)
{
	unsigned long int offset = ofs.tellp();

	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&_id), sizeof(_id));
	ofs.write(reinterpret_cast<char *>(&_dni), sizeof(_dni));
	Utilidades::stringToFile(_nombreYApellido, ofs);
	Utilidades::stringToFile(_clave, ofs);
	Utilidades::stringToFile(_domicilio, ofs);

	//Se escribe la referencia al Distrito guardando su id
	long idDistrito = (*(_distrito)).getId();
	ofs.write(reinterpret_cast<char *>(&idDistrito), sizeof(idDistrito));

	//Aca se tendrian q guardar todos los ids(u offsets) de elecciones
	//O el offset dentro del archivo VotanteEleccion
	/* Leandro: por ahora voy a hacer lo primero, ya que todavía
	 * no hay un archivo VotanteEleccion, así no la complico.
	 * Si hace falta después lo cambiamos.
	 */

	//Grabo la cantidad de elecciones que tiene
	string::size_type cantidadElecciones = this->_elecciones.size();
	ofs.write(reinterpret_cast<char *>(&cantidadElecciones), sizeof(cantidadElecciones));

	//Grabo los IDs de las elecciones
	long idEleccion = 0;
	for(string::size_type i = 0; i < cantidadElecciones; i++){
		idEleccion = this->_elecciones[i]->getId();
		ofs.write(reinterpret_cast<char *>(&idEleccion), sizeof(idEleccion));
	}

	return offset;
}


void Votante::Leer(ifstream & ifs, unsigned long int offset)
{
	// Elimino atributos de la instancia
	if (this->_distrito != NULL) {
		delete this->_distrito;
		this->_distrito = NULL;
	}
	this->vaciarVectorElecciones();

	// Me posiciono en el archivo
	ifs.seekg(offset,ios::beg);

	//Comienzo lectura de atributos
	ifs.read(reinterpret_cast<char *>(&_id), sizeof(_id));
	ifs.read(reinterpret_cast<char *>(&_dni), sizeof(_dni));
	_nombreYApellido = Utilidades::stringFromFile(ifs);
	_clave = Utilidades::stringFromFile(ifs);
	_domicilio = Utilidades::stringFromFile(ifs);

	//Se lee el id del Distrito
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

	/*Distrito distrito; //si no funciona probar con un puntero a distrito

	string rutaArchivo = distrito.getURLArchivoDatos();
	ifstream ifsDatos(rutaArchivo.c_str(), ios::in | ios::binary);
	if(!ifsDatos.is_open())
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + distrito.getClassName());

	distrito.Leer(ifsDatos, offset);
	ifsDatos.close();
	_distrito = new Distrito(distrito);
	delete hashIDDistritos;
*/															// BORRAR SI LO DE ARRIBA FUNCIONA (MARITN)

	//Aca se tendrian q leer todos los ids(u offsets) de elecciones
	//O el offset dentro del archivo VotanteEleccion y cargar los distritos al array
	/* Leandro: lo mismo que puse en el guardar: por ahora voy a hacer lo primero, ya que todavía
	 * no hay un archivo VotanteEleccion, así no la complico.
	 * Si hace falta después lo cambiamos.
	 */

	// Leo la cantidad de elecciones
	string::size_type cantidadElecciones = 0;
	ifs.read(reinterpret_cast<char *>(&cantidadElecciones), sizeof(cantidadElecciones));

	// Levanto todos los ids de las elecciones
	long idVector[cantidadElecciones];
	ifs.read(reinterpret_cast<char *>(idVector),cantidadElecciones * sizeof(this->_id));

	// Busco en el hash id_eleccion/offset el offset los id Elecciones
	Eleccion eleccion;
	string arch_registros_elec = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_REGS));
	string arch_bloq_libres_elec = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_BLOQ_LIB));
	string arch_tabla_elec = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_TABLA));
	hash_extensible *hashIDElecciones = new hash_extensible(arch_registros_elec,arch_bloq_libres_elec,arch_tabla_elec);

	//cosas que se usan adentro del for
	string idEleccion;
	RegistroIndice *returnEleccion;
	RegistroIndice EleccionBuscar(idEleccion,0);

	for(string::size_type i = 0; i < cantidadElecciones; i++){
		idEleccion = Utilidades::toString(idVector[i]);
		EleccionBuscar.setClave(idEleccion);
		returnEleccion = hashIDElecciones->buscar(&EleccionBuscar);
		if (returnEleccion == NULL) throw VotoElectronicoExcepcion("No se encuentra el id de la eleccion en el hash");
		offset = returnEleccion->getOffset();

		// Leo la eleccion del archivo de elecciones;
		dataAccess.Leer(eleccion,offset);
		this->_elecciones.push_back(new Eleccion(eleccion));	// Anda? No usar push_back(&eleccion) xq eso esta muy mal.
	}
	delete hashIDElecciones;
}

int Votante::getTamanioEnDisco(){

	int tamanio=0;

	tamanio+=sizeof(this->_dni);
	tamanio+=sizeof(this->_id);
	tamanio+=sizeof(this->_distrito->getId());
	tamanio+=sizeof(this->_elecciones.size());

	if(this->_elecciones.size()>0){
		tamanio+=sizeof(this->_elecciones[0]->getId())*this->_elecciones.size();
	}

	//No se si las sentencias de abajo estan bien..
	tamanio+sizeof(this->_clave.size());
	tamanio+=sizeof(char)*this->_clave.size();

	tamanio+=sizeof(this->_domicilio.size());
	tamanio+=sizeof(char)*this->_domicilio.size();

	tamanio+=sizeof(this->_nombreYApellido.size());
	tamanio+=sizeof(char)*this->_nombreYApellido.size();



	return tamanio;
}

inline string Votante::getURLArchivoDatos()
{
	return (*Configuracion::getConfig()).getValorPorPrefijo(Configuracion::URL_VOTANTES);
}


string Votante::getClassName() {return "Votante";}
