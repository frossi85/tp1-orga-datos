/*
 * Test.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#include "Test.h"
#include <iostream>

Test::Test() {
	// TODO Auto-generated constructor stub

}

void Test::informarError(string metodo){

	cout<<"Error en Clase "<<this->clase_en_testeo<<" en metodo/s: "<<metodo<<endl;

}

Test::~Test() {
	// TODO Auto-generated destructor stub
}
