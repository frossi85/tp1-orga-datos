#include "Eleccion.h"

/* Constructor que no se deberia usar. No guardar algo contruido asi. Desp se saca si no es necesario.*/
Eleccion::Eleccion()
{
	this->_id = -1;
	this->_fecha = "";
	this->_cargo = NULL;
}


Eleccion::Eleccion(string fecha, Cargo cargo, Distrito primerDistrito)
{
	this->_id = ManejoIDs::obtenerIDnuevo(this->getClassName());
	this->_fecha = fecha;
	this->_cargo = new Cargo(cargo);
	this->_distritos.push_back(new Distrito(primerDistrito));
}


Eleccion::~Eleccion() {
	delete this->_cargo;
	int cantidad = this->_distritos.size();
	for(int i=0;i<cantidad;i++)	delete this->_distritos[i];
}


Eleccion::Eleccion(const Eleccion &eleccion) {
	this->_id = eleccion._id;
	this->_fecha = eleccion._fecha;
	this->_cargo = new Cargo(*(eleccion._cargo));
	int cantidad = eleccion._distritos.size();
	for(int i=0;i<cantidad;i++)
		this->_distritos.push_back(new Distrito(*(eleccion._distritos[i])));
}


void Eleccion::agregarDistrito(Distrito distrito)
{
	Distrito *dist = new Distrito(distrito);
	this->_distritos.push_back(dist);
}


long Eleccion::getId() {return _id;}


string Eleccion::getFecha() {return this->_fecha;}


Cargo& Eleccion::getCargo() {return *(this->_cargo);}


void Eleccion::setCargo(Cargo cargo) {
	if (this->_cargo != NULL)	delete this->_cargo;
	this->_cargo = new Cargo(cargo);
}

vector<Distrito *> Eleccion::getDistritos() {return this->_distritos;}


string Eleccion::getDescripcion(){
	return (this->_cargo->getCargoPrincipal() + "  " + this->_fecha);
}


void Eleccion::Imprimir()
{
	cout<<"Id Eleccion: " <<_id << endl;
	cout<<"Fecha Eleccion: " <<_fecha <<endl;
	cout<<"Cargos de la Eleccion: " << endl;
	this->_cargo->Imprimir();
}


void Eleccion::ImprimirDistritos()
{
	vector<Distrito *>::size_type cantidadDistritos = _distritos.size();
	cout << "Distritos de la eleccion: " << endl;
	for(vector<Distrito *>::size_type i = 0; i < cantidadDistritos; i++)
		_distritos[i]->Imprimir();
	cout << endl;
}


unsigned long int Eleccion::Guardar(ofstream & ofs)
{
	unsigned long int offset = ofs.tellp();

	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&_id), sizeof(_id));
	Utilidades::stringToFile(_fecha, ofs);

	//Se escribe la referencia al Cargo guardando su id
	long idCargo = this->_cargo->getId();
	ofs.write(reinterpret_cast<char *>(&idCargo), sizeof(idCargo));

	//Grabo la cantidad de distritos q tiene
	string::size_type cantidadDistritos = this->_distritos.size();
	ofs.write(reinterpret_cast<char *>(&cantidadDistritos), sizeof(cantidadDistritos));

	//Comienzo a grabar los ids de los distritos
	long idDistrito = 0;
	for(string::size_type i = 0; i < cantidadDistritos; i++){
		idDistrito = this->_distritos[i]->getId();
		ofs.write(reinterpret_cast<char *>(&idDistrito), sizeof(idDistrito));
	}

	return offset;
}


void Eleccion::Leer(ifstream & ifs, unsigned long int offset)
{
	// Me posiciono en el archivo
	ifs.seekg(offset,ios::beg);

	//Comienzo lectura de atributos
	ifs.read(reinterpret_cast<char *>(&_id), sizeof(_id));
	_fecha = Utilidades::stringFromFile(ifs);

	// Leo el id del cargo
	long idCargo = 0;
	ifs.read(reinterpret_cast<char *>(&idCargo), sizeof(idCargo));

	// Busco en el hash id_cargo/offset el offset de ese idCargo
	string id = Utilidades::toString(idCargo);
	string arch_registros((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcargo_regs>"));
	string arch_bloq_libres((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcargo_bloq_lib>"));
	string arch_tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcargo_tabla>"));
	hash_extensible *hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	RegistroIndice CargoBuscar(id,0);
	RegistroIndice *returnReg = hash->buscar(&CargoBuscar);
	if (returnReg == NULL) throw VotoElectronicoExcepcion("No se encuentra el id de cargo en el hash");
	offset = returnReg->getOffset();

	// Leo el cargo del archivo de cargos
//	DataAccess dataAccess;
	Cargo cargo;
//	dataAccess.Leer(cargo,offset);
	_cargo = new Cargo(cargo);
	delete hash;

	// Distritos: leo la cantidad de distritos
	string::size_type cantidadDistritos = 0;
	ifs.read(reinterpret_cast<char *>(&cantidadDistritos), sizeof(cantidadDistritos));

	// Levanto todos los ids de los ditritos
	long idVector[cantidadDistritos];
	ifs.read(reinterpret_cast<char *>(idVector),cantidadDistritos * sizeof(this->_id));

	// Busco en el hash id_distrito/offset el offset los id Distritos
	Distrito distrito;
	arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_iddistrito_regs>"));
	arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_iddistrito_bloq_lib>"));
	arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_iddistrito_tabla>"));
	hash = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
	for(string::size_type i = 0; i < cantidadDistritos; i++){
		id = Utilidades::toString(idVector[i]);
		RegistroIndice DistritoBuscar(id,0);
		returnReg = hash->buscar(&DistritoBuscar);
		if (returnReg == NULL) throw VotoElectronicoExcepcion("No se encuentra el id del distrito en el hash");
		offset = returnReg->getOffset();

		// Leo el distrito del archivo de cargos
//		dataAccess.Leer(distrito,offset);
		this->_distritos.push_back(new Distrito(distrito));	// Anda? No usar push_back(&distrito) xq eso esta muy mal.
	}
	delete hash;
}


inline string Eleccion::getURLArchivoDatos() {
	return ((*Configuracion::getConfig()).getValorPorPrefijo(Configuracion::URL_ELECCION));
}


string Eleccion::getClassName() {return "Eleccion";}
