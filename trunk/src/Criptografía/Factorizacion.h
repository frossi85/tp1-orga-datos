/* 
 * File:   Factorizacion.h
 * Author: facundo
 *
 * Created on 27 de noviembre de 2011, 22:50
 */

#ifndef FACTORIZACION_H
#define	FACTORIZACION_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

/// Metodos de Factorizacion de Primos.
/**
 * Esta, es una clase utilitaria que provee metodos de factorizacion de numeros primos:
 *
 * Actualmente cuenta con dos metodos de factorizacion:
 * 1- Divisiones sucesivas: Metodo no usado en la practica real por ser muy lento
 * 2- Fermat: Una implementacion de este metodo, que es mucho mas rapida que la del punto 1, pero no util para numeros demasiado grandes
*/

typedef long long unsigned EnteroLargo;
typedef long long int EnteroLargoSignado;

class Factorizacion {
	friend class TestFactorizacion;
public:
	/// Post: si el numero es factorizable devuelve los primos en p y q*/
	/**Factoriza el numero N en dos primos, si la factorizacion se realizo con exito se retorna true*/
    static bool divisionesSucesivas(EnteroLargo N, EnteroLargo &p, EnteroLargo &q);

    /// Post: si el numero es factorizable devuelve los primos en p y q*/
    /**Factoriza el numero N en dos primos, si la factorizacion se realizo con exito se retorna true*/
    static void fermat(EnteroLargo N, EnteroLargo &p, EnteroLargo &q);

private:
    static bool esPrimo(EnteroLargo a);
    static bool esDivisiblePor(EnteroLargo a, EnteroLargo b);

    static bool esCuadradoPerfecto(EnteroLargo a);

    Factorizacion();
    virtual ~Factorizacion();
};

#endif	/* FACTORIZACION_H */

