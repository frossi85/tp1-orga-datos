#include "Cargo.h"

Cargo::Cargo(string cargoPrincipal){
	this->cargoPrincipal = cargoPrincipal;
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



void Cargo::agregarCargoSecundario(string cargo)
{
	this->cargosSecundarios.push_back(cargo);
}

Cargo::~Cargo() {
	// TODO Auto-generated destructor stub
}


