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
	string rutaArchivo = obj.getURLArchivoDatos();
	ifstream ifs(rutaArchivo.c_str(), ios::binary);
	//Posicionarme en el ifstream mediante el hash, para luego leer desde ahi

	if(!ifs.is_open())  //o if(!ifs)
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + obj.getClassName());

	//Comienzo escritura de atributos
	obj.Leer(ifs);

	ifs.close();
}

//Separar en Modificar y Crear, o validar con el has si existe o no y loggear una u otra accion
void DataAccess::Guardar(Grabable & obj)
{
	string rutaArchivo = obj.getURLArchivoDatos();

	ofstream ofs(rutaArchivo.c_str(), ios::binary);
	//Posicionarme en el ofstream mediante el hash, para luego escribir desde ahi

	if(!ofs.is_open())  //o if(!ofs)
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + obj.getClassName());

	//Comienzo escritura de atributos
	obj.Crear(ofs);

	Logger::Alta(obj); //Se tiene q logguear alta y modificacion, ver como lo valido

	ofs.close();
}

void DataAccess::Eliminar(Grabable & obj)
{
	string rutaArchivo = obj.getURLArchivoDatos();

	ofstream ofs(rutaArchivo.c_str(), ios::binary);
	//Posicionarme en el ofstream mediante el hash, para luego borrar el registro
	//Luego borrar del hash el registro

	if(!ofs.is_open())  //o if(!ofs)
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + obj.getClassName());

	//Comienzo escritura de atributos

	//Eliminar le corresponde al registro o al bloque q reacomode registros
	//obj.Eliminar(ofs);

	Logger::Eliminar(obj); //Se tiene q logguear alta y modificacion, ver como lo valido

	ofs.close();
}


