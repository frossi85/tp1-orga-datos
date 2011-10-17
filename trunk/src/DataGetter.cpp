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
	conteo1=new Conteo(lista1,distrito);
	conteo2=new Conteo(lista2,distrito);
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

	conteo1=new Conteo(lista,dist1);
	conteo2=new Conteo(lista,dist2);
	conteo1->incrementar();conteo1->incrementar(); conteo1->incrementar();
	conteo2->incrementar(); conteo2->incrementar();
	resultado.push_back(conteo1);
	resultado.push_back(conteo2);


	return resultado;


}



vector<Eleccion *> DataGetter::getElecciones_por_Distrito(Distrito& distrito){
	vector<Eleccion *> elecciones;



	return elecciones;


}



Conteo* DataGetter::getConteo(Eleccion& eleccion,Lista& lista, Distrito& distrito){

	Conteo *conteo_resultante;



	return conteo_resultante;

}


Votante* DataGetter::getVotante(const string dni){

	Votante *votante_resultante;

	//...
	//...

	Distrito distrito_prueba("Lanus");
	Votante *votante_prueba=new Votante(1111,"Juan Perez","tp","Corrientes 443",distrito_prueba);
	votante_resultante=votante_prueba;

	return votante_resultante;
}


vector<Lista *> DataGetter::getListas_por_Eleccion(Eleccion& eleccion){

	vector<Lista *> resultado;


	//Para probar

	Lista *l1,*l2,*l3;
	l1= new Lista("Proyecto Sur",eleccion);
	l2= new Lista("Pro",eleccion);
	l3= new Lista("Frente Amplio Progresista",eleccion);

	resultado.push_back(l1);
	resultado.push_back(l2);
	resultado.push_back(l3);

	return resultado;

}

vector<Eleccion *> DataGetter::getElecciones_por_Votante(Votante &votante){

	vector<Eleccion *> elecciones_resultado;



	//Para Probar Metodo
	Cargo cargo1("Presidente"),cargo2("Gobernador");
	Distrito distrito("Lanus");

	Eleccion *e1,*e2;

	e1= new Eleccion("20111023",cargo1,distrito);
	e2= new Eleccion("20111023",cargo2,distrito);

	elecciones_resultado.push_back(e1);
	elecciones_resultado.push_back(e2);

	return elecciones_resultado;


}


DataGetter::~DataGetter() {
	// TODO Auto-generated destructor stub
}
