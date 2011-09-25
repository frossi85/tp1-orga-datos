#include "Eleccion.h"


Eleccion::Eleccion(string fecha, Cargo& cargo, Distrito primerDistrito) : _cargo(cargo)
{
	//TODO: Verificar q esto se asigne bien
	this->_distritos.push_back(&primerDistrito);
}

Eleccion::~Eleccion() {
	// TODO Auto-generated destructor stub
}

void Eleccion::agregarDistrito(Distrito distrito)
{
	this->_distritos.push_back(&distrito);
}


