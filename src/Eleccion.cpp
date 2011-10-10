#include "Eleccion.h"

Eleccion::Eleccion()
{
	this->_id = -1;
	this->_fecha = "";
	this->_cargo = NULL;
}

Eleccion::Eleccion(string fecha, Cargo & cargo, Distrito & primerDistrito)
{
	this->_id = 0;
	this->_fecha = fecha;
	this->_cargo = &cargo;
	//TODO: Verificar q esto se asigne bien
	this->_distritos.push_back(&primerDistrito);
}

Eleccion::~Eleccion() {
	// Supuestamente no tengo que borrar xq son referencias.
	//int cantidad = this->_distritos.size();
	//for(int i=0;i<cantidad;i++)	delete this->_distritos[i];
}

Eleccion::Eleccion(const Eleccion &eleccion) {
	this->_id = eleccion._id;
	this->_fecha = eleccion._fecha;
	this->_cargo = new Cargo(*eleccion._cargo);
	int cantidad = eleccion._distritos.size();
	this->_distritos = vector<Distrito*>(cantidad,NULL);
	for(int i=0;i<cantidad;i++)	this->_distritos[i] = new Distrito(*eleccion._distritos[i]);
}

void Eleccion::agregarDistrito(Distrito &distrito)
{
	this->_distritos.push_back(&distrito);
}


long Eleccion::getId()
{
	return _id;
}

vector<Distrito *> Eleccion::getDistritos(){
	return this->_distritos;

}

string Eleccion::getDescripcion(){

	return (this->_cargo->getCargoPrincipal() + "  " + this->_fecha);

}

void Eleccion::Imprimir()
{
	cout<<_id;
	cout<<endl;
	cout<<_fecha;
	cout<<endl;

	cout<<"Cargo de la Eleccion: ";
	(*(_cargo)).Imprimir();
	cout<<endl;

	//TODO: Si no funciona size_type usar un long
	vector<Distrito *>::size_type cantidadDistritos = _distritos.size();

	for(vector<Distrito *>::size_type i = 0; i < cantidadDistritos; i++)
	{
		(*(_distritos[i])).Imprimir();
		cout<<endl;
	}
}

void Eleccion::Guardar(ofstream & ofs)
{
	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&_id), sizeof(_id));
	Utilidades::stringToFile(_fecha, ofs);

	//Habria q verificar q no se guarde una Eleccion q se halla creado con Eleccion()
	//Se escribe la referencia al Cargo guardando su id
	long idCargo = (*(_cargo)).getId();
	ofs.write(reinterpret_cast<char *>(&idCargo), sizeof(idCargo));

	//Aca se tendrian q guardar todos los ids(u offsets) de distritos
	//O el offset dentro del archivo EleccionDistrito
}

void Eleccion::Leer(ifstream & ifs)
{
	//Comienzo lectura de atributos
	ifs.read(reinterpret_cast<char *>(&_id), sizeof(_id));
	_fecha = Utilidades::stringFromFile(ifs);

	//Habria q verificar q no se guarde una Eleccion q se halla creado con Eleccion()
	//Se escribe la referencia al Cargo guardando su id
	long idCargo = 0;
	ifs.read(reinterpret_cast<char *>(&idCargo), sizeof(idCargo));
	//DataAccess dataAccess;
	//Cargo cargo;
	//dataAccess.Leer(idCargo, cargo);
	//_cargo = &cargo; //Ver si la instancia q creo aca se guarda en el puntero o se elimina al salir del metodo

	//Aca se tendrian q leer todos los ids(u offsets) de distritos
	//O el offset dentro del archivo EleccionDistrito y cargar los distritos al array
}


inline string Eleccion::getURLArchivoDatos()
{
	//Arroja una excepcion si lo uso y encima no devuelve el valor correcto
	string url((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_eleccion>"));

	url = "./archivos/eleccion.db";

	return url;
}



string Eleccion::getClassName()
{
	return "Eleccion";
}


