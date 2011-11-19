/*
 * File:   Vigenere.h
 * Author: martin
 *
 */

/*
 * ESTA LIMITADO TODAVIA. LIMITACIONES:
 *
 * SOLO SE ACEPTAN EN EL MENSAJE LETRAS, DE LA 'A' A LA 'Z' SIN LA 'Ñ' Y SOLO EN MAYUSCULA
 * NADA DE ESPACIOS,PUNTUACION,MINUSCULAS,NUMEROS
 *
 * TODAVIA NO TRABAJO CON ARCHIVOS DE TEXTO, SOLO CON STRINGS PASADOS
 *
 * EJEMPLOS DE MENSAJES SON (ESTAN EN LAS DIAPOSITIVAS Y EL RESUMEN DE CRIPTO):
 * MENSAJE: DEMOSTRACIONDELTEOREMA   / CLAVE: DATOS
 * MENSAJE_2: PARISVAUTBIENUNEMESSE	 / CLAVE: LOUP
 *
 *
 */

#ifndef VIGENERE_H
#define	VIGENERE_H

using namespace std;

class Vigenere {
public:
    Vigenere();
    Vigenere(string clave);
    Vigenere(const Vigenere& orig);
    virtual ~Vigenere();

    void setClave(string clave);
    string getClave();

    string cifrarCadena(string mensaje);
    string descifrarCadena(string criptograma);

private:
    string clave;
    int long_alfabeto;


};

#endif	/* VIGENERE_H */


/* EJEMPLO DE USO (PONGO EL MAIN QUE USE PARA PROBAR)
 *
 * #include <iostream>
#include <string>

#include "Vigenere.h"
using namespace std;


int main(int argc, char** argv) {

    string cad_aux;
    string criptograma;
    string mensaje;

    Vigenere test_cripto;

    cout << "Ingrese una clave: ";
    cin >> cad_aux;
    test_cripto.setClave(cad_aux);
    cout << "Su clave es: " << test_cripto.getClave() << endl;

    do {
        cout << endl << "Ingrese un mensaje: ";
        cin >> mensaje;
        criptograma = test_cripto.cifrarCadena(mensaje);
        cout << "El criptograma es: " << criptograma << endl;
        cout << "El desencriptado es: " << test_cripto.descifrarCadena(criptograma) << endl;
        cout << "¿Desea probar con otro mensaje? (S/N): ";
        cin >> cad_aux;
    } while (cad_aux[0] == 'S');

    return 0;
}

*/
