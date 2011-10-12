/*
 * TestVotante.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#include "TestVotante.h"
#include <iostream>

using namespace std;

TestVotante::TestVotante() {

	this->clase_en_testeo="Votante";

}

void TestVotante::inicializar(){
	this->distrito=new Distrito("Lanus");
	this->votante=new Votante(3500000,"Juan Perez","1234","Corrientes 444",*distrito);

}

void TestVotante::comenzar(){

	cout<<"Comenzo Test de Votante"<<endl;

	if (this->testConstructor()){

		this->informarError("Constructor");
	}

	if (this->testSetters()){

		this->informarError("Setters");
	}

	if (this->testCambioClave()){

		this->informarError("Cambio de Clave");
	}
}

bool TestVotante::testConstructor(){

	bool error=false;
	bool error_dni,error_nom,error_clave,error_domicilio,error_distrito;
	this->distrito=new Distrito("Urquiza");
	this->votante=new Votante(35000000,"Manuel Gonzales","5678","Mitre 1200",*distrito);

	error_dni= !(35000000==this->votante->getDNI());
	error_nom= !("Manuel Gonzales"==this->votante->getNombreYApellido());
	error_clave=!("5678"==this->votante->getClave());
	error_domicilio=!("Mitre 1200"==this->votante->getDomicilio());
	error_distrito=!("Urquiza"==this->votante->getDistrito().getNombre());

	error= error_dni || error_nom || error_clave || error_domicilio || error_distrito;


	this->liberarMemoria();

	return error;

}

bool TestVotante::testCambioClave(){

	bool error=false;
	this->inicializar();

	string clave_nueva="0001";


	this->votante->cambiarClave(this->votante->getClave(),clave_nueva);

	error=!(clave_nueva==this->votante->getClave());

	this->liberarMemoria();

	return error;

}

bool TestVotante::testSetters(){
	bool error_encontrado=false;
	bool error_distrito,error_domicilio,error_id;
	this->inicializar();

	Distrito distrito_nuevo("Espeleta");
	this->votante->setDistrito(distrito_nuevo);

	error_distrito=!(this->votante->getDistrito().getNombre()=="Espeleta");

	this->votante->setDomicilio("Callao 888");
	error_domicilio=!( this->votante->getDomicilio()== "Callao 888");

	this->votante->setId(1111);
	error_id=!(this->votante->getId()== 1111);

	error_encontrado= error_distrito || error_domicilio || error_id;

	this->liberarMemoria();
	return error_encontrado;

}

void TestVotante::liberarMemoria(){

	delete this->distrito;
	delete this->votante;

}

TestVotante::~TestVotante() {

}
