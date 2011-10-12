/*
 * TestDistrito.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#include "TestDistrito.h"

TestDistrito::TestDistrito() {

	this->clase_en_testeo="Distrito";

}

void TestDistrito::comenzar(){

	if (this->testConstructor()){
		this->informarError("Constructor");
	}

}

bool TestDistrito::testConstructor(){

	bool error_encontrado=false;
	this->inicializar();

	error_encontrado=!( "Avellaneda"==this->distrito->getNombre() );

	this->liberarMemoria();
	return error_encontrado;

}

void TestDistrito::inicializar(){
	this->distrito=new Distrito("Avellaneda");

}

void TestDistrito::liberarMemoria(){
	delete this->distrito;
}

TestDistrito::~TestDistrito() {
	// TODO Auto-generated destructor stub
}
