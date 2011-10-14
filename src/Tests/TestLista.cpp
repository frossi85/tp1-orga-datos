/*
 * TestLista.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */



#include "TestLista.h"
#include "../DataAccess.h"

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
	bool error_nombre,error_eleccion;
	this->inicializar();

	error_nombre=!(this->lista->getNombre()=="Proyecto Sur");

	error_eleccion=!( this->lista->getEleccion().getFecha()=="20110901"); //ultimo numero es 1

	error_encontrado=error_nombre || error_eleccion;

	this->liberarMemoria();

	return error_encontrado;

}

bool TestLista::testLectura_y_Escritura(){
	bool error=false;
	bool error_nombre,error_id,error_id_eleccion;
	this->inicializar();
//
//	DataAccess dtacc;
//
//	cout<<"Llego.."<<endl;
//	unsigned long int offset=dtacc.Guardar(*this->lista);
//
//
//	Lista lista("aaa",*this->eleccion);
//
//	dtacc.Leer(lista,offset);
//
//
//	error_nombre=!(this->lista->getNombre()==lista.getNombre());
//
//	error_id=!( this->lista->getId()==lista.getId() );
//
//	error_id_eleccion=!( this->lista->getEleccion().getId()==lista.getEleccion().getId() );
//
//	error= error_nombre || error_id || error_id_eleccion;


	this->liberarMemoria();

	return error;

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
