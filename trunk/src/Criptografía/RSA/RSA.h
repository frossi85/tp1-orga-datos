/* 
 * File:   RSA.h
 * Author: migue
 *
 * Created on 19 de noviembre de 2011, 16:22
 * 

 * 
 */

#ifndef RSA_H
#define	RSA_H
#include <stdlib.h>
#include <iostream>
#include "../Factorizacion.h"

using namespace std;

typedef long long unsigned EnteroLargo;
typedef long long int EnteroLargoSignado;


/*
 * 
 * Estructura usada para almacenar las claves
 * 
 */


class Clave {
public:
    Clave(){
        this->_X=0; this->_N=0;
    };
    
    Clave(EnteroLargo x,EnteroLargo n){
        this->_X=x; this->_N= n;
    };
    
    EnteroLargo N(){ return this->_N;}
    EnteroLargo D(){ return this->_X;}
    EnteroLargo E(){ return this->_X;}
    
    void setN(EnteroLargo n){this->_N=n;}
    void setD(EnteroLargo d){this->_X=d;}
    void setE(EnteroLargo e){this->_X=e;}
    
private:
    EnteroLargo _N,_X;    
};





class RSA {
    friend class TestRSA;
private:
    void generarCLaves();
    void generarD();
    bool generarE(EnteroLargo d,EnteroLargo phi_n);
    bool esPrimo(const EnteroLargo &numero);
    bool esMCDUno(const EnteroLargo &a,const EnteroLargo &b);
    void determinarCantidadChar();
    
    void complementoEspecial(EnteroLargo &a,const EnteroLargo &phi_n);
    
    EnteroLargo calcularModulo(EnteroLargo a,EnteroLargo b,EnteroLargo q);
    
    int generarAleatorio();
   
    std::string convertirAString(EnteroLargo *numeros,int cant);
    EnteroLargo* convertirAEnteroLargo(std::string mensaje,int &cant);
    
    string realizarProceso(string mensaje,const EnteroLargo &clave);
    int tamanioEnteroUtilizado();
    
    
    EnteroLargo P,Q,N,phiN,D,E;
    int cantidadChar;
    bool modo_encriptar;

public:
    
    /*
     * Constructor que genera las claves automaticamente
     */
    RSA();
    
    
    /*
     * Constructor que recive las clase que se pretenden usar.
     * Si las claves no son las correctas el encriptador funcionara MAL!!!
     */
    RSA(Clave privada,Clave publica);
    
    
    /*
     * Metodo que devuelve la clave PUBLICA que se esta utilizando
     */
    Clave getClavePublicaActual();
    
    /*
     * Metodo que devuelve la clave PRIVADA que se esta utilizando     
     */    
    Clave getClavePrivadaActual();
    
    
    /*
     * Metodo que setea las claves publica y privada que se tienen que utilizar para
     * encriptar y desencritar. Si las claves no son validas, habra errores en la 
     * encriptacion.
     */
    void setClaves(Clave privada,Clave publica);
    
    
    /*
     * Metodo que encripta un string recivido con la clave PUBLICA actual,
     * y lo devuelve en forma de string
     */
    std::string encriptar(std::string mensaje);
    
    /*
     * Metodo que desencripta un string recivido con la clave PRIVADA actual.
     * y devuelve el mensaje desencriptado en forma de string
     */
    std::string desencriptar(std::string msj_encrip);


	//Devuelve el exponente d de la calve privada

    /*
	 * Metodo que a partir de la clave publica (e,n) la romper y devuelve el exponente d de la calve privada
	 */
    static EnteroLargo romper(EnteroLargo e, EnteroLargo n);

    virtual ~RSA();
private:

};

#endif	/* RSA_H */

