/*
 * Candidato.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Candidato.h"

/* Constructor que no se deberia usar. No guardar algo contruido asi. Desp se saca si no es necesario.*/
Candidato::Candidato() {
	this->_id = -1;
	this->_listaPropia =  NULL;
	this->_votante = NULL;
}


Candidato::Candidato(Votante votante, Lista lista) {
	this->_id = 0;
	this->_listaPropia =  new Lista(lista);
	this->_votante = new Votante(votante);
}


Candidato::Candidato(const Candidato &candidato) {
	this->_id = candidato._id;
	this->_listaPropia = new Lista(*(candidato._listaPropia));
	this->_votante = new Votante(*(candidato._votante));
}


Candidato::~Candidato() {
	if (this->_listaPropia != NULL)	{
		delete this->_listaPropia;
		this->_listaPropia = NULL;
	}
	if (this->_votante != NULL)	{
		delete this->_votante;
		this->_votante = NULL;
	}
}


long Candidato::getId() {return _id;}


int Candidato::getDNI(){return this->_votante->getDNI();}


string Candidato::getNombreYApellido(){return this->_votante->getNombreYApellido();}


Cargo& Candidato::getCargo() {return (this->_listaPropia->getEleccion().getCargo());}


Lista& Candidato::getLista() {return *(this->_listaPropia);}

int Candidato::getTamanioEnDisco(){
	int tamanio=0;

	tamanio+=sizeof(this->_id);
	tamanio+=sizeof(this->_listaPropia->getId());
	tamanio+=sizeof(this->_votante->getId());

	return tamanio;
}


void Candidato::setLista(Lista lista) {
	if (this->_listaPropia != NULL) delete this->_listaPropia;
	this->_listaPropia = new Lista(lista);
}


void Candidato::setCargo(Cargo cargo) {
	this->_listaPropia->getEleccion().setCargo(cargo);
}


void Candidato::Imprimir()
{
	cout<<"Id Candidato: " <<_id <<endl;
	cout << "Informacion del candidato: " << endl;
	(*(this->_votante)).Imprimir();

	cout<<"Lista del candidato: "<<endl;
	(*(_listaPropia)).Imprimir();
	cout<<endl;
}


unsigned long int Candidato::Guardar(ofstream & ofs)
{
	//TODO: capaz por cada puntero a una instancia de otra clase deberia tener el id(offset)
	//y en leer cargar eso en vez de la instancia en si, y hacer metodos como getLista()
	//y q si el puntero esta en NULL ahi cargarlo desde la BD y mantenerlo en memoria

	unsigned long int offset = ofs.tellp();

	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&_id), sizeof(_id));

	long idLista = (*(_listaPropia)).getId();
	ofs.write(reinterpret_cast<char *>(&idLista), sizeof(idLista));

	//Se escribe la referencia al Votante guardando su id
	long idVotante = (*(_votante)).getId();
	ofs.write(reinterpret_cast<char *>(&idVotante), sizeof(idVotante));

	return offset;
}


void Candidato::Leer(ifstream & ifs, unsigned long int offset)
{
	// Elimino atributos de la instancia
	if (this->_listaPropia != NULL)	{
		delete this->_listaPropia;
		this->_listaPropia = NULL;
	}
	if (this->_votante != NULL)	{
		delete this->_votante;
		this->_votante = NULL;
	}

	// Me posiciono en el archivo
	ifs.seekg(offset,ios::beg);

	//Comienzo lectura de atributos
	ifs.read(reinterpret_cast<char *>(&_id), sizeof(_id));

	// Leo el id de la lista asociada
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
	DataAccess dataAccess;
	Lista lista;
	dataAccess.Leer(lista,offset);
	_listaPropia = new Lista(lista);
	delete hashIDListas;

	// Leo la lista del archivo de listas
	/*Lista lista; //si no funciona probar con un puntero a distrito

	string rutaArchivo = lista.getURLArchivoDatos();
	ifstream ifsDatos(rutaArchivo.c_str(), ios::in | ios::binary);
	if(!ifsDatos.is_open())
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + lista.getClassName());

	lista.Leer(ifsDatos, offset);
	ifsDatos.close();
	_listaPropia = new Lista(lista);
	delete hashIDListas;*/  //BORRAR ESTE COMENTARIO SI LO DE ARRIBA ANDA BIEN

	//leo el id del votante
	long idVotante = 0;
	ifs.read(reinterpret_cast<char *>(&idVotante), sizeof(idVotante));

	// Busco en el hash id_lista/offset el offset de ese idLista
	string idVot = Utilidades::toString(idVotante);
	string arch_registros_vot((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_REGS));
	string arch_bloq_libres_vot((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_BLOQ_LIB));
	string arch_tabla_vot((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_TABLA));
	hash_extensible *hashIDVotantes = new hash_extensible(arch_registros_vot,arch_bloq_libres_vot,arch_tabla_vot);
	RegistroIndice VotanteBuscar(idVot,0);
	RegistroIndice *returnVotante = hashIDVotantes->buscar(&VotanteBuscar);
	if (returnVotante == NULL) throw VotoElectronicoExcepcion("No se encuentra el id de votante en el hash");
	offset = returnVotante->getOffset();

	// Leo el votante del archivo de votantes
	Votante votante;
	dataAccess.Leer(votante,offset);
	_votante = new Votante(votante);
	delete hashIDVotantes;


	// Leo el votante del archivo de votantes
/*	Votante votante; //si no funciona probar con un puntero a votante

	rutaArchivo = lista.getURLArchivoDatos();
	ifsDatos.open(rutaArchivo.c_str(), ios::in | ios::binary);
	if(!ifsDatos.is_open())
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + votante.getClassName());

	votante.Leer(ifsDatos, offset);
	ifsDatos.close();
	_votante = new Votante(votante);
	delete hashIDVotantes; */ //BORRAR ESTE COMENTARIO SI LO DE ARRIBA ANDA BIEN


	//DataAccess dataAccess;
	//Votante votante;
	//dataAccess.Leer(idVotante, votante);
	//_votante = &votante; //Ver si la instancia q creo aca se guarda en el puntero o se elimina al salir del metodo

	//Cargo cargo;
	//dataAccess.Leer(idCargo, cargo);
	//_cargoAPresentarse = &cargo; //Ver si la instancia q creo aca se guarda en el puntero o se elimina al salir del metodo

	//Lista lista;
	//dataAccess.Leer(idLista, lista);
	//_listaPropia = &lista; //Ver si la instancia q creo aca se guarda en el puntero o se elimina al salir del metodo
}


inline string Candidato::getURLArchivoDatos() {
	string url((*Configuracion::getConfig()).getValorPorPrefijo(Configuracion::URL_CANDIDATO));
	return url;
}


string Candidato::getClassName() {return "Candidato";}
