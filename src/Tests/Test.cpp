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

	cout<<"**** Error en Clase "<<this->clase_en_testeo<<" en metodo/s: "<<metodo<<endl;

}

void Test::tituloTest(){
	cout<<"---------------------------------------"<<endl;
	cout<<"Se inicia el Test para "<<this->clase_en_testeo<<endl;
}

void Test::finalizarTest(){

	if(this->error_encontrado){

		cout<<"Se encontraron Errores para "<<this->clase_en_testeo<<endl<<endl;

	}else{

		cout<<"Pasaron los tests para "<<this->clase_en_testeo<<endl<<endl;
	}

}

Test::~Test() {
	// TODO Auto-generated destructor stub
}
