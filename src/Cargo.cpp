#include "Cargo.h"


/* Constructor que no se deberia usar. No guardar algo contruido asi. Desp se saca si no es necesario.*/
Cargo::Cargo(){
	this->cargoPrincipal = "";
	this->_id = -1;
}


Cargo::Cargo(string cargoPrincipal){
	this->cargoPrincipal = cargoPrincipal;
	this->_id = ManejoIDs::obtenerIDnuevo(this->getClassName());
}


Cargo::~Cargo() {}


Cargo::Cargo(const Cargo &cargo){
	this->_id = cargo._id;
	this->cargoPrincipal = cargo.cargoPrincipal;
	int cantidad = cargo.cargosSecundarios.size();
	this->cargosSecundarios = vector<string>();
	string a_insertar;
	for(int i=0;i<cantidad;i++)	{
		a_insertar = cargo.cargosSecundarios[i];
		this->cargosSecundarios.push_back(a_insertar);
	}
}


string Cargo::getCargoPrincipal() {return this->cargoPrincipal;}


vector<string> Cargo::getCargosSecundarios() {return this->cargosSecundarios;}


long Cargo::getId() {return _id;}


void Cargo::agregarCargoSecundario(string cargo) {this->cargosSecundarios.push_back(cargo);}


//Implementacion de interfaz Guardable
unsigned long int Cargo::Guardar(ofstream & ofs)
{
	unsigned long int offset = ofs.tellp();

	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&_id), sizeof(_id));
	Utilidades::stringToFile(cargoPrincipal, ofs);

	//Grabo la cantidad de cargos secundarios q tiene
	string::size_type cantidadCargosSecundarios = cargosSecundarios.size();
	ofs.write(reinterpret_cast<char *>(&cantidadCargosSecundarios), sizeof(cantidadCargosSecundarios));

	//Comienzo a grabar los cargos secundarios
	for(string::size_type i = 0; i < cantidadCargosSecundarios; i++)
		Utilidades::stringToFile(cargosSecundarios[i], ofs);

	return offset;
}


void Cargo::Leer(ifstream & ifs, unsigned long int offset)
{
	// Me posiciono en el archivo
	ifs.seekg(offset,ios::beg);

	//Comienzo lectura de atributos
	ifs.read(reinterpret_cast<char *>(&_id), sizeof(_id));
	cargoPrincipal = Utilidades::stringFromFile(ifs);

	//Leo la cantidad de cargos secundarios q tiene
	string::size_type cantidadCargosSecundarios = 0;
	ifs.read(reinterpret_cast<char *>(&cantidadCargosSecundarios), sizeof(cantidadCargosSecundarios));

	//Comienzo a leer los cargos secundarios
	for(string::size_type i = 0; i < cantidadCargosSecundarios; i++)
		cargosSecundarios.push_back(Utilidades::stringFromFile(ifs));
}


void Cargo::Imprimir()
{
	cout<<"Id Cargo: " << _id <<endl;
	cout<<"Cargo Principal: " << cargoPrincipal <<endl;
	for(string::size_type i=0; i<cargosSecundarios.size(); i++)
		cout<< "Cargo Secundario: " << cargosSecundarios[i] <<endl;
}


string Cargo::getURLArchivoDatos() {return (*Configuracion::getConfig()).getValorPorPrefijo(Configuracion::URL_CARGO);}


string Cargo::getClassName() {return "Cargo";}
