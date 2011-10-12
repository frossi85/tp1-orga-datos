/*
 * testDataAccess.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#include "TestDataAccess.h"

TestDataAccess::TestDataAccess() {

	this->clase_en_testeo="DataAccess";

}

void TestDataAccess::comenzar(){
	this->inicializar();
	this->tituloTest();
	this->error_encontrado=false;



	this->finalizarTest();

}

void TestDataAccess::inicializar(){

	this->dataAccess=new DataAccess();

}


void TestDataAccess::liberarMemoria(){

	delete this->dataAccess;

}

TestDataAccess::~TestDataAccess() {
	this->liberarMemoria();
}
