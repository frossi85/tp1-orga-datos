/* 
 * File:   TestRomperRSA.cpp
 * Author: Facundo
 * 
 * Created on 29 de noviembre de 2011, 18:30
 * 
 * IMPORTANTE!!!
 * 
 * No modificar nada de este test.
 * Esta hecho para que sea clase amiga de RSA, y por eso pueden 
 * dar errores de que no se encuentren las funciones y atributos 
 * que se estan accediendo.
 * 
 * 
 */

#include "TestRomperRSA.h"
#include <iostream>


using namespace std;

TestRomperRSA::TestRomperRSA() {
    this->rsa = new RSA(Clave(0,0),Clave(0,0));
    
}

void TestRomperRSA::iniciar(){
    this->errores=0;
    
    if (!this->testRomperRSA()){
        this->msjError("TestRomperRSA");
        this->errores++;
    }
    else
        this->msjTestExitoso();
    
    if(this->errores!=0){
        cout<<"****************************************"<<endl;
        cout<<"Fallaron "<<this->errores<<" Test"<<endl;
        cout<<"****************************************"<<endl;
    }else{
        
        cout<<"Todos los Test Pasaron Correctamente"<<endl;
    }
}

bool TestRomperRSA::testRomperRSA()
{
	this->msjInicioTest("romperRSA");
	this->cargarRSACompleto();

	EnteroLargo clavePrivadaPorRuptura = 0;

	cout<<endl<<"Clave publica E: "<<rsa->getClavePublicaActual().E()<<endl;
	cout<<endl<<"Clave privada D: "<<rsa->getClavePrivadaActual().D()<<endl;
	cout<<endl<<"Numero compuesto primo N: "<<rsa->getClavePublicaActual().N()<<endl;

	cout<<endl<<"Se comienza factorizacion de N ="<<rsa->getClavePublicaActual().N();
	cout<<", el proceso puede tardar hasta 5 minutos"<<endl;

	clavePrivadaPorRuptura = RSA::romper(rsa->getClavePublicaActual().E(), rsa->getClavePublicaActual().N());

	cout<<"Se termino el procedimiento de ruptura de la clave RSA termino, la clave privada obtenida fue: "<<clavePrivadaPorRuptura<<endl;

	if(rsa->getClavePrivadaActual().D() == clavePrivadaPorRuptura)
		return true;
	else
		return false;
}

TestRomperRSA::~TestRomperRSA(){
    
    delete this->rsa;
}

