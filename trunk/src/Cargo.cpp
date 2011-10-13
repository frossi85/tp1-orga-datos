#include "Cargo.h"
#include "ManejoIDs.h"

Cargo::Cargo(){
	this->cargoPrincipal = "";
	this->_id = -1;
}

Cargo::Cargo(string cargoPrincipal){
	this->cargoPrincipal = cargoPrincipal;
	//this->_id = 0;
	this->_id=ManejoIDs::obtenerIDnuevo(this->getClassName());
}

Cargo::~Cargo() { //TODO: En los destructores no hay q destruir strings averiguar si los vector si??
}

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

string Cargo::getCargoPrincipal()
{
	return this->cargoPrincipal;
}

vector<string> Cargo::getCargosSecundarios()
{
	//TODO: q hago aca si no existen cargos secundarios??
	return this->cargosSecundarios;
}

long Cargo::getId()
{
	return _id;
}

void Cargo::setCargoPrincipal(string cargoPrincipal)
{
	//TODO: Verificar si no es vacia y sino lanzar Excepcion
	this->cargoPrincipal = cargoPrincipal;
}

void Cargo::agregarCargoSecundario(string cargo)
{
	//TODO: Hay q verificar cargos duplicados??
	this->cargosSecundarios.push_back(cargo);
}

//Implementacion de interfaz Guardable
unsigned long int Cargo::Guardar(ofstream & ofs)
{
	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&_id), sizeof(_id));
	Utilidades::stringToFile(cargoPrincipal, ofs);

	//Grabo la cantidad de cargos secundarios q tiene
	string::size_type cantidadCargosSecundarios = cargosSecundarios.size();
	ofs.write(reinterpret_cast<char *>(&cantidadCargosSecundarios), sizeof(cantidadCargosSecundarios));
	//Comienzo a grabar los cargos secundarios
	for(string::size_type i = 0; i < cantidadCargosSecundarios; i++)
	{
		Utilidades::stringToFile(cargosSecundarios[i], ofs);
	}
}

void Cargo::Leer(ifstream & ifs, unsigned long int offset)
{
	//Comienzo lectura de atributos
	ifs.read(reinterpret_cast<char *>(&_id), sizeof(_id));
	cargoPrincipal = Utilidades::stringFromFile(ifs);

	//Grabo la cantidad de cargos secundarios q tiene
	string::size_type cantidadCargosSecundarios = 0;
	ifs.read(reinterpret_cast<char *>(&cantidadCargosSecundarios), sizeof(cantidadCargosSecundarios));
	//Comienzo a grabar los cargos secundarios
	for(string::size_type i = 0; i < cantidadCargosSecundarios; i++)
	{
		cargosSecundarios.push_back(Utilidades::stringFromFile(ifs));
	}

	ifs.close();

	Imprimir();
}

void Cargo::Imprimir()
{
	cout<<endl;
	cout<<"Id: ";
	cout<< _id;
	cout<<endl;
	cout<<"Cargos: ";
	cout<<cargoPrincipal;
	cout<<endl;
	for(string::size_type i=0; i<cargosSecundarios.size(); i++)
	{
		cout<<cargosSecundarios[i];
		cout<<endl;
	}
}

string Cargo::getURLArchivoDatos()
{
	return (*Configuracion::getConfig()).getValorPorPrefijo("<ruta_cargo>");
}

string Cargo::getClassName()
{
	return "Cargo";
}


