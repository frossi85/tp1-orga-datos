/* 
 * File:   TestRSA.h
 * Author: migue
 *
 * Created on 19 de noviembre de 2011, 18:30
 * 
 * IMPORTANTE!!!
 * 
 * No modificar nada de este test.
 * Esta hecho para que sea clase amiga de RSA, y por eso pueden 
 * dar errores de que no se encuentren las funciones y atributos 
 * que se estan accediendo.
 * 
 */

#ifndef TESTROMPERRSA_H
#define	TESTROMPERRSA_H
#include "RSA.h"

#include <iostream>

using namespace std;

class TestRomperRSA {
    friend class RSA;
public:
    TestRomperRSA();
    
    void iniciar();

    bool testRomperRSA();

    void msjInicioTest(string test){
        cout<<"*--------------------*"<<endl;
        cout<<"Se inicia el test para el metodo "<<test<<endl;
        
    };
    
    void msjTestExitoso(){
        cout<<"---Test terminado sin Errores---"<<endl;
    }
    
    void msjError(string metodo){
        cout<<"**Errores en Test de metodo "<<metodo<<endl;
    };
    
    void mostrarError(EnteroLargo esperado, EnteroLargo recivido){
        cout<<"Esperado: "<<esperado<<endl;
        cout<<"Recivido: "<<recivido<<endl;
        
    }
    void mostrarError(string esperado,string recivido){
        cout<<"Esperado: "<<esperado<<endl;
        cout<<"Recivido: "<<recivido<<endl;
        
    }
    
    void cargarRSACompleto(){
        delete this->rsa;
        this->rsa = new RSA;
        
    }
    
    virtual ~TestRomperRSA();
private:
    RSA *rsa;
    int errores;
};

#endif	/* TESTROMPERRSA_H */

