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

/*Distrito *DataAccess::getDistrito(string nombre) {
	if (d!=NULL) {
		return d;
	} else {													QUE ES ESTO? DE DONDE SALE "d"??
		d = new Distrito("distr");
		return d;
	}
}*/

//Recibe el id del grabable q quiero leer, obj es una instacia vacia a sobreescribir con los
//datos leidos de la BD dentro del metodo
void DataAccess::Leer(Grabable & obj, unsigned long int offset)
{
	string rutaArchivo = obj.getURLArchivoDatos();
	ifstream ifs(rutaArchivo.c_str(), ios::in | ios::binary);
	if(!ifs.is_open())
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + obj.getClassName());

	obj.Leer(ifs, offset);

	ifs.close();
}

unsigned long int DataAccess::Guardar(Grabable & obj)
{
	string rutaArchivo = obj.getURLArchivoDatos();
	ofstream ofs(rutaArchivo.c_str(), ios::out | ios::app | ios::binary);	// abro para escribir siempre al final (ios::app)
	if(!ofs.is_open())
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de " + obj.getClassName());

	unsigned long int offset = obj.Guardar(ofs);

	Logger::Alta(obj); //Se tiene q logguear alta y modificacion, ver como lo valido

	ofs.close();

	return offset;
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



Votante* DataAccess::getVotante(const char dni[]){

	Votante *votante_resultante;

	//...
	//...

	Distrito distrito_prueba("Lanus");
	Votante *votante_prueba=new Votante(1111,"Juan Perez","1111","Corrientes 443",distrito_prueba);
	votante_resultante=votante_prueba;

	return votante_resultante;
}

