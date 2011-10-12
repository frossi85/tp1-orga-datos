/*
 * TestEleccion.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#include "TestEleccion.h"

TestEleccion::TestEleccion() {

	this->clase_en_testeo="Eleccion";

}

void TestEleccion::comenzar(){

	if (this->testConstructor()){
		this->informarError("Constructor");
	}

	if(this->testLectura_y_Escritura()){
		this->informarError("de Lectura y Escritura");

	}

}

void TestEleccion::inicializar(){


}

bool TestEleccion::testConstructor(){

	bool error_encontrado=false;



	return error_encontrado;


}
bool TestEleccion::testLectura_y_Escritura(){

	bool error_encontrado=false;



	return error_encontrado;

}


TestEleccion::~TestEleccion() {
	// TODO Auto-generated destructor stub
}
