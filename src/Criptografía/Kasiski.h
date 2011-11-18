#ifndef KASISKI_H
#define	KASISKI_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Kasiski {
private:

    //tipos
    typedef struct _longitudPosible {
        unsigned long longitud;
        unsigned long ocurrencias;
    } longitudPosible;

    typedef struct _caracterFrecuencia {
        char caracter;
        unsigned long frecuencia;
    } caracterFrecuencia;

    ///atributos
    static char *bufferCriptograma;
    static vector<longitudPosible> longPosibles;
    static const vector<string> palabrasConocidas;

    ///métodos

    /** carga el texto en el buffer, eliminando espacios, signos de
     * puntuación, etc. si fuera necesario */
    ///Devuelve false en caso de error
    static bool LeerCriptograma(const char* rutaCriptograma);
    /** Devuelve el máximo común divisor entre x e y. */
    static unsigned long MCD(unsigned long x, unsigned long y);
    /** busca cadenas repetidas en el buffer, calcula la distancia entre
     * ellas, calcula el mcd entre ese número y los que ya están en el vector
     * de longitudes posibles de la clave, y agrega cada uno de los valores
     * obtenidos a dicho vector. */
    ///Devuelve false en caso de error
    static bool ProcesarCadenasRepetidas();
    /** agrega un valor al vector de longitudes posibles, o incrementa
     * su número de ocurrencias si ya estaba en el vector. */
    ///Devuelve false en caso de error
    static bool AgregarLongitud(unsigned long longitud);
    /** saca del vector de longitudes posibles la que tenga más ocurrencias,
     * y la devuelve. */
    ///Devuelve 0 en caso de error
    static unsigned long ObtenerLongitudMasProbable();
    /** busca en el texto las palabras del vector de palabras conocidas.
     * Devuelve cuántas de esas palabras fueron encontradas. */
    ///Devuelve -1 en caso de error
    static int BuscarPalabrasConocidas(const char* rutaTexto);
    /** Libera la memoria reservada por las estructuras de la clase. */
    static void LiberarMemoria();

public:
    /** Usando el método de Kasiski y análisis de frecuencias obtiene
     * varias claves posibles, por cada una genera el archivo supuestamente
     * desencriptado y busca en el las palabras conocidas. Deja sólo el archivo
     * en el que más de esas palabras aparezcan. Si no aparece ninguna en ningún
     * archivo, deja aquel que crea que más probablemente sea el correcto (porque
     * se lo obtuvo haciendo las sustituciones de símbolos con más probabilidades
     * de ser las correctas, por ejemplo). Los archivos generados se guardan en
     * rutaDestino. Antes de terminar llama a LiberarMemoria. */
    ///Devuelve false en caso de error.
    static bool Romper(const char* rutaCriptograma, const char* rutaDestino);
};

#endif	/* KASISKI_H */

