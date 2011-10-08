/*
 * DataAccess.cpp
 *
 *  Created on: 03/10/2011
 *      Author: facundo
 */

#include "DataAccess.h"
#include <string>
#include <iostream>

DataAccess::DataAccess() : configuracion(*Configuracion::getConfig()){
}

DataAccess::~DataAccess() {
	// TODO Auto-generated destructor stub
}

long DataAccess::getIdPorNombre(char objeto, string clave)
{
	switch (objeto) {
	case 'd':
		//distrito -> por nombre
		return 1;
		break;
	case 'v':
		//votane por dni
		return 2;
		break;
	case 'e':
		//eleccion por fecha
		return 3;
		break;
	case 'l':
		//lista por nombre
		return 4;
		break;
	case 'c':
		//cargo por nombre
		return 4;
		break;
	case 'a':
		//candidato por dni
		return 4;
		break;
	}
	// SI no lo halla devuelve cero
}

//Recibe el id del grabable q quiero leer, obj es una instacia vacia a sobreescribir con los
//datos leidos de la BD dentro del metodo
void DataAccess::getPorId(long id, Grabable & obj)
{
	string rutaArchivo = obj.getURLArchivoDatos();
	ifstream ifs(rutaArchivo.c_str(), ios::binary);
	//Posicionarme en el ifstream mediante el hash, para luego leer desde ahi
	cout << "cartel " << rutaArchivo << endl;

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

vector<Conteo*> DataAccess::getConteos_por_Eleccion_y_Distrito(Eleccion &eleccion,Distrito &distrito){

	vector<Conteo *> resultado;

	// Se cargan los conteos de todas las Listas para una eleccion y un distrito


	//Para probar el metodo...
	Lista lista1("IPF",eleccion),lista2("UxI",eleccion);
	Conteo *conteo1;
	Conteo *conteo2;
	conteo1=new Conteo(eleccion,lista1,distrito);
	conteo2=new Conteo(eleccion,lista2,distrito);
	conteo1->incrementar();conteo1->incrementar(); conteo1->incrementar();
	conteo2->incrementar(); conteo2->incrementar();
	resultado.push_back(conteo1);
	resultado.push_back(conteo2);


	return resultado;


}


vector<Conteo*> DataAccess::getConteos_por_Lista_y_Eleccion(Lista &lista,Eleccion &eleccion){

	vector<Conteo *> resultado;

	//Se cargan todos los conteos de todos los distritos para una Lista en una Eleccion
	//...
	//..


	//Para probar el metodo...

	Distrito dist1("Avellaneda"),dist2("Lomas de Zamora");
	Conteo *conteo1,*conteo2;

	conteo1=new Conteo(eleccion,lista,dist1);
	conteo2=new Conteo(eleccion,lista,dist2);
	conteo1->incrementar();conteo1->incrementar(); conteo1->incrementar();
	conteo2->incrementar(); conteo2->incrementar();
	resultado.push_back(conteo1);
	resultado.push_back(conteo2);


	return resultado;


}
