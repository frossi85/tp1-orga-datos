/*
 * File:   Vigenere.h
 * Author: martin
 *
 */


/*
 * TABLA DE VIGENERE:
 *
 * SE USA LA CODIFICACION DE CARACTERES DEL SISTEMA (UTF-8?) CON UN TOTAL DE 128 CARACTERES (DEL 0x00 AL 0x7f).
 * NO USAR 'Ñ', 'ñ', '¡', '¿', 'ü', acentos, ENTRE LOS MAS CONOCIDOS.
 *
 *
 * BUG CONOCIDO:
 *
 * AL ENCRIPTAR UN ARCHIVO, PUEDE DARSE EL CASO DE QUE UN CARACTER DEL CRIPTOGRAMA QUE SE VA A GUARDAR
 * EN EL ARCHIVO ENCRIPTADO SEA EL 0x00. POR EJEMPLO LA SUMA DEL @+@ (64+64 = 128, 128 MOD 128 = 0).
 * ESTO PRODUCE UN ERROR AL ABRIR EL ARCHIVO  ENCRIPTADO (CON EL GEDIT!!) PORQUE EL SISTEMA NO RECONOCE LA CODIFICACION DE
 * CARACTERES. PUEDE SER DEBIDO AL TEMA DEL "EOF"?
 * ACTUALIZACION: CON EL ECLIPSE LOS ABRE BIEN. PUEDE QUE SEA SOLO CON EL GEDIT.
 *
 * SIN EMBARGO, EL CRIPTOGRAMA SE GUARDA PERFECTAMENTE, YA QUE AL DESENCRIPTAR ESE ARCHIVO, EL MENSAJE ORIGINAL
 * ES EL CORRECTO Y EL ARCHIVO DESENCRIPTADO SE PUEDE ABRIR PERFECTAMENTE.
 *
 *
 * TESTS:
 *
 * PARA PROBAR DESDE UN ARCHIVO DE TEXTO. DEBE EXISTIR EL ARCHIVO A CIFRAR. EL ARCHIVO CIFRADO Y EL POSTERIORMENTE
 * DESCIFRADO PUEDEN NO EXISTIR, EN CASO DE EXISTIR SERAN REEMPLAZADOS POR LOS NUEVOS.
 *
 *
 * MODO DE TESTEO:
 *
 *    Vigenere test;
 * 	  test.ejecutarTestArchivo();
 */


#ifndef VIGENERE_H
#define	VIGENERE_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Vigenere {
public:
    Vigenere();
    Vigenere(const Vigenere& orig);
    virtual ~Vigenere();

    void setClave(string clave);
    string getClave();

    bool cifrarArchivo(string ruta_arch_aCifrar, string ruta_arch_cifrado);
    bool descifrarArchivo(string ruta_arch_aDescifrar, string ruta_arch_descifrado);

    void ejecutarTestArchivo();

private:
    string clave;
    int long_alfabeto;

};

#endif	/* VIGENERE_H */
