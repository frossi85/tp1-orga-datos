/*
 * TestCargo.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#include "TestCargo.h"
#include <vector>

TestCargo::TestCargo() {

	this->clase_en_testeo="Cargo";

}

void TestCargo::comenzar(){

	this->tituloTest();
	this->error_encontrado=false;

	if (this->testConstructor()){
		this->informarError("Constructor");
		this->error_encontrado=true;
	}

	if (this->testAgregarCargoSecundarios()){
			this->informarError("Agregar Cargos Secundarios");
			this->error_encontrado=true;
	}

	if (this->testLectura_y_Escritura()){
		this->informarError("Lectura y/o Escritura");
		this->error_encontrado=true;
	}

	this->finalizarTest();

}

void TestCargo::inicializar(){

	this->cargo=new Cargo("Presidente");

}


bool TestCargo::testConstructor(){
	bool error_encontrado=false;
	bool error_cargo_principal,error_nom_clase;
	this->cargo=new Cargo("Intendente");

	error_cargo_principal=!(this->cargo->getCargoPrincipal()=="Intendente");

	error_nom_clase=!(this->cargo->getClassName()=="Cargo");

	error_encontrado=error_cargo_principal || error_nom_clase;

	this->liberarMemoria();
	return error_encontrado;
}

bool TestCargo::testAgregarCargoSecundarios(){
	bool error_encontrado=false;
	bool error_cantidad,error_nombres;

	this->inicializar();

	this->cargo->agregarCargoSecundario("Vicepresidente");
	this->cargo->agregarCargoSecundario("Gobernador");
	this->cargo->agregarCargoSecundario("Diputado");

	vector<string> vec_cargos=this->cargo->getCargosSecundarios();

	error_cantidad=!( vec_cargos.size()==3 );

	error_nombres=	!( vec_cargos[0]=="Vicepresidente") ||
					!( vec_cargos[1]=="Gobernador")		||
					!( vec_cargos[2]=="Diputado");

	error_encontrado= error_cantidad || error_nombres;

	this->liberarMemoria();
	return error_encontrado;
}


bool TestCargo::testLectura_y_Escritura(){
	bool error_encontrado=false;


	return error_encontrado;
}
void TestCargo::liberarMemoria(){
	delete this->cargo;
}

TestCargo::~TestCargo() {
	// TODO Auto-generated destructor stub
}
