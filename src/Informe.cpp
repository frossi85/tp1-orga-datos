/*
 * Informe.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Informe.h"
#include <vector>

Informe::Informe(Eleccion& eleccion) {

	long id_eleccion=eleccion.getId();
	long id_distrito;
	long total_votos=0;
	Conteo *conteo;


	vector<Distrito *> distritos=eleccion.getDistritos();

	vector<Distrito *>::size_type cantidadDistritos = distritos.size();


	cout<<"Resultados Para Eleccion de "<<eleccion.getDescripcion()<<endl;


	for(string::size_type i = 0; i < cantidadDistritos; i++)
	{

		id_distrito=distritos[i]->getId();

		//Con los id de distrito y eleccion
		//buscar las Instancia de Conteo
		//que pertenezca a estos.
		//..
		//..


		cout<<distritos[i]->getNombre()<<" Votos: "<<conteo->getVotos()<<endl;
		total_votos+=conteo->getVotos();

	}

	cout<<"Total de votos: "<<total_votos<<endl;

}

Informe::Informe(Distrito& distrito) {
	// TODO Auto-generated constructor stub

}

Informe::Informe(Lista& lista){

	Eleccion eleccion=lista.getEleccion();
	Conteo *conteo;

	long id_distrito;
	long total_votos=0;

	vector<Distrito *> distritos=eleccion.getDistritos();

	vector<Distrito *>::size_type cantidadDistritos = distritos.size();


	cout<<"Resultados Para Lista "<<lista.getNombre()<<endl;


	for(string::size_type i = 0; i < cantidadDistritos; i++)
	{

		id_distrito=distritos[i]->getId();

		//Con los id de distrito, eleccion y lista
		//buscar el la Instancia de Conteo
		//que pertenezca a estos.
		//..
		//..


		cout<<distritos[i]->getNombre()<<" Votos: "<<conteo->getVotos()<<endl;
		total_votos+=conteo->getVotos();

	}
	cout<<"Total de votos: "<<total_votos<<endl;

}

Informe::~Informe() {
	// TODO Auto-generated destructor stub
}
