/*
 * Informe.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Informe.h"
#include <vector>
#include "DataAccess.h"
#include "DataGetter.h"

Informe::Informe(Eleccion& eleccion) {

	long id_eleccion=eleccion.getId();
	long id_distrito;
	long total_votos=0;
	Conteo *conteo;
	DataAccess data_access;

	vector<Distrito *> distritos=eleccion.getDistritos();

	vector<Distrito *>::size_type cantidadDistritos = distritos.size();


	cout<<"Resultados Para Eleccion de "<<eleccion.getDescripcion()<<endl;


	for(string::size_type i = 0; i < cantidadDistritos; i++)
	{

		//id_distrito=distritos[i]->getId();

		//Con los id de distrito y eleccion
		//buscar las Instancia de Conteo
		//que pertenezca a estos.
		//..
		//..
		//Facundo: No al final no se buscan por clave autonumerica, cuando te encuetre algo asi
		//hace en el DataAccess un metodo que sea algo como:
		//Conteo getConteoPorEleccionYDistrito(Eleccion, Distrito);
		//Por ahora hordodea el conteo que te devuelve para probar la impresion y despues, se implemtenta
		//la busqueda con el hash o el arbol, por ahora no te preocupes
		//
		// HECHO
		//


		vector<Conteo *> conteos=DataGetter::getConteos_por_Eleccion_y_Distrito(eleccion,(*distritos[i]));
		cout<<"Votos Para Distrito: "<<distritos[i]->getNombre()<<endl;
		total_votos+=this->mostrar_Conteos_por_Distrito(conteos);

	}

	cout<<"Total de votos en Eleccion: "<<total_votos<<endl;

}

long Informe::mostrar_Conteos_por_Distrito(vector<Conteo *> conteos){

	vector<Conteo *>::size_type i,cantidad_Conteos;
	cantidad_Conteos=conteos.size();
	Lista *lista;
	long total_votos=0;

	for (i=0;i<cantidad_Conteos;i++){

		*lista=conteos[i]->getLista();

		cout<<lista->getNombre()<<"  Votos: "<<conteos[i]->getVotos()<<endl;

		total_votos+=conteos[i]->getVotos();


	}

	cout<<"Total Votos en Distrito: "<<total_votos<<endl;

	return total_votos;

}

Informe::Informe(Distrito& distrito) {


	vector<Eleccion *> elecciones=DataGetter::getElecciones_por_Distrito(distrito);

	cout<<"Informe para Distito: "<<distrito.getNombre()<<endl;

	int cantidad_elecciones=elecciones.size();
	long total_votos=0;
	long total_votos_eleccion=0;

	for(int i=0;i<cantidad_elecciones;i++){

		cout<<"Informacion de Eleccion: "<<elecciones[i]->getDescripcion()<<endl;

		total_votos_eleccion=this->mostrar_Listas_por_Eleccion(*elecciones[i],distrito);

		total_votos+=total_votos_eleccion;
	}

	cout<<"Total de votos en Distrito: "<<total_votos<<endl;
}

long Informe::mostrar_Listas_por_Eleccion(Eleccion& eleccion,Distrito& distrito){
	long total_votos=0;

	vector<Lista *> listas=DataGetter::getListas_por_Eleccion(eleccion);
	int cantidad_listas=listas.size();

	cout<<"Lista...........Cantidad de Votos"<<endl;
	for (int i=0;i<cantidad_listas;i++){
		Conteo* conteo=DataGetter::getConteo(eleccion,*listas[i],distrito);

		cout<<listas[i]->getNombre()<<"..........."<<conteo->getVotos()<<endl;
		total_votos+=conteo->getVotos();
	}

	cout<<"Total Votos en Eleccion: "<<total_votos<<endl;

	return total_votos;

}


Informe::Informe(Lista& lista){

	Eleccion eleccion=lista.getEleccion();

	long total_votos=0;

	vector<Conteo *> conteos=DataGetter::getConteos_por_Lista_y_Eleccion(lista,eleccion);

	vector<Conteo *>::size_type cantidad_Conteos = conteos.size();


	cout<<"Resultados Para Lista "<<lista.getNombre()<<endl;
	cout<<"Distritos:"<<endl;

	for(string::size_type i = 0; i < cantidad_Conteos; i++)
	{

		//id_distrito=distritos[i]->getId();

		//Con los id de distrito, eleccion y lista
		//buscar el la Instancia de Conteo
		//que pertenezca a estos.
		//..
		//..
		Distrito* distrito;
		*distrito = conteos[i]->getDistrito();

		cout<<distrito->getNombre()<<" Votos: "<<conteos[i]->getVotos()<<endl;

		total_votos+=conteos[i]->getVotos();

	}
	cout<<"Total de votos: "<<total_votos<<endl;

}

Informe::~Informe() {
	// TODO Auto-generated destructor stub
}
