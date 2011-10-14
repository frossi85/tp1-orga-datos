/*
 * DataGetter.cpp
 *
 *  Created on: 13/10/2011
 *      Author: administrador
 */

#include "DataGetter.h"

DataGetter::DataGetter() {
	// TODO Auto-generated constructor stub

}


vector<Conteo*> DataGetter::getConteos_por_Eleccion_y_Distrito(Eleccion &eleccion,Distrito &distrito){

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


vector<Conteo*> DataGetter::getConteos_por_Lista_y_Eleccion(Lista &lista,Eleccion &eleccion){

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



Votante* DataGetter::getVotante(const char dni[]){

	Votante *votante_resultante;

	//...
	//...

	Distrito distrito_prueba("Lanus");
	Votante *votante_prueba=new Votante(1111,"Juan Perez","1111","Corrientes 443",distrito_prueba);
	votante_resultante=votante_prueba;

	return votante_resultante;
}


vector<Lista *> DataGetter::getListas_por_Eleccion(Eleccion& eleccion){

	vector<Lista *> resultado;


	return resultado;

}


DataGetter::~DataGetter() {
	// TODO Auto-generated destructor stub
}
