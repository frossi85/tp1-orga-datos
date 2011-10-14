/*
 * TestVotante.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#include "TestVotante.h"
#include "../DataAccess.h"
#include <iostream>

using namespace std;

TestVotante::TestVotante() {

	this->clase_en_testeo="Votante";

}

void TestVotante::inicializar(){
	this->distrito=new Distrito("Lanus");
	this->votante=new Votante(3500000,"Juan Perez","1234","Corrientes 444",*distrito);

}

void TestVotante::comenzar(){

	this->tituloTest();
	this->error_encontrado=false;

	if (this->testConstructor()){

		this->informarError("Constructor");
		this->error_encontrado=true;
	}

	if (this->testSetters()){

		this->informarError("Setters");
		this->error_encontrado=true;
	}

	if (this->testCambioClave()){

		this->informarError("Cambio de Clave");
		this->error_encontrado=true;
	}

	if(this->testLectura_y_Escritura()){

		this->informarError("Lectura y/o Escritura");
		this->error_encontrado=true;

	}

	this->finalizarTest();
}

bool TestVotante::testConstructor(){

	bool error=false;
	bool error_dni,error_nom,error_clave,error_domicilio,error_distrito;
	this->distrito=new Distrito("Urquiza");
	this->votante=new Votante(35000000,"Manuel Gonzales","5678","Mitre 1200",*distrito);

	error_dni= !(35000000==this->votante->getDNI());
	error_nom= !("Manuel Gonzales"==this->votante->getNombreYApellido());
	error_clave=!("5678"==this->votante->getClave());
	error_domicilio=!("Mitre 1200"==this->votante->getDomicilio());
	error_distrito=!("Urquiza"==this->votante->getDistrito().getNombre());

	error= error_dni || error_nom || error_clave || error_domicilio || error_distrito;


	this->liberarMemoria();

	return error;

}

bool TestVotante::testCambioClave(){

	bool error=false;
	this->inicializar();

	string clave_nueva="0001";


	this->votante->cambiarClave(this->votante->getClave(),clave_nueva);

	error=!(clave_nueva==this->votante->getClave());

	this->liberarMemoria();

	return error;

}

bool TestVotante::testSetters(){
	bool error_encontrado=false;
	bool error_distrito,error_domicilio,error_id;
	this->inicializar();

	Distrito distrito_nuevo("Espeleta");
	this->votante->setDistrito(distrito_nuevo);

	error_distrito=!(this->votante->getDistrito().getNombre()=="Espeleta");

	this->votante->setDomicilio("Callao 888");
	error_domicilio=!( this->votante->getDomicilio()== "Callao 888");

	this->votante->setId(1111);
	error_id=!(this->votante->getId()== 1111);

	error_encontrado= error_distrito || error_domicilio || error_id;

	this->liberarMemoria();
	return error_encontrado;

}

bool TestVotante::testLectura_y_Escritura(){

	bool error=false;
	bool error_id,error_nom,error_clave,error_domicilio;

	this->inicializar();
	DataAccess dt_acc;

	Votante vot1(56851133 ,"Manuel Perez","1234","Martinez 562",*this->distrito),
			vot2(15493286 ,"Victor Toledo","4321","Ortiz 2000",*this->distrito),
			vot3(16325891 ,"Germa Muñoz","4569","Callao 1002",*this->distrito),
			vot4(45632789 ,"Daniel Gomez","7892","Suipacha 444",*this->distrito),
			vot5(31256845 ,"Hugo Varela","2345","Mitre 300",*this->distrito);


	dt_acc.Guardar(vot1);
	dt_acc.Guardar(vot2);
	unsigned long int offset=dt_acc.Guardar(*this->votante);
	dt_acc.Guardar(vot3);
	dt_acc.Guardar(vot4);
	dt_acc.Guardar(vot5);

	Votante vot(this->votante->getDNI(),"","","",*this->distrito);

	dt_acc.Leer(vot,offset);

	error_id=!( vot.getId()==this->votante->getId());
	cout<<vot.getId()<<" "<<this->votante->getId()<<endl;

	error_nom=!( vot.getNombreYApellido()==this->votante->getNombreYApellido());
	cout<<vot.getNombreYApellido()<<" "<<this->votante->getNombreYApellido()<<endl;

	error_clave=!( vot.getClave()==this->votante->getClave());

	error_domicilio=!(vot.getDomicilio()==this->votante->getDomicilio());
	cout<<vot.getDomicilio()<<" "<<this->votante->getDomicilio()<<endl;

	error=	error_id || error_nom || error_clave || error_domicilio;

	this->liberarMemoria();
	return error;

}

void TestVotante::liberarMemoria(){

	delete this->distrito;
	delete this->votante;

}

TestVotante::~TestVotante() {

}
