/*
 * TestLista.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#include "TestLista.h"

TestLista::TestLista() {

	this->clase_en_testeo="Lista";

}

void TestLista::comenzar(){

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

void TestLista::inicializar(){

	this->distrito=new Distrito("Lanus");
	this->cargo=new Cargo("Presidente");
	this->eleccion=new Eleccion("20110901",*cargo,*distrito);
	this->lista=new Lista("Proyecto Sur",*this->eleccion);


}

bool TestLista::testConstructor(){
	bool error_encontrado=false;




	return error_encontrado;


}

bool TestLista::testLectura_y_Escritura(){
	bool error_encontrado=false;

	this->inicializar();




	this->liberarMemoria();

	return error_encontrado;

}


void TestLista::liberarMemoria(){

	delete distrito;
	delete cargo;
	delete eleccion;
	delete lista;

}

TestLista::~TestLista() {
	// TODO Auto-generated destructor stub
}
