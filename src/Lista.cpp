/*
 * Lista.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Lista.h"

/* Constructor que no se deberia usar. No guardar algo contruido asi. Desp se saca si no es necesario.*/
Lista::Lista()
{
	this->_eleccion = NULL;
	this->_nombre = "";
	this->_id = -1;
}


Lista::Lista(string nombre, Eleccion eleccion)
{

	this->_eleccion = new Eleccion(eleccion);
	this->_nombre = nombre;

	this->_id = 0;
}

Lista::Lista(const Lista &lista) {
	this->_id = lista._id;
	this->_nombre = lista._nombre;
	this->_eleccion = new Eleccion(*(lista._eleccion));
}


Lista::~Lista() {
	if (this->_eleccion != NULL) delete this->_eleccion;
}


long Lista::getId() {return _id;}


Eleccion& Lista::getEleccion() {return *(this->_eleccion);}


string Lista::getNombre() {return this->_nombre;}


void Lista::Imprimir()
{
	cout<<"Id Lista: " <<_id << endl;
	cout<< "Nombre Lista: " << _nombre << endl;
	cout << "Eleccion a la que se presenta: "<<endl;
	(*(_eleccion)).Imprimir();
	cout<<endl;
}


unsigned long int Lista::Guardar(ofstream & ofs)
{
	unsigned long int offset = ofs.tellp();

	//Comienzo escritura de atributos
	ofs.write(reinterpret_cast<char *>(&_id), sizeof(_id));
	Utilidades::stringToFile(_nombre, ofs);

	//Se escribe la referencia a la Eleccion guardando su id
	long idEleccion = (*(_eleccion)).getId();
	ofs.write(reinterpret_cast<char *>(&idEleccion), sizeof(idEleccion));

	//No se si va lo de abajo por q tendria sentido si se modifico
	//y se tendria q tener un flag q indique si se modifico algun atributo
	//es un quilombo no hacer lo de abajo, solo actualizar la referencia.
	//(*(_eleccion)).fueModificada();
	//DataAccess dataAccess;
	//dataAccess.Guardar(*(_eleccion));
	// RTA: NO NOS PUSIMOS, O POR LO MENOS YO, A PENSAR TANTO EN MODIFICACIONES..ESTOY TRATANDO DE QUE ANDEN LOS INSERTAR Y ELIMINAR
	// (MARTIN)
	return offset;
}


void Lista::Leer(ifstream & ifs, unsigned long int offset)
{
	//Comienzo lectura de atributos
	ifs.read(reinterpret_cast<char *>(&_id), sizeof(_id));
	_nombre = Utilidades::stringFromFile(ifs);

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
	DataAccess dataAccess;
	Eleccion eleccion;
	dataAccess.Leer(eleccion,offset);
	_eleccion = new Eleccion(eleccion);
	delete hashIDElecciones;

/*
	Eleccion eleccion; //si no funciona probar con un puntero a eleccion
	string rutaArchivo = eleccion.getURLArchivoDatos();
	ifstream ifsDatos(rutaArchivo.c_str(), ios::in | ios::binary);
	if(!ifsDatos.is_open())
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + eleccion.getClassName());
	eleccion.Leer(ifsDatos, offset);
	ifsDatos.close();
	_eleccion = new Eleccion(eleccion);
	delete hashIDElecciones;
*/                                            // BORRAR EL COMENTARIO SI ANDA COMO ESTA ARRIBA (MARTIN)
}


inline string Lista::getURLArchivoDatos() {
	return (*Configuracion::getConfig()).getValorPorPrefijo(Configuracion::URL_LISTA);
}


string Lista::getClassName() {return "Lista";}
