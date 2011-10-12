/*
 * TestEleccion.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#include "TestEleccion.h"
#include "../DataAccess.h"
#include <vector>


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

	if(this->testAgregarDistrito()){

		this->informarError("AgregarDistritos");
	}

}

void TestEleccion::inicializar(){

	Distrito *distrito=new Distrito("Lanus");
	Cargo *cargo=new Cargo("Presidente");
	this->eleccion=new Eleccion("20110901",*cargo,*distrito);
}

bool TestEleccion::testConstructor(){

	bool error_encontrado=false;

	Distrito *distrito=new Distrito("Avellaneda");
	Cargo *cargo=new Cargo("Gobernador");
	this->eleccion=new Eleccion("20110901",*cargo,*distrito);


	error_encontrado=!(this->eleccion->getClassName()=="Eleccion");


	this->liberarMemoria();

	return error_encontrado;


}


bool TestEleccion::testAgregarDistrito(){

	bool error_encontrado=false;
	bool error_cantidad,error_nombre;

	this->inicializar();

	Distrito distrito1("San Nicolas");

	this->eleccion->agregarDistrito(distrito1);

	vector<Distrito *> vec_distritos=this->eleccion->getDistritos();
	error_cantidad=!(vec_distritos.size()== 2);

	error_nombre=!(vec_distritos[1]->getNombre()=="San Nicolas");

	error_encontrado=error_nombre || error_cantidad;

	this->liberarMemoria();
	return error_encontrado;

}

bool TestEleccion::testLectura_y_Escritura(){

	bool error_encontrado=false;
	this->inicializar();

	DataAccess dtAccess;

	dtAccess.Guardar(*this->eleccion);





	this->liberarMemoria();
	return error_encontrado;

}

void TestEleccion::liberarMemoria(){

	delete cargo;
	delete distrito;
	delete eleccion;

}


TestEleccion::~TestEleccion() {

}
