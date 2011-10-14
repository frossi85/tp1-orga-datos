/*
 * TestCandidato.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#include "TestCandidato.h"
#include "../Eleccion.h"
#include "../Distrito.h"

TestCandidato::TestCandidato() {

	this->clase_en_testeo="Candidato";

}

void TestCandidato::comenzar(){

	this->tituloTest();
	this->error_encontrado=false;


	if(this->testConstructor()){
		this->informarError("Constructor");
		this->error_encontrado=true;
	}

	if(this->testLectura_y_Escritura()){
		this->informarError("Lectura y/o Escritura");
		this->error_encontrado=true;
	}

	this->finalizarTest();

}


void TestCandidato::inicializar(){


	this->cargo=new Cargo("Gobernador");
	Distrito distrito("Quilmes");

	this->eleccion=new Eleccion("200110905",*this->cargo,distrito);

	this->lista=new Lista("Lista 001",*this->eleccion);




	//this->candidato=new Candidato(35000000,"Monica Lopez","1234","Callao 242",distrito,*this->lista,*this->cargo);

	this->votante=new Votante(35000000,"Monica Lopez","1234","Callao 424",distrito);
	this->candidato=new Candidato(*this->votante,*this->lista);
}

bool TestCandidato::testConstructor(){

	bool error=false;
	bool error_dni,error_nom,error_lista,error_cargo;
	this->inicializar();

	error_dni=!( this->candidato->getDNI()== 35000000);

	error_nom=!( this->candidato->getNombreYApellido()== "Monica Lopez" );

	error_lista=!(this->candidato->getLista().getNombre()==this->lista->getNombre());

	error_cargo=!(this->candidato->getCargo().getCargoPrincipal()==this->cargo->getCargoPrincipal());

	error=error_dni || error_nom || error_lista || error_cargo;

	this->liberarMemoria();
	return error;

}

bool TestCandidato::testLectura_y_Escritura(){

	bool error=false;





	return error;
}

void TestCandidato::liberarMemoria(){

	delete this->cargo;
	delete this->eleccion;
	delete this->lista;
	delete this->votante;
	delete this->candidato;

}

TestCandidato::~TestCandidato() {
	// TODO Auto-generated destructor stub
}
