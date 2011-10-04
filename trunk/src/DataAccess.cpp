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

	//Comienzo Lectura de atributos
	//Primero como no tengo el hash ni el arbol, hacer una busqueda secuencial desde el principio
	//del archivo leyendo un registro y verificando si es el q busco
	//Asi podria probar toda la aplicacion sin arbol ni hash

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
	//Mientras no tenga el hash ni el arbol, situarme al final del archivo con ofstream y
	//grabar lo nuevo al final
	//Para ahorrarme problemas de actualizacion por ahora solo trabajar con crear al final y leer
	//no usar modificaciones

	obj.Guardar(ofs);

	Logger::Alta(obj); //Se tiene q logguear alta y modificacion, ver como lo valido

	ofs.close();
}

void DataAccess::Eliminar(Grabable & obj)
{
	string rutaArchivo = obj.getURLArchivoDatos();

	//NO USAR ELEMINAR HASTA NO TENER EL HASH o EL ARBOL

	ofstream ofs(rutaArchivo.c_str(), ios::binary);
	//Posicionarme en el ofstream mediante el hash, para luego borrar el registro
	//Luego borrar del hash el registro

	if(!ofs.is_open())  //o if(!ofs)
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + obj.getClassName());

	//TODO: Eliminar le corresponde al registro o al bloque q reacomoda registros??
	//obj.Eliminar(ofs);

	Logger::Eliminar(obj); //Se tiene q logguear alta y modificacion, ver como lo valido

	ofs.close();
}


