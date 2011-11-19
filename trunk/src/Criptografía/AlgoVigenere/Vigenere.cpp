/*
 * File:   Vigenere.cpp
 * Author: martin
 *
 */

#include <string>

#include "Vigenere.h"

Vigenere::Vigenere() {
    this->long_alfabeto = 26;
}

Vigenere::Vigenere(string clave) {
    this->clave = clave;
    this->long_alfabeto = 26;
}

Vigenere::Vigenere(const Vigenere& orig) {
    this->clave = orig.clave;
    this->long_alfabeto = orig.long_alfabeto;
}

Vigenere::~Vigenere() {
}

string Vigenere::getClave() {
    return this->clave;
}

void Vigenere::setClave(string clave) {
    this->clave = clave;
}

string Vigenere::cifrarCadena(string mensaje) {
    string criptograma;
    int long_clave = this->clave.length();
    int long_mensaje = mensaje.length();
    int pos = 0;
    for(int i=0;i<long_mensaje;i++) {
        int caracter = (((mensaje[i]-char('A')) + (this->clave[pos]-char('A'))) % this->long_alfabeto);
        pos++;
        caracter = caracter + char('A');
        if(pos >= long_clave)   pos = 0;
        criptograma += caracter;
    }
    return criptograma;
}

string Vigenere::descifrarCadena(string criptograma) {
    string mensaje;
    int long_clave = this->clave.length();
    int long_criptograma = criptograma.length();
    int pos = 0;
    for(int i=0;i<long_criptograma;i++) {
        int caracter = (((criptograma[i]-char('A')) - (this->clave[pos]-char('A')))%this->long_alfabeto);
        if (caracter < 0) caracter += this->long_alfabeto;
        pos++;
        caracter = caracter + char('A');
        if(pos >= long_clave)   pos = 0;
        mensaje += caracter;
    }
    return mensaje;
}
