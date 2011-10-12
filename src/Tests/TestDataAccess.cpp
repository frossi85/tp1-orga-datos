/*
 * testDataAccess.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#include "TestDataAccess.h"

TestDataAccess::TestDataAccess() {
	// TODO Auto-generated constructor stub

}

void TestDataAccess::comenzar(){
	this->inicializar();




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
