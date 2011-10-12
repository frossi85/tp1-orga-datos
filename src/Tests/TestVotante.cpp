/*
 * TestVotante.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#include "TestVotante.h"
#include <iostream>

using namespace std;

TestVotante::TestVotante() {
	// TODO Auto-generated constructor stub

}

void TestVotante::inicializar(){
	Distrito *distrito=new Distrito("Lanus");
	this->votante=new Votante(3500000,"Juan Perez","1234","Corrientes 444",*distrito);

}

void TestVotante::comenzar(){

	cout<<"Comenzo Test de Votante"<<endl;



}

bool TestVotante::testConstructor(){

	bool error=false;




	return error;

}

bool TestVotante::testCambioClave(){

	bool error=false;
	this->inicializar();

	string clave_nueva="0001";


	return error;

}

bool TestVotante::testSetters(){
	bool error=false;



	return error;

}

TestVotante::~TestVotante() {
	// TODO Auto-generated destructor stub
}
