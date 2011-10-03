/*
 * DataAccess.cpp
 *
 *  Created on: 03/10/2011
 *      Author: facundo
 */

#include "DataAccess.h"

DataAccess::DataAccess() : configuracion(*Configuracion::getConfig()){
}

DataAccess::~DataAccess() {
	// TODO Auto-generated destructor stub
}

//Recibe el id del grabable q quiero leer, obj es una instacia vacia a sobreescribir con los
//datos leidos de la BD dentro del metodo
void DataAccess::getPorId(long id, Grabable & obj)
{
	//Obtener ruta del archivo de la configuracion por class name de Guardable o Logueables
	string rutaArchivo = "./distrito.db";

	ifstream ifs(rutaArchivo.c_str(), ios::binary);
	//Posicionarme en el ifstream mediante el hash, para luego leer desde ahi

	if(!ifs.is_open())  //o if(!ifs)
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de Distritos");

	//Comienzo escritura de atributos
	obj.Leer(ifs);

	ifs.close();
}

void DataAccess::Guardar(Grabable & obj)
{
	//Obtener ruta del archivo de la configuracion por class name de Guardable o Logueables
	string rutaArchivo = "./distrito.db";

	ofstream ofs(rutaArchivo.c_str(), ios::binary);
	//Posicionarme en el ofstream mediante el hash, para luego escribir desde ahi

	if(!ofs.is_open())  //o if(!ofs)
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de Distritos");

	//Comienzo escritura de atributos
	obj.Crear(ofs);

	ofs.close();

}


