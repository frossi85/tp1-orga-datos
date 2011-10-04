#include "Cargo.h"

Cargo::Cargo(){
	this->cargoPrincipal = "";
}

Cargo::Cargo(string cargoPrincipal){
	this->cargoPrincipal = cargoPrincipal;
}

Cargo::~Cargo() { //TODO: En los destructores no hay q destruir strings averiguar si los vector si??
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
void Cargo::Guardar(ofstream & ofs)
{
	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&id), sizeof(id));
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

void Cargo::Leer(ifstream & ifs)
{
	//Comienzo lectura de atributos
	ifs.read(reinterpret_cast<char *>(&id), sizeof(id));
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
	cout<< id;
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
	//Arroja una excepcion si lo uso y encima no devuelve el valor correcto
	string url((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_cargo>"));

	url = "./cargo.db";

	return url;
}

string Cargo::getClassName()
{
	return "Cargo";
}


