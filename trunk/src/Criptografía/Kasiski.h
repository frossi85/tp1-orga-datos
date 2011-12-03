#ifndef KASISKI_H
#define	KASISKI_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>

using namespace std;

/** Clase estática que aplica el algoritmo de Kasiski y análisis de frecuencias para intentar
 * romper la encriptación de Vigenère.
 * Su único método público es Romper.
 */
class Kasiski {
private:

    //tipos

	/** Se usa para almacenar las posibles longitudes para la clave de Vigenère, junto con la cantidad de veces
	 * que aparece esa longitud como resultado del MCD entre las distancias entre cadenas repetidas. A mayor cantidad
	 * de ocurrencias, hay mayor probabilidad de que esa sea la longitud correcta.
	 */
    typedef struct _longitudPosible {
        unsigned long longitud;
        unsigned long ocurrencias;
    } longitudPosible;

	/** Se usa en el análisis de frecuencias. Almacena cada caracter junto con la cantidad de veces que aparece
	 * en el texto.
	 */
    typedef struct _caracterFrecuencia {
        char caracter;
        unsigned long frecuencia;
    } caracterFrecuencia;

    //atributos
    static char *bufferCriptograma;
    static size_t tamanioBuffer;
    static vector<longitudPosible> longPosibles;
    static const vector<string> PALABRAS_CONOCIDAS;
    static const vector<char> CARACTERES_FRECUENTES;
    static const unsigned int MIN_LONG_CADENA;
    static const unsigned int LONG_ALFABETO;

    //métodos

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
    static void AgregarAListaDeFrecuencias(vector<caracterFrecuencia> *listaFrec, char caracter);
    static char ObtenerCaracterMasFrecuente(vector<caracterFrecuencia> *listaFrec);
    /** aplica una clave tentativa al buffer para obtener el texto desencriptado.
     * Genera un archivo con el resultado en rutaDestino. */
    static void Desencriptar(const vector<char> *clave, const char* rutaDestino);
    /** devuelve cuántas veces aparecen las palabras del vector palabras en el archivo
     * de texto ubicado en rutaOrigen. */
    ///Devuelve -1 en caso de error.
    static int CantidadDeOcurrencias(const vector<string> palabras, const char* rutaOrigen);
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

